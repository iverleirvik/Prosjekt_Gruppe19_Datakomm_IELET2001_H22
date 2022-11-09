#ifndef UbidostsUnsub_h
#define UbidostsUnsub_h
#include "UbidotsEsp32Mqtt.h"
class UbidotsUnsub : public Ubidots {       
    public: 
    bool unSubscribe(const char* topic);
    bool unSubscribeLastValue(const char* deviceLabel, const char* variableLabel); 
    UbidotsUnsub(const char* token):Ubidots(token){};
  UbidotsUnsub(const char* token, const char* clientName):Ubidots( token, clientName){};
  UbidotsUnsub(const char* token, const char* broker, const int brokerPort):Ubidots(token, broker,  brokerPort){};
  UbidotsUnsub(const char* token, const char* clientName, const char* broker):Ubidots( token,  clientName, broker){};
  UbidotsUnsub(const char* token, const char* clientName, const char* broker, const int brokerPort):Ubidots(token,  clientName,  broker,  brokerPort){};

    
};

#endif