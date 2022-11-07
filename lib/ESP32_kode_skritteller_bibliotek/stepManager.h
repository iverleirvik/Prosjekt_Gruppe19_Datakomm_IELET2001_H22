#ifndef stepManager_h
#define stepManager_h


#include <WiFi.h>
#include "time.h"

class stepManager {
  public:
    void init ();                          //initialize
    void registerStep();                   //register one step
    unsigned int getCurrentCycleSteps();   // get the current amount og step.
    unsigned long   getCurrentDaySteps();  //get total steps today
    void resetStepCycle();                 //reset counter in current cycle. use after sending to Ubidots 

  private:
    int getDateInYear();                   //get the day in the curren year. 0 indexed.

    unsigned int _currentCycleSteps;       // number of steps in the current cycle
    unsigned long _currentDaySteps;        //number of steps today.
    int _prevDayCycle;

};



#endif
