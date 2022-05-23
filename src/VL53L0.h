#include <Adafruit_VL53L0X.h>
#include <Wire.h>
#include <Arduino.h>

// Define which Wire objects to use, may depend on platform
// or on your configurations.
#define SENSOR1_WIRE Wire
#define SENSOR2_WIRE Wire
#if defined(WIRE_IMPLEMENT_WIRE1)
#define SENSOR3_WIRE Wire1

#else
#define SENSOR3_WIRE Wire

#endif



typedef struct {
  Adafruit_VL53L0X *psensor; // pointer to object
  TwoWire *pwire;
  int id;            // id for the sensor
  int shutdown_pin;  // which pin for shutdown;
  int interrupt_pin; // which pin to use for interrupts.
  Adafruit_VL53L0X::VL53L0X_Sense_config_t
      sensor_config;     // options for how to use the sensor
         // range value used in continuous mode stuff.
  uint8_t sensor_status; // status from last ranging in continuous.
} sensorList_t;

// Actual object, could probably include in structure above61
Adafruit_VL53L0X sensor1;
Adafruit_VL53L0X sensor2;
Adafruit_VL53L0X sensor3;

// Setup for 4 sensors
sensorList_t sensors[] = {

    {&sensor1, &SENSOR1_WIRE, 0x30, 21, 1,
     Adafruit_VL53L0X::VL53L0X_SENSE_LONG_RANGE, 0},
    {&sensor2, &SENSOR2_WIRE, 0x31, 19, 3,
     Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_SPEED, 0},
    {&sensor3, &SENSOR3_WIRE, 0x32, 18, 5,
     Adafruit_VL53L0X::VL53L0X_SENSE_DEFAULT, 0 }

};

const int COUNT_SENSORS = sizeof(sensors) / sizeof(sensors[0]);

const uint16_t ALL_SENSORS_PENDING = ((1 << COUNT_SENSORS) - 1);
uint16_t sensors_pending = ALL_SENSORS_PENDING;
uint32_t sensor_last_cycle_time;

void timed_async_read_sensors() ;

void Initialize_sensors();