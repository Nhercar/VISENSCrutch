#include "BLEHandler.h"
#include "AnalogSensor.h" // Include to fetch the filtered value


// BLE Variables
BLEService AccService("1000");
BLEStringCharacteristic AccCharacteristic("1010", BLERead | BLENotify, 12);
BLEStringCharacteristic RotCharacteristic("1011", BLERead | BLENotify, 12);
BLEStringCharacteristic EulerCharacteristic("1012", BLERead | BLENotify, 12);
BLEFloatCharacteristic ForceCharacteristic("1013", BLERead | BLENotify);

bool setupBleMode() {
  if (!BLE.begin()) {
    return false;
  }

  BLE.setDeviceName("Crutch");
  BLE.setLocalName("Crutch");
  BLE.setAdvertisedService(AccService);

  // Add IMU characteristics
  AccService.addCharacteristic(AccCharacteristic);
  AccService.addCharacteristic(RotCharacteristic);
  AccService.addCharacteristic(EulerCharacteristic);

  // Add analog sensor characteristic
  AccService.addCharacteristic(ForceCharacteristic);

  BLE.addService(AccService);
  BLE.advertise();

  BLE.setConnectionInterval(6, 10);

  return true;
}

void updateForce(float update){
   ForceCharacteristic.writeValue(update);
}

void handleBLE(float* acc, float* rot, float* euler) {
  static bool wasConnected = false; // Tracks connection status
  BLEDevice central = BLE.central();

  if (central && central.connected()) {
    if (!wasConnected) {
      // Handle new connection event
      Serial.println("BLE Central device connected.");
      wasConnected = true; // Update connection status
    }
    
    // Convert IMU data to 12-byte char arrays


    AccCharacteristic.writeValue((char*)acc);
    RotCharacteristic.writeValue((char*)rot);
    EulerCharacteristic.writeValue((char*)euler);
   

 
    // Fetch the filtered analog value as a char array
    

    // Notify BLE characteristic with filtered analog value
    
  } else {
    if (wasConnected) {
      // Handle disconnection event
      Serial.println("BLE Central device disconnected.");
      wasConnected = false; // Update connection status
      BLE.advertise();      // Start advertising again
    }
  }
}
