//import the pin out from the eletronics 
#include "config.h"
//hardware control 
#include <Arduino.h>
//ROS-----
#include <ros.h>
#include <std_msgs/Float32.h>

#define CANAL_A  0
#define CANAL_B  1


ros::NodeHandle nh;

void controlWheel( const std_msgs::Float32 &wheel_power,
                   unsigned int pwm_pin,
                   unsigned int in_one,
                   unsigned int in_two)
    {
        float factor = max(min(wheel_power.data,1.0f),-1.0f);

        if(factor>=0){
            digitalWrite(in_one,HIGH);
            digitalWrite(LED_BUILD_IN,HIGH);
            digitalWrite(in_two,LOW);
            ledcWrite(pwm_pin,1023*factor);


        }
        else{
            digitalWrite(in_one,LOW);
            digitalWrite(in_two,HIGH);
            // ledcWrite(pwm_pin,(unsigned int)(1023*(-1*factor)));

        }

    }

void rightWheel(const std_msgs::Float32 &wheel_power){
<<<<<<< HEAD
        controlWheel(wheel_power,CANAL_A,AIN1,AIN2);
=======
>>>>>>> 47203d9743d31664a276171ae1ca382aaba4018a
        delay(2000);
        digitalWrite(LED_BUILD_IN,LOW);

}

<<<<<<< HEAD
void leftWheel(const std_msgs::Float32 &wheel_power){
        controlWheel(wheel_power,CANAL_B,BIN1,BIN2);
        delay(1000);
        digitalWrite(LED_BUILD_IN,LOW);
        delay(1000);
        digitalWrite(LED_BUILD_IN,HIGH);
        delay(1000);
        digitalWrite(LED_BUILD_IN,LOW);
=======
void blink(const std_msgs::Float32 &wheel_power){
       for(int i =0;i<=wheel_power.data;i++){
        digitalWrite(LED_BUILD_IN,HIGH);
        delay(1000);
        digitalWrite(LED_BUILD_IN,LOW);
        delay(1000);
       }
>>>>>>> 47203d9743d31664a276171ae1ca382aaba4018a


}

ros::Subscriber<std_msgs::Float32> sub_right("wheel_power_right",&rightWheel);
<<<<<<< HEAD
ros::Subscriber<std_msgs::Float32> sub_left("wheel_power_left",&leftWheel);


=======
ros::Subscriber<std_msgs::Float32> sub_left("blink",&blink);
>>>>>>> 47203d9743d31664a276171ae1ca382aaba4018a
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
  nh.subscribe(sub_left);

}

void loop(){
    
    nh.spinOnce();

}