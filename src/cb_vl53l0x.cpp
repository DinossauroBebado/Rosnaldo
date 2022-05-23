
#include <cb_vl53l0x.h>


Distance::Distance(int nSensor,int xShut, Adafruit_VL53L0X sensors)
{

    int possible_adresses[9] = {
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38
    };

    int COUNT_SENSORS = nSensor; 

    Adafruit_VL53L0X SENSORS_OBJ[nSensor]  = sensors;
    int XSHUT = xShut;

    Sensor_info sensores[COUNT_SENSORS];

    for(int i = 0;i<=COUNT_SENSORS;i++)
    {
        sensores[i] = {SENSORS_OBJ[i],possible_adresses[i],&XSHUT[i]};
    }


}

void Distance::begin()
{   //Shut down everthing 
    for(int i = 0; i<= COUNT_SENSORS;i++)
    {
        digitalWrite(sensores[i].shutPin,LOW);
        delay(10);
    }
    //Wake one by one and init it
    for(int i = 0; i<= COUNT_SENSORS;i++)
    {   digitalWrite(sensores[i].shutPin,HIGH);
        delay(10);
        if(
            !sensores[i].psensor->begin(sensores[i].adress,false,Wire,VL53L0X_SENSE_HIGH_SPEED);
          )
        {
            Serial.println("Failed to Start");
            delay(1000);
            break;
        }   
    }   
}