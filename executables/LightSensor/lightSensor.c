/*
	lightSensor.c
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/



#include "lightSensor.h"


#define MIN_VAL 500
#define MAX_VAL 1800

struct lightSensorData {char path[50]; };
//initialize the data structure and allocate the memeory
LightSensor initLightSensor(char *path){
    LightSensor lightSensor = malloc(sizeof(struct lightSensorData));
    strcpy(lightSensor->path, path);
    return lightSensor;
}
// from the value it converts to a percentage rescaling on the range
int valueToPercentage(float value){
    return (int)(100 * (value / (float)(MAX_VAL - MIN_VAL)));
}
//read the values from the file and calls the convertion function
int readLightSensor(LightSensor lightSensor){
    FILE *p;
    float value;
    char path[50];
    strcat(strcpy(path, lightSensor->path), "/in_voltage0_raw");

    if((p = fopen(path,"r")) == NULL)
        exit(1);

    fscanf(p, "%f", &value);

    fclose(p);

    return valueToPercentage(value);
}
