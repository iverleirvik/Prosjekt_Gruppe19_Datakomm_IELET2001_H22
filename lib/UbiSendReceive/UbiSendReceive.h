#ifndef UbiSendReceive_h
#define UbiSendReceive_h

#include <Arduino.h>
#include "UbidotsEsp32Mqtt.h"
#include "OLED.h"
#include "Adafruit_SSD1306.h"
#include <vector>

using namespace std;


class UbiSendReceive {
    protected:
        bool newDay{false};
        bool notPubYet{false};
        unsigned long startTime{0};
        Ubidots &_ubidots;
        OLED oled;
        char* _variableLabel;
        char* _deviceLabel;
        int vinner;
        int lockedSteps; 
        int firstMessagesIgnore{0}; // Brukes hvis det er meldinger registrert i ubidots databaser.
        int Placement{1};
        int timerEspSendMessage{1000}; // Kan være lurt at er forskjellig mellom hver av enhetene.
        int timerEspStopListening{9000};
        
    public:
        UbiSendReceive(char * deviceLabel, char* variableLabel, Ubidots &ubidots): 
        _deviceLabel(deviceLabel), _variableLabel(variableLabel), _ubidots(ubidots){};
        
        void UbiSendReceive_CALLBACK(char *topic, byte *payload, unsigned int length, int steps);
        void UbiSendReceive_INIT(const char *VARIABLE_DATA, const char *VARIABLE_NEWDAY);
        void UbiSendReceive_loop(Adafruit_SSD1306 &display, int &steps);
        vector<int> skrittFelles; // Lagt den her midlertidig. Plasseringen vil komme ann på kode til
                                  // til Torstein og Alvar. Ellers kommer vi til å trenge GET og SET-ish.

};

#endif 
