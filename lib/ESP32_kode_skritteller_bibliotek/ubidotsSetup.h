#ifndef ubidotsSetup_h
#define ubidotsSetup_h

#include "UbidotsEsp32Mqtt.h"   Inkluderer nødvendig bibliotek.
#include <Arduino.h>

namespace ubidotsSetup {    // namespace istedenfor klasse. En annen måte å gjøre ting på. En måte at funksjoner og variabler kan ha samme navn utenom at de overkjører hverandre.
void init(Ubidots& ubidots, void(*callback) (char*, byte*, unsigned int),const char *ssid, const char *pass);   // Deklarering av funksjoner som henter inn informasjon
int checkConnection( Ubidots&ubidots, char *deviceLabel, const char *subVariableLabel[], int subVariableLength, int timerStarter);  // som burde være hemmelig, eller av 
void sub ( Ubidots&ubidots, char *deviceLabel, const char *subVariableLabel[], int subVariableLength, int timerStarter);    // hensiktsmessige årsaker.
}
#endif
