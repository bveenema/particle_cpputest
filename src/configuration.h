/********************************
configuration.h

Author: Ben Veenema
Description: Contains hardware configuration information used in multiple modules
********************************/
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// Power Source configuration
#define NUMPOWERSOURCES 2
#define HIGHVOLTPOWER 0
#define USBPOWER 1
struct powerSource {
  uint8_t type;
  uint16_t maxCurrent;
};

const struct powerSource power[NUMPOWERSOURCES] {
  {HIGHVOLTPOWER, 18000},
  {USBPOWER, 2000}
};

// USB Port configuration options (USB_C cannot be disabled, USB_2 has no medium)
#define PORT_DISABLE 0
#define PORT_HI 1
#define PORT_MED 2
#define PORT_LOW 3

// Number of USB Charging Ports
#define NUMPORTS 8

// Types of USB Charging Ports
#define NUMTYPES 2
#define USB_2 0
#define USB_C 1

// Friendly reference to USB Charging Ports
#define PORT0 0
#define PORT1 1
#define PORT2 2
#define PORT3 3
#define PORT4 4
#define PORT5 5 // BAT
#define PORT6 6
#define PORT7 7


struct portStruct {
  uint8_t type;
  int adcPin;
  uint8_t shiftLocation; // bit in shift register where a ports configuration bits begin
  uint8_t priority; // Lowest number is highest priority (ex. 0 is highest priority)
};

// Friendly access to HW configuration of every USB Chargin Port
// Array of ports with structure {type, adcPin, shiftLocation}
// Location in array refers to PORT# (ex. PORT3 = HW_ports[3])
const struct portStruct HW_ports[NUMPORTS] = {
  {USB_2, A2, 24, 0}, //PORT0
  {USB_2, A3, 4, 2},  //PORT1
  {USB_2, A4, 12, 2}, //PORT2
  {USB_2, A5, 8, 2},  //PORT3
  {USB_2, A6, 20, 2}, //PORT4
  {USB_2, A7, 16, 2}, //PORT5 (BAT)
  {USB_C, A0, 0, 1},  //PORT6
  {USB_C, A1, 2, 1},  //PORT7
};

// Shift Register pins
#define SHIFT_OUT D2
#define SHIFT_IN D3
#define SHIFT_CLK D4
#define SHIFT_OUT_EN D5
#define SHIFT_IN_EN D6
#define SHIFT_LOAD D7

#endif
