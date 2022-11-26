/*
	mainHeater.c
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/


#include "Heater.h"

int main( int argc, char *argv[]){

    if(argc != 2){
        printf("Parameters missing \n");
        exit(1);
    }
    Heater heater = initHeater("49", "/sys/class/gpio");
    if(!strcmp(argv[1], "on"))
        setHeater(heater, 1);
    if(!strcmp(argv[1], "off"))
        setHeater(heater, 0);
    return 0;
}
