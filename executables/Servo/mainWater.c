/*
	mainWater.c
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/


#include "servo.h"

int main( int argc, char *argv[]){
    int value;
    Servo servo;
    if(argc != 2){
        printf("Parameters missing \n");
        exit(1);
    }

    value = atoi(argv[1]);
    if (value < 0 || value > 180){
        printf("The parameter is not within the accepted range \n");
        exit(1);
    }

    servo = initServo("P9_42", 20000000, "/sys/class/pwm/pwmchip0/pwm-0:0");
    setServo(servo, value);
    activateServo(servo, 1);

    return 0;
}
