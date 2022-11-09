#ifndef stepManager_h
#define stepManager_h


#include <WiFi.h>
#include "time.h"
#include "UbidotsEsp32Mqtt.h"

class stepManager {
  public:
    stepManager (Ubidots & Ubidots,const char * deviceLabel, const char * cycleLabel,const char * dayLabel) : 
    _Ubidots(Ubidots), _cycleLabel(cycleLabel),_dayLabel(dayLabel), _deviceLabel(deviceLabel) {}
    void init ();                          //initialize
    void registerStep();                    //register one step
    unsigned int getCurrentCycleSteps();    // get the current amount og step.
    unsigned long   getCurrentDaySteps();   //get total steps today
    void resetStepCycle();                  //reset counter in current cycle. use after sending to Ubidots 
    void ubiPublisStep();                   //send steps data and reset current cycle.
  private:
    int getDateInYear();                    //get the day in the curren year. 0 indexed.
    int _timer=0;
    unsigned int _currentCycleSteps;        // number of steps in the current cycle
    unsigned long _currentDaySteps;         //number of steps today.
    int _prevDayCycle;
    Ubidots _Ubidots;
    const char* _cycleLabel;
    const char* _dayLabel ;
    const char* _deviceLabel;

};



#endif
