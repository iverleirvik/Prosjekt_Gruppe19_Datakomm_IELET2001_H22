#ifndef ubidotsSetup_cpp
#define ubidotsSetup_cpp


//#include "UbidotsEsp32Mqtt.h"
#include "ubidotsSetup.h"
//#include <Arduino.h>
namespace ubidotsSetup {

void init(Ubidots & ubidots, void(*callback) (char*, byte*, unsigned int), const char *ssid, const char *pass)
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(ssid, pass);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
}
int checkConnection( Ubidots &ubidots, char *deviceLabel, const char *subVariableLabel [], int subVariableLength, int timerStarter) {
  ubidots.loop();
  if (!ubidots.connected())
  {
    ubidots.reconnect();
    
    sub(ubidots,  deviceLabel,  subVariableLabel, subVariableLength, timerStarter);
    return 1;
  }
  return 0;
}

void sub ( Ubidots &ubidots, char *deviceLabel, const char *subVariableLabel [], int subVariableLength, int timerStarter) {
  for (int i = 0; (i < subVariableLength) ; i++ ) {
    ubidots.subscribeLastValue(deviceLabel, subVariableLabel[i]);
  }

  ubidots.add(subVariableLabel[2], timerStarter);
  ubidots.publish(deviceLabel);

}
}



#endif
