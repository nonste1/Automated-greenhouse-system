/*
	servo.h
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct servoData servoData;
typedef servoData* Servo;

Servo initServo(char *name, int period, char *path);
void setServo(Servo servo, int value);
void activateServo(Servo servo, int bool);