/****************************************************************
   Owen Lyke @ SparkFun Electronics
   Original Creation Date: April 17 2019

   Please see License.md for the license information.
   Distributed as-is; no warranty is given.
 ***************************************************************/

#include "ICM_20948.h"  // 9DOF sensor
#include "ubidotsSetup.h" // For ubidots
#include "UbidotsEsp32Mqtt.h" // Ubidots
#include "secrets.h"  // Informasjon som burde holdes hemmelig.
#include "UbidotsConfig.h" // Informasjon som ikke trengs å holdes hemmelig.
#include "UbiSendReceive.h" // Bibliotek for samhandling og tilstandsmaskiner med ubidots.

#include <chrono>
#include <random>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <stdlib.h>

// -----------------------------------------------------------------------------------------
// SENSOR
#define SERIAL_PORT Serial  // Defineringen av navnet som ICM bruker til serial.
#define WIRE_PORT Wire //  Din ønskede wire port. Brukt når "USE_SPI" ikke er definert. 
#define AD0_VAL 1      // Verdien til den siste biten av I2C addressene. På sparkfun 9DoF IMU utbrytningskort er normalveriden 1, og når ADR jumperen er lukket blir normalverdien 0.
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// SCREEN
#define WIRE Wire // Defineringen av navnet som skjemren bruker til WIRE.
#define OLED_RESET 4  // Definering skjermen behøver.
#define SCREEN_ADDRESS 0x3C // Definering skjermen behøver.
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// Declaring objects
Ubidots ubidots(UBIDOTS_TOKEN); // Initialiserer for ubidots objektet.
ICM_20948_I2C myICM; // Definerer sensor objektet. 
UbiSendReceive talley(DEVICE_LABEL_2, VARIABLE_LABEL_2, ubidots); // Initialiserer UbiSendReceive objektet. Objekt på grunn av klasseegenskaper.
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE, OLED_RESET); //Initialiserer skjerm objektet.
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// Declaring local functions
float pythagorasAcc(ICM_20948_I2C *sensor);                   // Deklarer funksjoner brukt lokalt i mainfila. Dette er på grunn av at det er en .cpp fil og ikke .ino fil. 
void numberOfSteps(int &stepCounter, int sensorAccLevel);     // C++ påkrever det.
void callback(char *topic, byte *payload, unsigned int length);
void stepScreen(Adafruit_SSD1306 &display, int steps);
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// Initialiserer lokale variabler.
int stepC{0};
unsigned long sensorTimer{0}; // Disse variablene er brukt for å telle skritt, samt for repeterbare timede hendelser.
unsigned long screenTimer{0};

// Variablene under kan man endre på for å gi skrittelleren den karakteristikken man er ute etter.
int sensorAccuracyTime{170};  // Denne variabelen bestemmer hvor ofte sensoren skal foreta en måling. 1/(170ms + 30ms) = 5 målinger i sekundet.
int sensorAccLevel{1200}; // Hvilket nivå en måling skal registreres ved.
int screenUpdateRate{1000}; // Hvor odte en skjermen skal oppdatere antall skritt.
// -----------------------------------------------------------------------------------------

void setup()  // Prosesser som må gjennomføres før skrittelleren er operativ.
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(100, 2000);
  int timerEspSendMessage = distribution(generator);
  talley.timerEspSendMessage = timerEspSendMessage;
   
  ubidotsSetup::init(ubidots, callback, WIFI_SSID, WIFI_PASS);  // Legger til hemmelig informasjon og callback-funksjonen som man selv må legge til ting til.
  ubidotsSetup::sub(ubidots, DEVICE_LABEL_2, SUB_VARIABLE_LABEL, SUB_VARIABLE_LABEL_LENGTH, ubidotsStartTimer); // Funksjon som har ansvar for å abonnere på variabler.

// -------------------------------------------------------------------------------
  // SKJERM
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS); // Address 0x3C for 128x32. Starte skjermen.
// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
  // SENSOR

  WIRE_PORT.begin();  // Starte wire port.
  WIRE_PORT.setClock(400000); // Setter klokkehastigheten til 400k.

  // myICM.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

  bool initialized = false; // Initialiserer lokal variabel for å sjekke om sensoren fungerer som den skal.
  while (!initialized)  // while-løkke som varer så lenge sensoren ikke er initiialisert.
  {
    myICM.begin(WIRE_PORT, AD0_VAL);  // Starte sensoren ved hejlp av sensorobjektet.

    SERIAL_PORT.print(F("Initialization of the sensor returned: "));
    SERIAL_PORT.println(myICM.statusString()); // Sjekker om sensoren fungerer som den skal.
    if (myICM.status != ICM_20948_Stat_Ok)  // Sjekker om sensoren fungerer som den skal, hvis ikke vil while-løkka forestå.
    {
      SERIAL_PORT.println("Trying again...");
      delay(500); // Venter mellom hvert forsøk på å starte sensoren.
    }
    else
    {
      initialized = true; // Alt har gått fint og man kan gå videre.
    }
  }
// -------------------------------------------------------------------------------
}


void loop() { // løkke som vil repeteres så lenge skrittelleren er operativ.

  ubidotsSetup::checkConnection(ubidots, DEVICE_LABEL_2, SUB_VARIABLE_LABEL, SUB_VARIABLE_LABEL_LENGTH, ubidotsStartTimer); // Sjekker om alt står greit til med ubidots.
  talley.UbiSendReceive_loop(display, stepC); // Kjører funksjon som inneholder tilstandsmaskiner for kommunikasjon og visning av konkurranse på skjerm.

  if(millis() > screenTimer + screenUpdateRate) { // if-setning som har som ansvar å ikke skrive ut til skjermen alt for mange ganger om gangen. 
    stepScreen(display, stepC);
    screenTimer = millis();
  }

  if (myICM.dataReady())  { //  Funksjon som har samme funksjon som over, men som returnerer en boolsk verdi.
    if (millis() > sensorTimer + 30 + sensorAccuracyTime) {  // 30 kommer fra sensoren må ha. Kan sløyfes. Passer på at man registrerer et bestemt antall målinger i sekundet.
      myICM.getAGMT(); // 
      numberOfSteps(stepC, sensorAccLevel); // Bestemmer om man skal registrere et steg basert på manipuleringen av målingen gjort i pythagorasAcc-funksjonen.
      sensorTimer = millis(); // Tiden som sier noe om siste måling som ble registrert.
    }
  }
  else  {
    SERIAL_PORT.println("Waiting for data");  // Er ikke sensoren ok skriv ut dette og vent et halvt sekund.
    delay(500);
  }
  display.clearDisplay(); // Tøm skjermen før neste runde i loopen.
}




float pythagorasAcc(ICM_20948_I2C *sensor)  { // Funksjon som nøytraliserer hvilken orientering skrittelleren holdes i.
  return sqrt(pow(sensor->accX(), 2) + pow(sensor->accY(), 2) + pow(sensor->accZ(), 2));  // roten av summen til kvadratene av akselerometerverdiene.
}

void numberOfSteps(int &stepCounter, int sensorAccLevel)  { 
  if (pythagorasAcc(&myICM) > sensorAccLevel) { // SJekker om målingen er betydelig nok for at et skritt skal registreres.
    stepCounter++; //Øker skrittet.
    Serial.println(stepC);  // Viser i serial monitoren.
  }
}

void callback(char *topic, byte *payload, unsigned int length)  { // Vil kjøres når det kommer en ny melding fra ubidots. Innholdet fra ubidots blir sendt videre som argument.
  int payloadInt;          // Initialiserer en rekke variabler for å kunne oversette til brukbare datatyper.
  char paloadChar[20];
  Serial.print("Message arrived [");  // Viser hvilken variabel meldingen kommer fra.
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)  {         // En del av oversettingen.
    paloadChar[i] = ((char)payload[i]);       //
  }                                           //
  payloadInt = atoi(paloadChar);              //
  Serial.println(payloadInt);                 //
  talley.UbiSendReceive_CALLBACK(topic, payload, length, stepC); // UbiSendReceive funksjonen som er laget for å kjøres i callback.
}

void stepScreen(Adafruit_SSD1306 &display, int steps) { // Funksjonen som viser hvor mange skritt man har til nå. Viktigste oppgave er å legge innkomne skritt
                                                        // fra andre skrittellere inn i en vektor som kan brukes til å sjekke om man fått flest skritt eller ikke.
  display.clearDisplay(); // Tømmer skjermen.
  display.setTextSize(3); // Setter tekststørrelsen til 3.
  display.setTextColor(SSD1306_WHITE);  // Setter tekstfargen til hvit.
  display.setCursor(0,0); // Plassering av tekst.
  //display.clearDisplay();
  display.println(steps); // Skriver antall tekst ut til skjermen.
  display.display();  // Det som faktisk viser alt vi har gjort til nå på skjermen.

}
