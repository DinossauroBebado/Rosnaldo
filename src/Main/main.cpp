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
        controlWheel(wheel_power,CANAL_A,AIN1,AIN2);
        delay(2000);
        digitalWrite(LED_BUILD_IN,LOW);

}

void leftWheel(const std_msgs::Float32 &wheel_power){
        controlWheel(wheel_power,CANAL_B,BIN1,BIN2);
        digitalWrite(LED_BUILD_IN,LOW);
        delay(1000);
        digitalWrite(LED_BUILD_IN,HIGH);
        delay(1000);
        digitalWrite(LED_BUILD_IN,LOW);
<<<<<<< HEAD
}

void blink(const std_msgs::Float32 &wheel_power){
       for(int i =0;i<=wheel_power.data;i++){
       }
}

ros::Subscriber<std_msgs::Float32> sub_right("wheel_power_right",&rightWheel);
ros::Subscriber<std_msgs::Float32> sub_left("wheel_power_left",&leftWheel);


=======


}

ros::Subscriber<std_msgs::Float32> sub_right("wheel_power_right",&rightWheel);
<<<<<<< HEAD
ros::Subscriber<std_msgs::Float32> blink_sub("blink",&blink);

=======
<<<<<<< HEAD
ros::Subscriber<std_msgs::Float32> sub_left("wheel_power_left",&leftWheel);


=======
ros::Subscriber<std_msgs::Float32> sub_left("blink",&blink);
>>>>>>> 47203d9743d31664a276171ae1ca382aaba4018a
>>>>>>> 56d139a9a32d21b52f1a64ac31ec9cd829231fae
>>>>>>> 05b8d81d11cc11b3ab62d5982a3daab753b272e5
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