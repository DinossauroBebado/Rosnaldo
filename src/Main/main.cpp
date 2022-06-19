//import the pin out from the eletronics 
#include <config.h>
//hardware control 
#include <Arduino.h>
//ROS-----
#include <ros.h>
#include <std_msgs/Float32.h>

#define CANAL_A  0
#define CANAL_B  1


ros::NodeHandle nh;



void rightWheel(const std_msgs::Float32 &wheel_power){
        delay(2000);
        digitalWrite(LED_BUILD_IN,LOW);

}

void blink(const std_msgs::Float32 &wheel_power){
       for(int i =0;i<=wheel_power.data;i++){
        digitalWrite(LED_BUILD_IN,HIGH);
        delay(1000);
        digitalWrite(LED_BUILD_IN,LOW);
        delay(1000);
       }


}

ros::Subscriber<std_msgs::Float32> sub_right("wheel_power_right",&rightWheel);
ros::Subscriber<std_msgs::Float32> blink_sub("blink",&blink);

void setup(){
  pinMode(PWMA, OUTPUT);//Definimos os pinos  como saída.
  pinMode(PWMB, OUTPUT);
  
  ledcAttachPin(PWMA, CANAL_A);//Atribuimos o pino PWMA ao canal 0.
  ledcAttachPin(PWMB, CANAL_B);//Atribuimos o pino PWMB ao canal 1.
  ledcSetup(CANAL_A, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.
  ledcSetup(CANAL_B, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.

  //-------------DIGITAL------------------

  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(LED_BUILD_IN,OUTPUT);

  nh.initNode();
  nh.subscribe(sub_right);
  nh.subscribe(blink_sub);

}

void loop(){
    
    nh.spinOnce();

}