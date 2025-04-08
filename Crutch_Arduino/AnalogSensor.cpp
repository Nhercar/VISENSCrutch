#include "AnalogSensor.h"
#include "BLEHandler.h"
#include <SimpleTimer.h>
#include <cstring> // For memcpy

// Analog Sensor Variables
const int ANALOG_PIN = A0;          // Analog pin for the pressure sensor
const int filterFactor = 10;        // Number of samples to average for 50Hz filtering
volatile float filteredValue = 0;   // Filtered value
volatile int sampleCount = 0;       // Number of samples accumulated
volatile float accumulatedValue = 0; // Sum of samples for averaging

// SimpleTimer instance
SimpleTimer timer;

// ISR-like function for analog sampling
void sampleISR() {
  int rawValue = analogRead(ANALOG_PIN);  // Read the analog sensor
  accumulatedValue += rawValue;          // Accumulate the raw value
  sampleCount++;

  if (sampleCount >= filterFactor) {
    // Compute the filtered value
    filteredValue = accumulatedValue / sampleCount;
    updateForce(filteredValue);
    // Reset accumulator and counter
    accumulatedValue = 0;
    sampleCount = 0;
  }
}

void setupAnalogSensor() {
  pinMode(ANALOG_PIN, INPUT);

  // Set up the timer for 250Hz sampling (4ms interval)
  timer.setInterval(4, sampleISR); // Interval in milliseconds
}

void loopAnalogSensor() {
  // Call the timer's `run()` function to execute scheduled tasks
  timer.run();
}

float getFilteredValue() {
  // Return the latest filtered value
  return filteredValue;
}

void getFilteredValueAsCharArray(char* buffer) {
  // Convert the filtered value to a 12-byte char array
  if (buffer) {
    memset(buffer, 0, 4);                       // Zero out the buffer
    memcpy(buffer, (const void*)&filteredValue, sizeof(float)); // Explicit cast
  }
}
