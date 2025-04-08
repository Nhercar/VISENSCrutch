//At least the following hardware connections are required:

// PinMTi-DevBoard - CableColour - ArduinoPin 
//MTi_SCL - 9 - Amarillo - Arduino_A5 
//MTi_SDA - 11 - Naranja - Arduino_A4 
//MTi_GND  - 24 - Gris - Arduino_GND 
//MTi_3.3V - 1 - Rojo - Arduino_3.3V 
//MTi_DRDY - 15 - Blanco - Arduino_D3 

//Additionally, make sure to:
//  -Enable I2C by switching PSEL0,1 to "1"
//  -Supply the MTi-#-DK with 3.3V (since 5V will force USB mode)
//  -Add 2.7 kOhm pullup resistors to the SCL/SDA lines (only for MTi-#-DK board Rev 2.3 or older - newer revisions come with onboard pullup resistors)



#include "IMUHandler.h"
#include "BLEHandler.h"
#include "AnalogSensor.h"

// IMU Data Buffers
float acc[3] = {0};
float rot[3] = {0};
float euler[3] = {0};

char forceSensor[12] = {0};

void setup() {
  Serial.begin(9600);

  // Initialize IMU
  IMUsetUp();

  // Initialize BLE
  if (setupBleMode()) {
    Serial.println("Bluetooth initialized");
  } else {
    Serial.println("Bluetooth initialization failed");
  }

  // Initialize Analog Sensor
  setupAnalogSensor();
}

void loop() {
  // Fetch IMU data and handle BLE notifications
  if (IMUgetData(acc, rot, euler)) {
    handleBLE(acc, rot, euler);
  }

  // Run the analog sensor sampling loop
  loopAnalogSensor(); // Ensure this is declared in AnalogSensor.h
}
