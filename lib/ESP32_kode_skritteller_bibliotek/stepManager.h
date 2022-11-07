#ifndef stepManager_h
#define stepManager_h


#include <WiFi.h>
#include "time.h"

class stepManager {
  public:
    void init ();
    void registerStep();
    unsigned int getCurrentCycleSteps();
    unsigned long   getCurrentDaySteps();
    void resetStepCycle();

  private:
    int getDateInYear();

    unsigned int _currentCycleSteps;
    unsigned long _currentDaySteps;
    int _prevDayCycle;

};



#endif
