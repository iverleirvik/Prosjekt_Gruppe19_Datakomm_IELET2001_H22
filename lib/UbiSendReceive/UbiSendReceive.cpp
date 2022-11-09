#include "UbiSendReceive.h"

void UbiSendReceive::UbiSendReceive_CALLBACK(char *topic, byte *payload, unsigned int length) {
  char charWord[20];
  for (int i = 0; i < length; i++)
  {
    //Serial.print((char)payload[i]);
    charWord[i] = (char)payload[i];
  }// word = firstLetter + secondLetter

  Serial.println();

  if(strstr(topic, "/v2.0/devices/esp32/1/lv")){
    skrittFelles.push_back(atoi(charWord));
    }

  if(strstr(topic, "/v2.0/devices/esp32/2/lv")){
    newDay = true;
    }
}

  void UbiSendReceive::UbiSendReceive_INIT(const char *VARIABLE_DATA, const char *VARIABLE_NEWDAY){
  ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_DATA);
  ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_NEWDAY);
  }

 void UbiSendReceive::UbiSendReceive() {
  if (newDay == true){
    if (millis() > 1000 && notPubYet == false) {
    Serial.println("pub");
    ubidots.add(VARIABLE_LABEL, /*Skritt*/5);
    ubidots.publish(DEVICE_LABEL);
    notPubYet = true;

    startTime = millis();
    }

    if(millis() > startTime + 9000) {
    newDay = false;
    notPubYet = false;
    Serial.println("starter på nytt");

    // LEGG INN ALVAR OG TORSTEIN FUNKSJON

    skrittFelles.clear();
    }
  }
 }