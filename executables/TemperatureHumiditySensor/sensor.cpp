/*
	sensor.cpp
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/


#include "sensor.h"
#include<unistd.h>



#define ADDRESS 0x27

#include <bitset>

using namespace exploringBB;

HIH8120::HIH8120() : I2CDevice(2, ADDRESS)
{}

sensorData HIH8120::readData()
{
    // Request data
    write(0);

    usleep(40000);

    unsigned char *values;

    values = readDevice(4);

    sensorData record;

    int humidity = 0;
    //take the 6 most significant bit from Data Byte and left shift to 8 positions
    humidity |= (values[0] & 0b00111111) << 8;
    //read Data Byte 2 (most 8 significant bits of humidity)
    humidity |= values[1];
    //calculate the humidity according to formula
    record.humidity = (float)100*(float)humidity/((float)((1<<14) - 2));

    int temperature = 0;
    //the first part of the temperature data
    temperature |= values[2] << 6;
    //right shift because the first two LSB are empty
    temperature |= values[3] >> 2;
    //calculate temperature from formula:
    record.temperature = (float)temperature/((float)((1<<14) - 2))*(float)165 - 40;

    delete[] values;

    return record;
}

