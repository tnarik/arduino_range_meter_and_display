// Do not remove the include below
#include "arduino_range_meter_and_display.h"

const int sonar_pwm_pin    = 3;

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
}

// The loop function is called in an endless loop
void loop() {
  int cms = pwm_val();
  Serial.println(cms);
  delay(100);

}
