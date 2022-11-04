#ifndef secrets_h
#define secrets_h

const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds
char *DEVICE_LABEL = "pedometer_1";   // Put here your Device label to which data  will be published
char *VARIABLE_LABEL = "steps"; // Put here your Variable label to which data  will be published

const char * SUB_VARIABLE_LABEL [] = {"start_comptetition","start"};
const int SUB_VARIABLE_LABEL_LENGTH=sizeof(SUB_VARIABLE_LABEL)/sizeof(SUB_VARIABLE_LABEL[0]);


const char *UBIDOTS_TOKEN = "";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "";      // Put here your Wi-Fi password


#endif
