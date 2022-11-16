#ifndef ubidotsSetup_cpp
#define ubidotsSetup_cpp


//#include "UbidotsEsp32Mqtt.h"
#include "ubidotsSetup.h"
//#include <Arduino.h>
namespace ubidotsSetup {

void init(Ubidots & ubidots, void(*callback) (char*, byte*, unsigned int), const char *ssid, const char *pass)  // Funksjon som setter opp koblingen til ubidots.
{
  // put your setup code here, to run once:
  Serial.begin(115200); // Starter Serial.
  while (!Serial);
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(ssid, pass);  // Kobler til internett.
  ubidots.setCallback(callback);  // Setter callbackfunksjonen som vi sev har laget.
  ubidots.setup();                // Kjører oppsett av ubidots.
  ubidots.reconnect();            // Kobler seg til på nytt.
}
int checkConnection( Ubidots &ubidots, char *deviceLabel, const char *subVariableLabel [], int subVariableLength, int timerStarter) { // Sjekker om man fortsatt er koblet til.
  ubidots.loop(); // Sjekker tilstanden i ubidots. F. eks om det har kommet meldinger på variabelen.
  if (!ubidots.connected()) // Hvis den ikke er koblet opp lenger, start prosedyre for å gjenoppta koblingen.
  {
    ubidots.reconnect();
    
    sub(ubidots,  deviceLabel,  subVariableLabel, subVariableLength, timerStarter);
    return 1;
  }
  return 0;
}

void sub ( Ubidots &ubidots, char *deviceLabel, const char *subVariableLabel [], int subVariableLength, int timerStarter) { // Funksjon abonnerer på variabel og enheter.
  for (int i = 0; (i < subVariableLength) ; i++ ) {
    ubidots.subscribeLastValue(deviceLabel, subVariableLabel[i]);
  }

  ubidots.add(subVariableLabel[2], timerStarter); // Denne delen prøver å sette i gang et event på ubidots ved oppstart av når man abonnerer på en variabel.
  ubidots.publish(deviceLabel);

}
}



#endif
