#ifndef ubidotsSetup_h
#define ubidotsSetup_h

#include "UbidotsUnsub.h"
#include <Arduino.h>

namespace ubidotsSetup {
void init(UbidotsUnsub & ubidots, void(*callback) (char*, byte*, unsigned int),const char *ssid, const char *pass);
int checkConnection( UbidotsUnsub &ubidots, char *deviceLabel, const char *subVariableLabel[], int subVariableLength);
void sub ( UbidotsUnsub &ubidots, char *deviceLabel, const char *subVariableLabel[], int subVariableLength);
}
#endif //ubidotsSetup_h
