#include "filter.h"

const int SENSOR_PIN = 34;

// The threshold for my predictive maintenance alarm
// Since max voltage is 4095, 4095^2 is about 16 million. 
// Let's set the alarm threshold at 10 million.
const float ALARM_THRESHOLD = 10000000.0; 

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT); 
  Serial.println("System Booted. Monitoring Vibration Power...");
}

void loop() {
  // Read the physical sensor
  float raw_value = analogRead(SENSOR_PIN); 
  
  // Clean the noise
  float clean_value = apply_low_pass_filter(raw_value);
  
  // Calculate the kinetic energy (Power)
  float current_power = calculate_window_power(clean_value);
  
  // The Anomaly Detector logic
  if (current_power > ALARM_THRESHOLD) {
      Serial.println("======================================");
      Serial.println("🚨 CATASTROPHIC FAILURE IMMINENT 🚨");
      Serial.print("Power Spike Detected: ");
      Serial.println(current_power);
      Serial.println("======================================");
      
      // Freeze the system for 2 seconds so you can see the alarm
      delay(2000); 
  }
  
  // Normal delay to prevent crashing the serial monitor
  delay(50);
}