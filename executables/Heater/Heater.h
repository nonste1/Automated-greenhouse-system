/*
	Heater.h
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct heaterData heaterData;
typedef heaterData* Heater;

Heater initHeater(char *name, char *path);
void setHeater(Heater heater, int value);
void activateHeater(Heater heater, int bool);