#ifndef dummyGetSensorData_h
#define dummyGetSensorData_h
#include <Arduino.h>
namespace dummy
{
    int getStep()
    {
        if (analogRead(34) == 100)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
#endif