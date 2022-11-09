#ifndef UbiSendReceive_h
#define UbiSendReceive_h

#include <Arduino.h>
#include "UbidotsEsp32Mqtt.h"
#include "UbidotsConfig.h"
#include <vector>
using namespace std;

bool newDay{false};
bool notPubYet{false};
unsigned long startTime{0};
vector<int> skrittFelles;

namespace UbiSendReceive {
    void UbiSendReceive_CALLBACK(char *topic, byte *payload, unsigned int length);
    void UbiSendReceive_INIT(const char *VARIABLE_DATA, const char *VARIABLE_NEWDAY);
    void UbiSendReceive();
}

#endif UbiSendReceive_h
