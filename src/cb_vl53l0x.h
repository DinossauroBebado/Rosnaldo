

// ---------------------------------------------------------------------------------------
// Library for the easy development off robots with multiple VL43L0X distance sensor 
// Recevies the pins with the Xshut pins and return a struct with each reading
// ---------------------------------------------------------------------------------------

#include <Adafruit_VL53L0X.h>
#include <Wire.h>

class Distances
{
private:
   
public:
    
    
    
    
    Adafruit_VL53L0X sensor1;
    Adafruit_VL53L0X sensor2;
    Adafruit_VL53L0X sensor3;
    Adafruit_VL53L0X sensor[3] = {sensor1, sensor2,sensor3};

    Distances::Distances(int nSensor){
      int ranges_mm[nSensor];
      int nSensor = nSensor;
    }
    
    int * readDistances(int nSensor,bool debug);
    void begin(int xShutpinA, int xShutPinB, int xShutpinC);
};
//change xshutPin for a array with the pins 
void Distances::begin(int nSensor,int xShutpinA, int xShutPinB, int xShutpinC)
{   

    int adresses[nSensor] = {0x30,0x31,0x32} ;

    int XShutpin[nSensor] = {xShutpinA,xShutPinB,xShutpinC};

    for(int i; i<=nSensor;i++){
        digitalWrite(XShutpin[i],LOW);
        delay(10);
    }

    for(int i; i<=nSensor;i++){
        digitalWrite(XShutpin[i],HIGH);
        delay(10);
        sensor[i].begin(adresses[i],false,&Wire,Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_SPEED);
    }

     for (int i = 0; i < nSensor; i++) {
      ranges_mm[i] = sensor[i].startRange();
    }
}

int * Distances::readDistances(int nSensor,bool debug){
  int ranges_mm[nSensor];
   
  bool timeouts[nSensor];
  uint32_t stop_times[nSensor];

  
  uint32_t start_time = millis();

  // Tell all sensors to start.
 
 
  for (int i = 0; i < nSensor; i++) {
    ranges_mm[i] = sensor[i].readRangeResult();
    timeouts[i] = sensor[i].timeoutOccurred();
    stop_times[i] = millis();
  }
  
if(debug){
  for (int i = 0; i < nSensor; i++) {
    
    Serial.print(ranges_mm[i], DEC);
    
    if (timeouts[i])
      Serial.print(F("(TIMEOUT) "));
    else
      Serial.print(F("          "));
    start_time = stop_times[i];
  }
  Serial.println();

} 
    return ranges_mm ;
}
