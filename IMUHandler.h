
#ifndef IMUHANDLER_H
#define IMUHANDLER_H

#include <MTi.h>
#include <Wire.h>

// IMU Function Prototypes
void IMUsetUp();
bool IMUgetData(float* acc, float* rot, float* euler); // Fetch IMU data

// ISR
void dataReadyISR();

#endif
