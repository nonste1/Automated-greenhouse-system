/*
	servo.c
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/


#include "servo.h"

#define DUTY_CYCLE_ON 2350000
#define DUTY_CYCLE_OFF 1460000

struct servoData{ char name[10]; char path[50]; };
//access the file provided as parameter and change the value
void setDriver(int time, char *path){
    FILE *p;
    if((p = fopen(path,"w")) == NULL)
        exit(1);

    fprintf(p, "%d", time);
    fclose(p);
}
//check whether the pin is in pwm mode or not and eventually export it
void initialization(Servo servo){
    FILE *p;
    char mode[9];

    char path[50] = "/sys/devices/platform/ocp/ocp:";
    strcat(strcat( path, servo->name), "_pinmux/state");

    char command[50] = "config-pin ";
    strcat(strcat( command, servo->name), " pwm");

    if((p = fopen(path,"r")) == NULL)
        exit(1);

    fscanf(p, "%s", mode);
    if (strcmp(mode,"pwm") != 0)
        system(command);

    if((p = fopen(servo->path,"r")) == NULL)
        setDriver(0, strcat(strncpy(path, servo->path, 23), "/export"));

    fclose(p);
}
//allocate memory and crate the abstract structure
Servo initServo(char *name, int period, char *path){
    Servo servo = malloc(sizeof(struct servoData));
    char pathTot[50];

    strcpy(servo->name, name);
    strcpy(servo->path, path);

    strcat(strcpy(pathTot, servo->path), "/period");
    initialization(servo);
    setDriver(period, pathTot);
    return servo;
}
//set the duty cycle based on the angle
void setServo(Servo servo, int value){
    char path[50];
    strcat(strcpy(path, servo->path), "/duty_cycle");
    setDriver(value * (DUTY_CYCLE_ON-DUTY_CYCLE_OFF) / 180 + DUTY_CYCLE_OFF, path);
}
//activate the servo
void activateServo(Servo servo, int bool) {
    char path[50];
    strcat(strcpy(path, servo->path), "/enable");
    setDriver(bool, path);
}

