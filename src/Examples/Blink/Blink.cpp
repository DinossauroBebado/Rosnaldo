#include <Arduino.h>
#include <Main/config.h> 

void setup(){
    pinMode(LED_BUILD_IN,OUTPUT);
    Serial.begin(SERIAL_RATE);

}
void loop(){
    digitalWrite(LED_BUILD_IN,HIGH);
    Serial.println("ON");
    delay(500);
    digitalWrite(LED_BUILD_IN,LOW);
    Serial.println("OFF");
    delay(500);
}