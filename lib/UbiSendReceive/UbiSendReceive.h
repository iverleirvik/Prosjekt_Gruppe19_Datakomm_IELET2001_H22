#ifndef UbiSendReceive_h
#define UbiSendReceive_h

#include <Arduino.h>
#include "UbidotsEsp32Mqtt.h"
#include <vector>
using namespace std;


class UbiSendReceive {
    protected:
        bool newDay{false};
        bool notPubYet{false};
        unsigned long startTime{0};
        Ubidots  &_ubidots;
        char* _variableLabel;
        char* _deviceLabel;
        

    public:
        UbiSendReceive(char * deviceLabel, char* variableLabel, Ubidots & ubidots): 
        _deviceLabel(deviceLabel), _variableLabel(variableLabel), _ubidots(ubidots){};
        
        void UbiSendReceive_CALLBACK(char *topic, byte *payload, unsigned int length);
        void UbiSendReceive_INIT(const char *VARIABLE_DATA, const char *VARIABLE_NEWDAY);
        void UbiSendReceive_loop();
        vector<int> skrittFelles; // Lagt den her midlertidig. Plasseringen vil komme ann på kode til
                                  // til Torstein og Alvar. Ellers kommer vi til å trenge GET og SET-ish.

};

#endif //UbiSendReceive_h
