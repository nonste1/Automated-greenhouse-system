/*
	mainSensor.cpp
	Author: Stefano Gregis 329936 Giorgio Ajmone 329846
	Date: 15/11/2022
*/

#include "sensor.h"
#include <iostream>


using namespace std;

using namespace exploringBB;

int main()
{
    HIH8120 s = HIH8120();
    sensorData r = s.readData();
    cout << r.humidity << " " << r.temperature << endl;
}
