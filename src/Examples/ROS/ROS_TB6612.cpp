//import the pin out from the eletronics 
#include "config.h"
//hardware control 
#include <Arduino.h>
//ROS-----
#include <ros.h>
#include <std_msgs/Float32.h>

#define CANAL_R  0
#define CANAL_L  1


ros::NodeHandle nh;

void controlWheel( const std_msgs::Float32 &wheel_power,
                   unsigned int channel,
                   unsigned int in_one,
                   unsigned int in_two)
    {
        float factor = wheel_power.data ;

        if(factor > 1){
            factor = 1; 
        }
        if(factor < -1){
            factor = -1; 
        }

        if(factor>=0){
            //frente
            digitalWrite(in_one,LOW);
            digitalWrite(in_two,HIGH);
            ledcWrite(channel,1023*factor);
        }else{
            // tras
            digitalWrite(in_one,HIGH);
            digitalWrite(in_two,LOW);
            ledcWrite(channel,-1023*factor);
        }
        

    }

void rightWheel(const std_msgs::Float32 &wheel_power){
        controlWheel(wheel_power,CANAL_R,AIN1,AIN2);
        
}
void leftWheel(const std_msgs::Float32 &wheel_power){
        controlWheel(wheel_power,CANAL_L,BIN1,BIN2);
        
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
ros::Subscriber<std_msgs::Float32> sub_left("wheel_power_left",&leftWheel);
ros::Subscriber<std_msgs::Float32> blink_sub("blink",&blink);


void setup(){
  pinMode(PWMA, OUTPUT);//Definimos os pinos  como saída.
  pinMode(PWMB, OUTPUT);
  
  ledcAttachPin(PWMA, CANAL_R);//Atribuimos o pino PWMA ao canal 0.
  ledcAttachPin(PWMB, CANAL_L);//Atribuimos o pino PWMB ao canal 1.
  ledcSetup(CANAL_R, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.
  ledcSetup(CANAL_L, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.

  //-------------DIGITAL------------------

  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  
  pinMode(LED_BUILD_IN,OUTPUT);

  nh.initNode();
  nh.subscribe(sub_right);
  nh.subscribe(sub_left);
  nh.subscribe(blink_sub);

}

void loop(){
    
    nh.spinOnce();

}