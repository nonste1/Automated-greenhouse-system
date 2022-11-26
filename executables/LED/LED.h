/*
	LED.h
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ledData ledData;
typedef ledData* LED;

LED initLED(char *name, int period, char *path);
void setLED(LED led, int value);
void activateLED(LED led, int bool);