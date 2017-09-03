#include "NTPClock2.h"
//#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"

// Module connection pins
const byte PIN_CLK = 0;   // define CLK pin (any digital pin)
const byte PIN_DIO = 2;   // define DIO pin (any digital pin)

// Create clock object
SevenSegmentExtended clock(PIN_CLK, PIN_DIO);

//-----------------------------------------------------------------------------
// SETUP     SETUP     SETUP     SETUP     SETUP     SETUP     SETUP     SETUP
//-----------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  
  // All the WiFi and NTP stuff
  doSetup();

  // LED TM1637 Display
  clock.begin();
  clock.setBacklight(100);//% brightness
  //clock.setColonOn(true);

  Serial.println("Setup completed");
}

//-----------------------------------------------------------------------------
// LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP
//-----------------------------------------------------------------------------
void loop() {
  //digitalClockDisplay();

  //We just want the hour() and minute() to display
  clock.printTime(hour(),minute(),true);

  // We don't need to do this very often
  delay(400);
}
