/*
	mainLED.c
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/


#include "LED.h"

#define maxTime 2000000

int percentageToTime (int percentage){
    return ( maxTime / 100 * percentage);
}

int main( int argc, char *argv[]){
    int value;
    LED led;
    if(argc != 2){
        printf("Parameters missing \n");
        exit(1);
    }

    value = atoi(argv[1]);
    if (value < 0 || value > 100){
        printf("The parameter is not within the accepted range \n");
        exit(1);
    }

    led = initLED("P9_22", 20000000, "/sys/class/pwm/pwmchip1/pwm-1:0");
    setLED(led, percentageToTime(value));
    activateLED(led, 1);

    return 0;
}
