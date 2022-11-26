/*
	Heater.c
	Author: Stefano gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/


#include "Heater.h"

struct heaterData{ char name[10]; char path[50]; };

//Writes to a given file a specified value got as a parameter
void setDriver(int time, char *path){
    FILE *p;
    if((p = fopen(path,"w")) == NULL)
        exit(1);

    fprintf(p, "%d", time);
    fclose(p);
}

//Sets the direction of the pin as out
void setDriverMode(char *mode, char *path){
    FILE *p;
    if((p = fopen(path,"w")) == NULL)
        exit(1);

    fprintf(p, "%s", mode);
    fclose(p);
}

//Exports the pin
void initialization(Heater heater){
    FILE *p;
    char mode[9], pathTot[50], command[50];

    sprintf(pathTot, "%s%s%s", heater->path, "/gpio", heater->name);

    if((p = fopen(pathTot,"r")) == NULL)
        setDriver(atoi(heater->name), strcat(strcpy(pathTot, heater->path), "/export"));

    fclose(p);
}

//Allocate the memory and initialize the mode and the direction
Heater initHeater(char *name, char *path){
    Heater heater = malloc(sizeof(struct heaterData));
    char pathTot[50];

    strcpy(heater->name, name);
    strcpy(heater->path, path);

    sprintf(pathTot, "%s%s%s%s", heater->path,"/gpio", heater->name,"/direction");
    
    initialization(heater);
    setDriverMode("out", pathTot);
    return heater;
}

//turn on and off the heater
void setHeater(Heater heater, int value){
    char pathTot[50];
    sprintf(pathTot, "%s%s%s%s", heater->path, "/gpio", heater->name,"/value");
    setDriver(value, pathTot);
}

//enables the pin
void activateHeater(Heater heater, int bool) {
    char path[50];
    strcat(strcpy(path, heater->path), "/enable");
    setDriver(bool, path);
}

