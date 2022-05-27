#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X right = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test.");
  if (!right.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power
  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));

  // start continuous ranging
  right.startRangeContinuous();
}

void loop() {
  if (right.isRangeComplete()) {
    Serial.print("Distance in mm: ");
    Serial.println(right.readRange());
  }
}