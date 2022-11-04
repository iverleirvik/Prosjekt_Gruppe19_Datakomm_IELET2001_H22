/****************************************************************
   Owen Lyke @ SparkFun Electronics
   Original Creation Date: April 17 2019

   Please see License.md for the license information.
   Distributed as-is; no warranty is given.
 ***************************************************************/
 
#include "ICM_20948.h"

#define SERIAL_PORT Serial
#define WIRE_PORT Wire // Your desired Wire port.      Used when "USE_SPI" is not defined
#define AD0_VAL 1      // The value of the last bit of the I2C address. On the SparkFun 9DoF IMU breakout the default is 1, and when the ADR jumper is closed the value becomes 0.

ICM_20948_I2C myICM; // Otherwise create an ICM_20948_I2C object

float pythagorasAcc(ICM_20948_I2C *sensor);
void numberOfSteps(int &stepCounter);
int stepC{0};

void setup()
{
  SERIAL_PORT.begin(115200);
  while (!SERIAL_PORT);

  WIRE_PORT.begin();
  WIRE_PORT.setClock(400000);

  //myICM.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

  bool initialized = false;
  while (!initialized)
  {
    myICM.begin(WIRE_PORT, AD0_VAL);

    SERIAL_PORT.print(F("Initialization of the sensor returned: "));
    SERIAL_PORT.println(myICM.statusString());
    if (myICM.status != ICM_20948_Stat_Ok)
    {
      SERIAL_PORT.println("Trying again...");
      delay(500);
    }
    else
    {
      initialized = true;
    }
  }
}

void loop()
{
  if (myICM.dataReady())
  {
    myICM.getAGMT();  // The values are only updated when you call 'getAGMT'
    delay(30);
    delay(170); // lagt til av Iver

    Serial.println(pythagorasAcc(&myICM));
    numberOfSteps(stepC);
    Serial.println(stepC); 
  }
  else
  {
    SERIAL_PORT.println("Waiting for data");
    delay(500);
  }
}


float pythagorasAcc(ICM_20948_I2C *sensor) {
  return sqrt(pow(sensor->accX(), 2) + pow(sensor->accY(), 2) + pow(sensor->accZ(), 2)); // Kan vurdere å fjerne sqrt.
}

void numberOfSteps(int &stepCounter){
  if(pythagorasAcc(&myICM) > 1200) stepCounter++;
}