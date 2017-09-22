#include "ParticleDummy.h"

// I/O Functions
void pinMode(uint16_t, uint8_t){}
uint16_t analogRead(uint16_t){return 0;}

// Timing Functions
uint32_t millis(void){return 0;}
void delayMicroseconds(uint32_t){}
