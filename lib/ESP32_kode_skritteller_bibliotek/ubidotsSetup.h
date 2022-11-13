#ifndef ubidotsSetup_h
#define ubidotsSetup_h

#include "UbidotsEsp32Mqtt.h"
#include <Arduino.h>
//#include "UbidotsConfig.h"

namespace ubidotsSetup {
void init(Ubidots& ubidots, void(*callback) (char*, byte*, unsigned int),const char *ssid, const char *pass);
int checkConnection( Ubidots&ubidots, char *deviceLabel, const char *subVariableLabel[], int subVariableLength, int timerStarter);
void sub ( Ubidots&ubidots, char *deviceLabel, const char *subVariableLabel[], int subVariableLength, int timerStarter);
//int vERDI{100001}; // MÅ GJØRES ORDENTLIG
}
#endif //ubidotsSetup_h
