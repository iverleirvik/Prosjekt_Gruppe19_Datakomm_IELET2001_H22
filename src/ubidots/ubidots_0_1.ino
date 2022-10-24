
#include "UbidotsEsp32Mqtt.h"
#include "secrets.h"
#include "ubidotsSetup.h"
#include "secrets.h"
Ubidots ubidots(UBIDOTS_TOKEN);

const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds
char *DEVICE_LABEL = "pedometer_1";   // Put here your Device label to which data  will be published
char *VARIABLE_LABEL = "steps"; // Put here your Variable label to which data  will be published

const char * SUB_VARIABLE_LABEL [] = {"start_comptetition","start"};
const int SUB_VARIABLE_LABEL_LENGTH=sizeof(SUB_VARIABLE_LABEL)/sizeof(SUB_VARIABLE_LABEL[0]);

unsigned long timer=0;
uint8_t analogPin = 34; // Pin used to read data from GPIO34 ADC_CH6.

void setup() {
ubidotsSetup::init(ubidots, callback , WIFI_SSID, WIFI_PASS);
ubidotsSetup::sub(ubidots, DEVICE_LABEL,SUB_VARIABLE_LABEL, SUB_VARIABLE_LABEL_LENGTH);

}

void loop()
{
  ubidotsSetup::checkConnection(ubidots, DEVICE_LABEL,SUB_VARIABLE_LABEL, SUB_VARIABLE_LABEL_LENGTH);
  
  if ((millis() - timer) > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {
    float value = analogRead(analogPin);
    ubidots.add(VARIABLE_LABEL, value); // Insert your variable Labels and the value to be sent
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }
  
}


void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
