#ifndef UbidostsUnsub_h
#define UbidostsUnsub_h
#include "UbidotsEsp32Mqtt.h"
class UbidotsUnsub : public Ubidots {       
     
    bool unSubscribe(const char* topic);
    bool unSubscribeLastValue(const char* deviceLabel, const char* variableLabel);  
};

#endif