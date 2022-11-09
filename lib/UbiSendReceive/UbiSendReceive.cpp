#include "UbiSendReceive.h"

void UbiSendReceive::UbiSendReceive_CALLBACK(char *topic, byte *payload, unsigned int length) {
  char charWord[20];
  for (int i = 0; i < length; i++)  {
    charWord[i] = (char)payload[i];
  }

  if(strstr(topic, "/v2.0/devices/esp32/1/lv")) { // OBS: Pass på og endre topic-streng til ubidotsbrukeren!
    skrittFelles.push_back(atoi(charWord));   // Legger verdi til i vectoren
  }

  if(strstr(topic, "/v2.0/devices/esp32/2/lv")) {
    newDay = true;
  }
}

void UbiSendReceive::UbiSendReceive_INIT(const char *VARIABLE_DATA, const char *VARIABLE_NEWDAY) {
  ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_DATA);
  ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_NEWDAY);
}

void UbiSendReceive::UbiSendReceive() {
  if (newDay == true) {
    if (millis() > 1000 && notPubYet == false) {
      bidots.add(VARIABLE_LABEL, /*Skritt*/5); //TODO: Legge inn kode for skritt
      ubidots.publish(DEVICE_LABEL);
      notPubYet = true;

      startTime = millis();
    }

    if(millis() > startTime + 9000) {
      newDay = false;
      notPubYet = false;

      // LEGG INN ALVAR OG TORSTEIN FUNKSJON

      skrittFelles.clear();
    }
  }
}