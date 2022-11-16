#include "UbiSendReceive.h"

void UbiSendReceive::UbiSendReceive_CALLBACK(char *topic, byte *payload, unsigned int length, int steps) {
  char charWord[20];
  for (int i = 0; i < length; i++)  {
    charWord[i] = (char)payload[i];
  }

  ///*
  if(firstMessagesIgnore <= 3) { // SKAL ANTAGELIGVIS SLETTES
    firstMessagesIgnore++;
    return;
  }
  //*/

  if(strstr(topic, "/v2.0/devices/esp32/1/lv")) { // OBS: Pass på og endre topic-streng til ubidotsbrukeren!
    skrittFelles.push_back(atoi(charWord));   // Legger verdi til i vectoren
  }

  if(strstr(topic, "/v2.0/devices/esp32/2/lv")) {
    newDay = true;
    lockedSteps = steps;
    Serial.println("Callback 2");
  }
  Serial.println("generell callback");
}

void UbiSendReceive::UbiSendReceive_INIT(const char *VARIABLE_DATA, const char *VARIABLE_NEWDAY ) {
  _ubidots.subscribeLastValue(_deviceLabel, VARIABLE_DATA);
  _ubidots.subscribeLastValue(_deviceLabel, VARIABLE_NEWDAY);
}


void UbiSendReceive::UbiSendReceive_loop(Adafruit_SSD1306 &display, int &steps) {
  if (newDay == true) {
    if (millis() > timerEspSendMessage && notPubYet == false) {
      _ubidots.add(_variableLabel, lockedSteps);
      _ubidots.publish(_deviceLabel);
      notPubYet = true;
      Serial.println("Inne i pub");
      startTime = millis();
    }

    if(millis() > startTime + timerEspStopListening) {
      newDay = false;
      notPubYet = false;
      Serial.println("ferdig nå");
// -----------------------------------------------------------------------------
        
        // LEGG INN ALVAR OG TORSTEIN FUNKSJON
          {
            sort(skrittFelles.begin(), skrittFelles.end(), greater<int>());
            vinner = skrittFelles[0];
            for(int i = 0; i < skrittFelles.size(); i++) {
              if(skrittFelles[i] > lockedSteps)  {
                Placement += 1;
              }
            }
            if(Placement == 1){           
              oled.victoryCelebration(display);
            }
            else {
              oled.loserNotification(Placement, display);
            }
            Placement = 1;
          }
// -----------------------------------------------------------------------------
      skrittFelles.clear();
      lockedSteps = 0;
      steps = 0;
      }
    }
}
