#ifndef UbiSendReceive_h
#define UbiSendReceive_h

#include <Arduino.h>
#include "UbidotsEsp32Mqtt.h"
#include "UbidotsConfig.h"
#include <vector>
using namespace std;
#include "UbidotsConfig.h"

class UbiSendReceive {
    protected:
        bool newDay{false};
        bool notPubYet{false};
        unsigned long startTime{0};
        

    public:
        void UbiSendReceive_CALLBACK(char *topic, byte *payload, unsigned int length);
        void UbiSendReceive_INIT(const char *VARIABLE_DATA, const char *VARIABLE_NEWDAY,Ubidots &ubidots);
        void UbiSendReceive_loop(Ubidots &ubidots);
        vector<int> skrittFelles; // Lagt den her midlertidig. Plasseringen vil komme ann på kode til
                                  // til Torstein og Alvar. Ellers kommer vi til å trenge GET og SET-ish.
};

#endif //UbiSendReceive_h
