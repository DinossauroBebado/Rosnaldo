

// ---------------------------------------------------------------------------------------
// Library for the easy development off robots with multiple VL43L0X distance sensor 
// Recevies the pins with the Xshut pins and return a struct with each reading
// ---------------------------------------------------------------------------------------
#include <Arduino.h>
#include <Adafruit_VL53L0X.h>
#include <Wire.h>



typedef struct{
    Adafruit_VL53L0X *psensor;
    int adress;
    int shutPin;
}Sensor_info;


class Distance
{
private:
  /* data */
public:
  Distance(int nSensor,int xShut, Adafruit_VL53L0X sensors);

  int COUNT_SENSORS ;
  Adafruit_VL53L0X SENSORS[] ;
  int XSHUT[] ;
  Sensor_info sensores[];/
  

  void begin();
  int * readSensor(bool debug);

};

