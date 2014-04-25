// Do not remove the include below
#include "arduino_range_meter_and_display.h"

#include <SPI.h>

const int sonar_pwm_pin    = 3;
int csPin = 10; //You can use any IO pin but for this example we use 10

int pwm_val () {
  unsigned long raw_pwm_value = pulseIn(sonar_pwm_pin, HIGH);
  //Serial.print("pwm: ");
  //Serial.println(raw_pwm_value);
  //Serial.println( raw_pwm_value/57.87);
  // Datasheet: PW - This pin outputs a pulse width representation of range.
  // To calculate distance use the scale factor of 147mS per inch ( 57.87 per cm)
  return raw_pwm_value/57.87;
}

//The setup function is called once at startup of the sketch
void setup() {
  Serial.begin(9600);
  pinMode(sonar_pwm_pin, INPUT);

  SPI.begin(); //Start the SPI hardware
  SPI.setClockDivider(SPI_CLOCK_DIV64); //Slow down the master a bit

  //Send the reset command to the display - this forces the cursor to return to the beginning of the display
  digitalWrite(csPin, LOW); //Drive the CS pin low to select OpenSegment
  SPI.transfer('v'); //Reset command
}

// The loop function is called in an endless loop
void loop() {
  int cms = pwm_val();
  Serial.println(cms);
  delay(100);

}
