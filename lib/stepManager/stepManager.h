#ifndef stepManager_h
#define stepManager_h


#include <WiFi.h>
#include "time.h"
#include "UbidotsUnsub.h"

class stepManager {
  public:
    stepManager (UbidotsUnsub & Ubidots,const char * deviceLabel, const char * cycleLabel,const char * dayLabel, const char * daySent) : 
    _Ubidots(Ubidots), _cycleLabel(cycleLabel),_dayLabel(dayLabel), _deviceLabel(deviceLabel), _daySent(daySent) {}
    void init ();                          //initialize
    void registerStep();                    //register one step
    unsigned int getCurrentCycleSteps();    // get the current amount og step.
    unsigned long   getCurrentDaySteps();   //get total steps today
    void resetStepCycle();                  //reset counter in current cycle. use after sending to Ubidots 
    void resetDayCycle();                   //reset counter in current cycle. use when new day or series is started.
    void ubiPublisStep();                   //send steps data and reset current cycle.
    int getDateInYear();                    //get the day in the curren year. 0 indexed.
    void addDayStep(int steps);

    // update currentDaySteps if Ubidots has valid old data. 
    void handelUbidotsCalback(char * topic, int payloadInt);
  protected:
    int _notUpdated=1;
    int _timer=0;
    unsigned int _currentCycleSteps;        // number of steps in the current cycle
    unsigned long _currentDaySteps;         //number of steps today.
    int _oldStep;
    int _oldDay;
    //int _prevDayCycle;
    UbidotsUnsub & _Ubidots;
    const char* _cycleLabel;                //where to send cycle
    const char* _dayLabel ;                 //where to send the current day
    const char* _deviceLabel;               //name of device
    const char* _daySent;                   //value of today.
    

};



#endif
