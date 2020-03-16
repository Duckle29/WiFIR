#include "main.h"

#define CLEAR_PIN D7

void setup() {
  Serial.begin(115200);
  //schlep(5e6);
  WiFiManager wifiManager;

  pinMode(CLEAR_PIN, INPUT_PULLUP);
  delay(10);

  if(!digitalRead(CLEAR_PIN)) // If reset via clear pin
  {
    // Wait 5 seconds
    uint32_t delay_start = millis();
    while(!digitalRead(CLEAR_PIN) && millis() - delay_start > 5000)
    {
      delay(50);
    }
    // Ensure any button bounce has cleared in case the button was released prematurely.
    delay(10);

    // If button still held, clear WiFi settings.
    if(!digitalRead(CLEAR_PIN))
    {
      wifiManager.resetSettings();
    }
  }

  wifiManager.autoConnect("WiFIR");
}

void loop() {
  // put your main code here, to run repeatedly:
}


char * uintToStr( const uint64_t num, char *str )
{
  uint8_t i = 0;
  uint64_t n = num;
 
  do
    i++;
  while ( n /= 10 );
 
  str[i] = '\0';
  n = num;
 
  do
    str[--i] = ( n % 10 ) + '0';
  while ( n /= 10 );

  return str;
}

void schlep(uint64_t duration)
{
  char dur[21];
  uintToStr(duration, dur);
  Serial.println("Sleeping for " + String(dur) + "uS");
  ESP.deepSleepInstant(duration);
}