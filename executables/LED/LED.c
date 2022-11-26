/*
	LED.c
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/



#include "LED.h"


struct ledData{ char name[10]; char path[50]; };

//writes on the file based on the given path
void setDriver(int time, char *path){
    FILE *p;
    if((p = fopen(path,"w")) == NULL)
        exit(1);

    fprintf(p, "%d", time);
    fclose(p);
}
//checks the mode and if not exported it exports the pin
void initialization(LED led){
    FILE *p;
    char mode[9];

    char path[50] = "/sys/devices/platform/ocp/ocp:";
    strcat(strcat( path, led->name), "_pinmux/state");

    char command[50] = "config-pin ";
    strcat(strcat( command, led->name), " pwm");

    if((p = fopen(path,"r")) == NULL)
        exit(1);

    fscanf(p, "%s", mode);
    if (strcmp(mode,"pwm") != 0)
        system(command);

    if((p = fopen(led->path,"r")) == NULL)
        setDriver(0, strcat(strncpy(path, led->path, 23), "/export"));

    fclose(p);
}
//creates the abstract data structure and returns the pointer
LED initLED(char *name, int period, char *path){
    LED led = malloc(sizeof(struct ledData));
    char pathTot[50];

    strcpy(led->name, name);
    strcpy(led->path, path);

    strcat(strcpy(pathTot, led->path), "/period");
    initialization(led);
    setDriver(period, pathTot);
    return led;
}
//modifies the duty cycle
void setLED(LED led, int value){
    char path[50];
    strcat(strcpy(path, led->path), "/duty_cycle");
    setDriver(value, path);
}
// enables the pin
void activateLED(LED led, int bool) {
    char path[50];
    strcat(strcpy(path, led->path), "/enable");
    setDriver(bool, path);
}

