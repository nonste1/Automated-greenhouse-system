/*
	sensor.h
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/



#include "I2CDevice.h"

namespace exploringBB {

    typedef struct {
        float temperature;
        float humidity;
    } sensorData;

    class HIH8120 : public I2CDevice {
    public:
        HIH8120();
        sensorData readData();
    };
}