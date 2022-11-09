#ifndef stepManager_cpp
#define stepManager_cpp


#include <WiFi.h>
#include "time.h"
#include "UbidotsEsp32Mqtt.h"
#include "stepManager.h"


void stepManager::init () {
  const char* ntpServer = "pool.ntp.org";
  const long  gmtOffset_sec = 0;
  const int   daylightOffset_sec = 3600;
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}
void stepManager::registerStep() {

  if (stepManager::getDateInYear() != _prevDayCycle) {
    _currentDaySteps = 0;
  }
  _currentDaySteps += 1;
  _currentCycleSteps += 1;
  _prevDayCycle=stepManager::getDateInYear();
}

unsigned int stepManager::getCurrentCycleSteps() {
  return _currentCycleSteps;
}

unsigned long stepManager::getCurrentDaySteps() {
  return _currentDaySteps;
}

int stepManager::getDateInYear() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return -1;
  }
  return timeinfo.tm_yday;
}
void stepManager::resetStepCycle() {
  _currentCycleSteps = 0;
}

void stepManager::ubiPublisStep(){
  _Ubidots.add(_cycleLabel, stepManager::getCurrentCycleSteps());
  _Ubidots.add(_dayLabel, stepManager::getCurrentDaySteps());
  _Ubidots.add(_daySent, stepManager::getDateInYear());
  _Ubidots.publish(_deviceLabel);
  stepManager::resetStepCycle();
}

const char* _cycleLabel;
    const char* _dayLabel ;
#endif
