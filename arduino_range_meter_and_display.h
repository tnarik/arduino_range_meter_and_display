// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _arduino_range_meter_and_display_H_
#define _arduino_range_meter_and_display_H_
#include "Arduino.h"
//add your includes for the project arduino_range_meter_and_display here

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project arduino_range_meter_and_display here
int pwm_val ();
void spi_out_command(byte command, byte data); // send a command
void spi_out_display(byte digit1, byte digit2, byte digit3, byte digit4); // a byte per digit
void spi_out_number(unsigned short num, unsigned short base); // Use different bases

//Do not add code below this line
#endif /* _arduino_range_meter_and_display_H_ */
