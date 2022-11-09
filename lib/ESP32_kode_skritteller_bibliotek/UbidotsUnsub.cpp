#ifndef UbidostsUnsub_cpp
#define UbidostsUnsub_cpp
#include "UbidotsUnsub.h"
#include "UbidotsEsp32Mqtt.h"
namespace UbidotsUnsub {
bool UbidotsUnsub::unSubscribe(const char* topic) { return _clientMqttUbi.subscribe(topic); }

/**
 * Retrieves data from Ubidots by subscribing to an lv topic
 * @arg deviceLabel [Mandatory] device label where the dot is stored
 * @arg variableLabel [Mandatory] variable label where the dot is stored
 */

bool UbidotsUnsub::unSubscribeLastValue(const char* deviceLabel, const char* variableLabel) {
  char topic[MAX_BUFFER_SIZE];
  sprintf(topic, "/v2.0/devices/%s/%s/lv", deviceLabel, variableLabel);
  Serial.print("Subscribing to");
  Serial.println(topic);
  return UbidotsUnsub::unsubscribe(topic);
}
}


#endif