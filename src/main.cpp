#include <Arduino.h>
#include <VL53L0.h> 


// ----------------------------------------
// Example code for how to use the lib for the VL53L0X distance sensor
// ----------------------------------------


//fazer uma lista com os objetos dos sensores 
//passar essa lista pra classe 
//encapsular tudo 


//retornar a lista de distancias 



void setup(){
  Serial.begin(115200);
  Wire.begin();
  // wait until serial port opens ... For 5 seconds max
  while (!Serial && millis() < 5000)
    ;

  pinMode(13, OUTPUT);

  // initialize all of the pins.
  Serial.println(F("VL53LOX_multi start, initialize IO pins"));
  for (int i = 0; i < COUNT_SENSORS; i++) {
    pinMode(sensors[i].shutdown_pin, OUTPUT);
    digitalWrite(sensors[i].shutdown_pin, LOW);

    if (sensors[i].interrupt_pin >= 0)
      pinMode(sensors[i].interrupt_pin, INPUT_PULLUP);
  }
  Serial.println(F("Starting..."));
  Initialize_sensors();

}

void loop(){

    timed_async_read_sensors();

    delay(50);
}