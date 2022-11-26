/*
	mainLight.c
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/


#include "lightSensor.h"

int main(){
    LightSensor lightSensor = initLightSensor("/sys/bus/iio/devices/iio:device0");
    fprintf(stdout, "%d", readLightSensor(lightSensor));
    return 0;
}
