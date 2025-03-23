#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

void setupAnalogSensor();
void loopAnalogSensor(); // Declare the function
float getFilteredValue();
void getFilteredValueAsCharArray(char* buffer);

#endif
