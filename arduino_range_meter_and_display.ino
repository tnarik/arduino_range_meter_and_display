// Do not remove the include below
#include "arduino_range_meter_and_display.h"

#include <SPI.h>
#include <SPI7Segment.h>

const int sonar_pwm_pin    = 3;
// the Arduino default constant 'SS' is used (10). Any other IO pin could be used
//const int slave_select_pin = 10;

int pwm_val () {
  unsigned long raw_pwm_value = pulseIn(sonar_pwm_pin, HIGH);
  // From the datasheet: PW - This pin outputs a pulse width representation of range.
  // To calculate distance use the scale factor of 147mS per inch (57.87 per cm)
  return raw_pwm_value/57.87;
}


//The setup function is called once at startup of the sketch
void setup() {
  Serial.begin(9600);
  pinMode(sonar_pwm_pin, INPUT);

  SPI.begin(); //Start the SPI hardware
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV64); //Slow down the master 1/64

  //Send the reset command to the display - this forces the cursor to return to the beginning of the display
  SPI7Segment.command('v', ' '); //Reset command
  SPI7Segment.command(0x7A, 0x20); // brightness setup (will wear out the flash or eeprom with every write).
}

// The loop function is called in an endless loop
void loop() {
  int cms = pwm_val();
  Serial.println(cms);
  SPI7Segment.number(cms, 10);
  delay(100);

}
