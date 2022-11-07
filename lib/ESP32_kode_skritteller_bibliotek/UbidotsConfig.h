#ifndef UbidotsConfig_h
#define UbidotsConfig_h

const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds
char *DEVICE_LABEL = "pedometer1";   // Put here your Device label to which data  will be published
char *VARIABLE_LABEL = "steps"; // Put here your Variable label to which data  will be published

const char * SUB_VARIABLE_LABEL [] = {"start_comptetition","start"};
const int SUB_VARIABLE_LABEL_LENGTH=sizeof(SUB_VARIABLE_LABEL)/sizeof(SUB_VARIABLE_LABEL[0]);

#endif