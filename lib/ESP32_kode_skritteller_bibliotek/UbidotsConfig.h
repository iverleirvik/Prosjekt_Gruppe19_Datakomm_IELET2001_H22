#ifndef UbidotsConfig_h
#define UbidotsConfig_h
//#ifndef STR
//#define STR_INDIR(x) #x
//#define STR(x) STR_INDIR(x)
//#define DEVICE_TYPE "pedometer"
//#define DEVICE_NUMBER 1
//#endif
//char *DEVICE_LABEL = DEVICE_TYPE  STR(DEVICE_NUMBER) ;

//------------------------------------------------------

#define DEVICE_LABEL_2 "ESP32"  // Enhetsnavn, nødvendighet fra ubidots.
#define VARIABLE_LABEL_2 "1"    // Variabelnavn som ikke er i bruk
#define VARIABLE_LABEL_3 "2"    // ---------------||--------------

//------------------------------------------------------

const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds. IKKE I BRUK.
char *VARIABLE_LABEL = "steps"; // Put here your Variable label to which data  will be published
int ubidotsStartTimer{100001}; // Verdi som ubidots trenger for å starte event. Må sendes til "3".

const char * SUB_VARIABLE_LABEL [] = {"1", "2", "3"}; //    variabelnavn som er i bruk. Variabel "1" er brukt for å skrittellerne til å publisere sine skritt. Variabel "2" brukes 
const int SUB_VARIABLE_LABEL_LENGTH=sizeof(SUB_VARIABLE_LABEL)/sizeof(SUB_VARIABLE_LABEL[0]);   // av eventet i ubidots til å sende at "Nå er konkurransen over for denne gang" og
                                                                                                // "3 er for å trigge eventet."
#endif

// HER MÅ VI RYDDE