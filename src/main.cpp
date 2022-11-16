/****************************************************************
   Owen Lyke @ SparkFun Electronics
   Original Creation Date: April 17 2019

   Please see License.md for the license information.
   Distributed as-is; no warranty is given.
 ***************************************************************/

#include "ICM_20948.h"
#include "ubidotsSetup.h"
#include "UbidotsEsp32Mqtt.h"
#include "secrets.h"
#include "UbidotsConfig.h"
#include "UbiSendReceive.h"

// -----------------------------------------------------------------------------------------
// SENSOR
#define SERIAL_PORT Serial
#define WIRE_PORT Wire // Your desired Wire port.      Used when "USE_SPI" is not defined
#define AD0_VAL 1      // The value of the last bit of the I2C address. On the SparkFun 9DoF IMU breakout the default is 1, and when the ADR jumper is closed the value becomes 0.
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// SCREEN
#define WIRE Wire
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// Declaring objects
Ubidots ubidots(UBIDOTS_TOKEN);
ICM_20948_I2C myICM; 
UbiSendReceive talley(DEVICE_LABEL_2, VARIABLE_LABEL_2, ubidots);
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE, OLED_RESET);
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// Declaring local functions
float pythagorasAcc(ICM_20948_I2C *sensor);
void numberOfSteps(int &stepCounter, int sensorAccLevel);
void callback(char *topic, byte *payload, unsigned int length);
void stepScreen(Adafruit_SSD1306 &display, int steps);
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// Declaring and defining local variables
int stepC{0};
unsigned long sensorTimer{0};
int sensorAccuracyTime{170};
int sensorAccLevel{1200};
unsigned long screenTimer{0};
int screenUpdateRate{1000};
// -----------------------------------------------------------------------------------------

void setup()
{
  ubidotsSetup::init(ubidots, callback, WIFI_SSID, WIFI_PASS);
  ubidotsSetup::sub(ubidots, DEVICE_LABEL_2, SUB_VARIABLE_LABEL, SUB_VARIABLE_LABEL_LENGTH, ubidotsStartTimer);

  WIRE_PORT.begin();
  WIRE_PORT.setClock(400000);

  // myICM.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial


// -------------------------------------------------------------------------------
  // SKJERM
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS); // Address 0x3C for 128x32
// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
  // SENSOR
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
// -------------------------------------------------------------------------------
}


void loop() {

  ubidotsSetup::checkConnection(ubidots, DEVICE_LABEL_2, SUB_VARIABLE_LABEL, SUB_VARIABLE_LABEL_LENGTH, ubidotsStartTimer);
  talley.UbiSendReceive_loop(display, stepC);

  if(millis() > screenTimer + screenUpdateRate) {
    stepScreen(display, stepC);
    screenTimer = millis();
  }

  if (myICM.dataReady())  {
    if (millis() > sensorTimer + 30 + sensorAccuracyTime) {  // 30 kommer fra sensoren må ha. Kan sløyfes.
      myICM.getAGMT();
      numberOfSteps(stepC, sensorAccLevel);
      sensorTimer = millis();
    }
  }
  else  {
    SERIAL_PORT.println("Waiting for data");
    delay(500);
  }
  display.clearDisplay();
}




float pythagorasAcc(ICM_20948_I2C *sensor)  {
  return sqrt(pow(sensor->accX(), 2) + pow(sensor->accY(), 2) + pow(sensor->accZ(), 2));
}

void numberOfSteps(int &stepCounter, int sensorAccLevel)  {
  if (pythagorasAcc(&myICM) > sensorAccLevel) {
    stepCounter++;
    Serial.println(stepC);
  }
}

void callback(char *topic, byte *payload, unsigned int length)  {
  int payloadInt;
  char paloadChar[20];
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)  {
    paloadChar[i] = ((char)payload[i]);
  }
  payloadInt = atoi(paloadChar);
  Serial.println(payloadInt);
  talley.UbiSendReceive_CALLBACK(topic, payload, length, stepC);
}

void stepScreen(Adafruit_SSD1306 &display, int steps) {

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println(steps);
  display.display();

}
