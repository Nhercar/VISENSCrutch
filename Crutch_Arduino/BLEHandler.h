#ifndef BLEHANDLER_H
#define BLEHANDLER_H

#include <ArduinoBLE.h>

// BLE Function Prototypes
bool setupBleMode();
void handleBLE(float* acc, float* rot, float* euler );
void updateForce(float update);

#endif
