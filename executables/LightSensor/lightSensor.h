/*
	lightSensor.h
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct lightSensorData lightSensorData;
typedef lightSensorData* LightSensor;

LightSensor initLightSensor( char *path);
int readLightSensor(LightSensor lightSensor);
