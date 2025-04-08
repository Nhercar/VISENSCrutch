#include "IMUHandler.h"
#include "AnalogSensor.h" // Include to fetch the filtered value


#define DRDY 3
#define ADDRESS 0x6B

// IMU Variables
MTi *MyMTi = NULL;
volatile bool dataReady = false;

// IMU Setup
void IMUsetUp() {
  Wire.begin();
  Wire.setClock(400000);
  pinMode(DRDY, INPUT);

  attachInterrupt(digitalPinToInterrupt(DRDY), dataReadyISR, RISING);

  MyMTi = new MTi(ADDRESS, DRDY);

  if (!MyMTi->detect(1000)) {
    while (1) {}  // Halt if IMU is not detected
  } else {
    MyMTi->goToConfig();
    MyMTi->requestDeviceInfo();
    MyMTi->goToMeasurement();
  }
}

// ISR for IMU data ready
void dataReadyISR() {
  dataReady = true;
}

// Fetch IMU data
bool IMUgetData(float* acc, float* rot, float* euler) {
  if (!dataReady) return false;

  dataReady = false;  // Reset the flag
  MyMTi->readMessages();

  // Populate the arrays with IMU data
  acc[0] = MyMTi->xbus.acc[0];
  acc[1] = MyMTi->xbus.acc[1];
  acc[2] = MyMTi->xbus.acc[2];

  rot[0] = MyMTi->xbus.rot[0];
  rot[1] = MyMTi->xbus.rot[1];
  rot[2] = MyMTi->xbus.rot[2];

  euler[0] = MyMTi->xbus.euler[0];
  euler[1] = MyMTi->xbus.euler[1];
  euler[2] = MyMTi->xbus.euler[2];

 
  return true;
}

