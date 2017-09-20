/********************************
CurrentSense.h

Author: Ben Veenema
Description:
********************************/

#ifdef TESTING
  #include "../test/ParticleDummy.h"
#else
  #include "Particle.h"
#endif
#include "configuration.h"

#ifndef CURRENTSENSE_H
#define CURRENTSENSE_H

// Minimum time between current readings
#define CURRENT_READ_RATE 30 //30
#define SAMPLE_SIZE 64

class currentSense {
public:
  currentSense();

  //Setup Hardware
  void begin();

  //Maintenance function: Check if read is needed
  void update();

  //Return instantaneous total current
  uint16_t getTotalCurrent();

  //Return milli-Amps of single port
  uint16_t getPort(uint8_t port);

  //Return milli-Amps of all ports in array pointer
  uint16_t* getPorts();

private:
  void readPorts();
  void calculateAverage();

  bool hasMinSamples;
  uint16_t portsMilliAmps[NUMPORTS], totalCurrentOutput;
  uint32_t lastUpdateTime;
  uint16_t historyMilliAmps[NUMPORTS][SAMPLE_SIZE];
  uint8_t bufferIndex;
};

extern currentSense CurrentSense;

#endif
