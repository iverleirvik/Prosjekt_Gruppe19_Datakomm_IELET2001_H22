#ifndef UbiSendReceive_h
#define UbiSendReceive_h

#include <Arduino.h>                //
#include "UbidotsEsp32Mqtt.h"       //  Innkluderer biblioteker nødvendig for klassen.
#include "OLED.h"                   //
#include "Adafruit_SSD1306.h"       //
                                    //
#include <vector>                   //

using namespace std;


class UbiSendReceive {
    protected:
        bool newDay{false};     // Variabler for tilstandsmaskiner.
        bool notPubYet{false};
        unsigned long startTime{0};
        Ubidots &_ubidots;  // Deklarer objekter. Denne er interessant siden den gjør det som en referanse til objektet fra constructor. Det vil derfor holde seg opppdatert.
        OLED oled;
        char* _variableLabel;   // Lokale variabler for ubidots.
        char* _deviceLabel;
        int vinner;
        int lockedSteps; 
        int firstMessagesIgnore{0}; // Brukes hvis det er meldinger registrert i ubidots databaser.
        int Placement{1};
        int timerEspSendMessage{1000}; // Kan være lurt at er forskjellig mellom hver av enhetene.
        int timerEspStopListening{9000};    // En tid der all data må være sendt fordi skrittelleren slutter å lytte etter meldinger.
        
    public:
        UbiSendReceive(char * deviceLabel, char* variableLabel, Ubidots &ubidots): 
        _deviceLabel(deviceLabel), _variableLabel(variableLabel), _ubidots(ubidots){};  //Constructor. En måte å initialisere et objekt på.
        
        void UbiSendReceive_CALLBACK(char *topic, byte *payload, unsigned int length, int steps);   // Deklarer funksjoner brukt i UbiSendReceive.
        void UbiSendReceive_INIT(const char *VARIABLE_DATA, const char *VARIABLE_NEWDAY);   // IKKE BRUKT, men kan brukes til å abonnere på variabler.
        void UbiSendReceive_loop(Adafruit_SSD1306 &display, int &steps);    // Funksjonen som blir brukt i hver runde i loopen.
        vector<int> skrittFelles; // Lagt den her midlertidig. Plasseringen vil komme ann på kode til
                                  // til Torstein og Alvar. Ellers kommer vi til å trenge GET og SET-ish.

};

#endif 
