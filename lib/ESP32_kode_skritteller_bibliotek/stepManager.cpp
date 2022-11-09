#ifndef stepManager_cpp
#define stepManager_cpp


#include <WiFi.h>
#include "time.h"
#include "UbidotsUnsub.h"
#include "stepManager.h"


void stepManager::init () {
  const char* ntpServer = "pool.ntp.org";
  const long  gmtOffset_sec = 0;
  const int   daylightOffset_sec = 3600;
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}
void stepManager::registerStep() {

  _currentDaySteps += 1;
  _currentCycleSteps += 1;
  //_prevDayCycle=stepManager::getDateInYear();
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
void stepManager::resetDayCycle() {
  _currentDaySteps = 0;
}

void stepManager::ubiPublisStep(){
  _Ubidots.add(_cycleLabel, stepManager::getCurrentCycleSteps());
  _Ubidots.add(_dayLabel, stepManager::getCurrentDaySteps());
  _Ubidots.add(_daySent, stepManager::getDateInYear());
  _Ubidots.publish(_deviceLabel);
  stepManager::resetStepCycle();
}
void stepManager::addDayStep(int steps){
  _currentDaySteps += steps;
}
void stepManager::handelUbidotsCalback(char * topic, int payloadInt){
if (strstr(_daySent, topic))
  {
    if (payloadInt == stepManager::getDateInYear())
    {
      if (_oldStep != -1)
        stepManager::addDayStep(_oldStep);
      _oldDay = 1;
    }
    _Ubidots.unSubscribeLastValue(_deviceLabel, _daySent);
  }
  else if (strstr(_dayLabel, topic))
  {
    _oldStep = payloadInt;
    _Ubidots.unSubscribeLastValue(_deviceLabel, _dayLabel);
    if (_oldDay = 1)
      stepManager::addDayStep(_oldStep);
  }
  }
#endif
