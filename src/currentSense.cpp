#include "currentSense.h"
currentSense CurrentSense;

//public:
  currentSense::currentSense(){}

  //Setup Hardware, set pins as inputs, clear historyMilliAmps and portsMilliAmps,
  //    set lastUpdateTime to ensure first update() call results in a read
  //    Reset hasMinSamples and bufferIndex
  void currentSense::begin(){
    for(uint8_t i=0; i<NUMPORTS; i++){
      pinMode(HW_ports[i].adcPin, INPUT);
      portsMilliAmps[i] = 0;
      for(uint8_t j=0; j<SAMPLE_SIZE; j++){
        historyMilliAmps[i][j] = 0;
      }
    }
    hasMinSamples = false;
    this->bufferIndex = 0;
    lastUpdateTime = millis()-CURRENT_READ_RATE-1;
  }

  //Maintenance funciont: Check if read is needed
  void currentSense::update(){
    uint32_t time = millis();
    if(time - lastUpdateTime > CURRENT_READ_RATE){
      readPorts();
      calculateAverage();
      lastUpdateTime = time;
    }
  }

  //Return instantaneous total current
  uint16_t currentSense::getTotalCurrent(){
    return totalCurrentOutput;
  }

  //Return milli-Amps of single port
  uint16_t currentSense::getPort(uint8_t port){
    return portsMilliAmps[port];
  }

  //Return milli-Amps of all ports in array pointer
  uint16_t* currentSense::getPorts(){
    return portsMilliAmps;
  }

//private:
  void currentSense::readPorts(){
    for(uint8_t i=0; i<NUMPORTS; i++){
      uint16_t rawADC = analogRead(HW_ports[i].adcPin);
      uint32_t milliAmps;
      if(HW_ports[i].type == USB_2) {
        // I = Vout / 1.5 --> (ADC*3.3*1000*10)/(4095*15)
        milliAmps = rawADC*33000/61425;
      } else if(HW_ports[i].type == USB_C) {
        milliAmps = 3000*rawADC/4095;
      } else {
        milliAmps = 0;
      }
      historyMilliAmps[i][this->bufferIndex] = (uint16_t) milliAmps;
      delayMicroseconds(10);
    }

    // Update Buffer
    this->bufferIndex += 1;
    if(bufferIndex >= SAMPLE_SIZE){
      hasMinSamples = 1;
      bufferIndex = 0;
    }
  }

  void currentSense::calculateAverage(){
    // Summate data points
    uint32_t dataSums[NUMPORTS] ={0};
    for(uint8_t i=0; i<NUMPORTS; i++){
      for(uint8_t j=0; j<SAMPLE_SIZE; j++){
        dataSums[i] += historyMilliAmps[i][j];
      }
    }
    // calculate Averarge
    uint32_t averageMilliAmps[NUMPORTS];
    totalCurrentOutput = 0;
    for(uint8_t i=0; i<NUMPORTS; i++){
      if(hasMinSamples){
        averageMilliAmps[i] = dataSums[i]/SAMPLE_SIZE;
      } else {
        averageMilliAmps[i] = dataSums[i]/this->bufferIndex;
      }
      portsMilliAmps[i] = (uint16_t)averageMilliAmps[i];
      totalCurrentOutput += portsMilliAmps[i];
    }
  }
