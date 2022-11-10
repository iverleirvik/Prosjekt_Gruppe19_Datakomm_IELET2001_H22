#ifndef ubidotsSetup_h
#define ubidotsSetup_h

#include "UbidotsEsp32Mqtt.h"
#include <Arduino.h>

namespace ubidotsSetup {
void init(Ubidots& ubidots, void(*callback) (char*, byte*, unsigned int),const char *ssid, const char *pass);
int checkConnection( Ubidots&ubidots, char *deviceLabel, const char *subVariableLabel[], int subVariableLength);
void sub ( Ubidots&ubidots, char *deviceLabel, const char *subVariableLabel[], int subVariableLength);
}
#endif //ubidotsSetup_h
