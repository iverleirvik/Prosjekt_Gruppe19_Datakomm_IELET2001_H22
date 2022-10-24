#ifndef ubidotsSetup_cpp
#define ubidotsSetup_cpp


#include "UbidotsEsp32Mqtt.h"
#include "ubidotsSetup.h"
#include <Arduino.h>
namespace ubidotsSetup {

void init(Ubidots & ubidots, void(*callback) (char*, byte*, unsigned int), const char *ssid, const char *pass)
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(ssid, pass);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();

}
int checkConnection( Ubidots &ubidots, char *deviceLabel, const char *subVariableLabel [], int subVariableLength) {
  ubidots.loop();
  if (!ubidots.connected())
  {
    ubidots.reconnect();
    
    sub( ubidots,  deviceLabel,  subVariableLabel, subVariableLength);
    return 1;
  }
  return 0;
}

void sub ( Ubidots &ubidots, char *deviceLabel, const char *subVariableLabel [], int subVariableLength) {
for (int i = 0; (i < subVariableLength) ; i++ ){
  ubidots.subscribeLastValue(deviceLabel, subVariableLabel[i]); 

}


}





}



#endif
