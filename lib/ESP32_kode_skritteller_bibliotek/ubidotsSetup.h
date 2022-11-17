#ifndef ubidotsSetup_h
#define ubidotsSetup_h

#include "UbidotsEsp32Mqtt.h"   Inkluderer nødvendig bibliotek.
#include <Arduino.h>

namespace ubidotsSetup {    // namespace istedenfor klasse. En annen måte å gjøre ting på. En måte at funksjoner og variabler kan ha samme navn utenom at de overkjører hverandre.
// Deklarering av funksjoner som henter inn informasjonson. ssid og pass burde være hemmelig, men er i det miste lagt i egen .h fil.
void init(Ubidots& ubidots, void(*callback) (char*, byte*, unsigned int),const char *ssid, const char *pass);   
// må kjøres jevnlig. sjekker tilkoblingen og om det er kommet nye meldinger.
int checkConnection( Ubidots&ubidots, char *deviceLabel, const char *subVariableLabel[], int subVariableLength, int timerStarter); 
// subscriber til de angitte Topivenen i subVariableLabel.
void sub ( Ubidots & ubidots, char *deviceLabel, const char *subVariableLabel[], int subVariableLength, int timerStarter);    
}
#endif
