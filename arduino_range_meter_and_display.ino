// Do not remove the include below
#include "arduino_range_meter_and_display.h"

#include <SPI.h>

const int sonar_pwm_pin    = 3;
// the Arduino default constant 'SS' is used (10). Any other IO pin could be used
//const int slave_select_pin = 10;

int pwm_val () {
  unsigned long raw_pwm_value = pulseIn(sonar_pwm_pin, HIGH);
  // From the datasheet: PW - This pin outputs a pulse width representation of range.
  // To calculate distance use the scale factor of 147mS per inch (57.87 per cm)
  return raw_pwm_value/57.87;
}

void spi_out_command(byte command, byte data) {
  digitalWrite(SS, LOW); // enlow to select
  SPI.transfer(command);    // command
  if ( command != 0x76 && command != 0x81 ) {
    SPI.transfer(data);    // data
  }
  digitalWrite(SS, HIGH); // high to deselect
}

void spi_out_display(byte digit1, byte digit2, byte digit3, byte digit4) {
  digitalWrite(SS, LOW); // low to select
  SPI.transfer(digit1);
  SPI.transfer(digit2);
  SPI.transfer(digit3);
  SPI.transfer(digit4);
  digitalWrite(SS, HIGH); // high to deselect
}

void spi_out_number(unsigned short num, unsigned short base) {
  unsigned short digit[4] = { 0, ' ', ' ', ' ' };
  if ( (base<2) || (base>16) || (num>(base*base*base*base-1)) ) {
    spi_out_display('x', 'x', 'n', 'o');  // indicates overflow
  } else {
    unsigned short place = 0;
    while ( num && place < 4 ) {
      if ( num > 0 ) digit[place++] = num%base;
      num /= base;
    }

    spi_out_display(digit[3], digit[2], digit[1], digit[0]);
  }
}

//The setup function is called once at startup of the sketch
void setup() {
  Serial.begin(9600);
  pinMode(sonar_pwm_pin, INPUT);

  SPI.begin(); //Start the SPI hardware
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV64); //Slow down the master 1/64

  //Send the reset command to the display - this forces the cursor to return to the beginning of the display
  spi_out_command('v', ' '); //Reset command

  spi_out_command(0x7A, 0x20); // brightness setup (will wear out the flash or eeprom with every write).
}

// The loop function is called in an endless loop
void loop() {
  int cms = pwm_val();
  Serial.println(cms);
  spi_out_number(cms, 10);
  delay(100);

}
