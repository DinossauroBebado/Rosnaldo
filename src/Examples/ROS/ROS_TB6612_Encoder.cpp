//import the pin out from the eletronics 
#include "config.h"
//hardware control 
#include <Arduino.h>
#include <RotaryEncoder.h>
//ROS-----
#include <ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
//general use
#include <math.h>
//define motor channels 
#define CANAL_R  0
#define CANAL_L  1
#define PWM_MIM 150
#define PWM_MAX 1023
#define SATURATION 1020
//Encoders 
RotaryEncoder encoderRight(ENCODERRA, ENCODERRB);
RotaryEncoder encoderLeft(ENCODERLA, ENCODERLB);

ros::NodeHandle nh;


// status

//PWM
std_msgs::Float32 leftPwm_msg;
ros::Publisher leftPwmPub("status/left/pwm",&leftPwm_msg);

std_msgs::Float32 rightPwm_msg;
ros::Publisher rightPwmPub("status/right/pwm",&rightPwm_msg);
//Encoder 

std_msgs::Float32 rightEncoderTick_msg;
ros::Publisher  rightEncoderTickPub("status/right/ticks",&rightEncoderTick_msg);

std_msgs::Float32 leftEncoderTick_msg;
ros::Publisher  leftEncoderTickPub("status/left/ticks",&leftEncoderTick_msg);

//rosrun teleop_twist_keyboard teleop_twist_keyboard.py 
// rosrun rosserial_python serial_node.py /dev/ttyUSB0

int valorR = 0;
int newPosR = 0;

int valorL = 0;
int newPosL = 0;

bool _connect = false ;

float mapPwm(float x , float mim, float max){
    return x*(max - mim) + mim ; 
}

//check if the conections is up 
bool rosConnected(){
    bool connected = nh.connected();
    if(_connect != connected){
        _connect = connected;
        digitalWrite(LED_BUILD_IN,!connected);
    }
    return connected;
}



//send comands to H bridge 
// void controlWheel( uint16_t PWM,
//                    int dir,
//                    unsigned int channel,
//                    unsigned int in_one,
//                    unsigned int in_two)
//     {
      

//             //frente
//             digitalWrite(in_one,dir>0);
//             digitalWrite(in_two,dir);
//             ledcWrite(channel,PWM);
//                    // tras
                 

//     }

//break
void stop(){
    digitalWrite(AIN1,LOW);
    digitalWrite(AIN2,LOW);
    digitalWrite(BIN1,LOW);
    digitalWrite(BIN2,LOW); 

    ledcWrite(CANAL_L,0);
    ledcWrite(CANAL_R,0);
}
//receive from ros and send to hardware
void onTwist(const geometry_msgs::Twist &msg){

    if(!_connect){
        //stop
        stop();
        return;
    }

    
    // lazy calc
    // float left = (msg.linear.x - msg.angular.z)/2;
    // float right = (msg.linear.x + msg.angular.z)/2;

    //right calc 
    float right = ((2*msg.linear.x)+(msg.angular.z*DISTANCE))/(2*RADIUS);
    float left = ((2*msg.linear.x)-(msg.angular.z*DISTANCE))/(2*RADIUS);

    //map to pwm range
    uint16_t leftPWM  = mapPwm(fabs(left),PWM_MIM,PWM_MAX);
    uint16_t rightPWM = mapPwm(fabs(right),PWM_MIM,PWM_MAX);

    //make sure anything explode
    if(leftPWM>SATURATION)
        leftPWM = SATURATION;
    if(rightPWM>SATURATION)
        rightPWM = SATURATION;


    

    digitalWrite(AIN1,left<0);
    digitalWrite(AIN2,left>0);
    digitalWrite(BIN1,right<0);
    digitalWrite(BIN2,right>0); 

    ledcWrite(CANAL_L,leftPWM);
    ledcWrite(CANAL_R,rightPWM);

    
}

//blink in case of test 
void blink(const std_msgs::Float32 &wheel_power){
       for(int i =0;i<=wheel_power.data;i++){
        digitalWrite(LED_BUILD_IN,HIGH);
        delay(1000);
        digitalWrite(LED_BUILD_IN,LOW);
        delay(1000);
       }
}

ros::Subscriber<std_msgs::Float32> blink_sub("blink",&blink);
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel",&onTwist);

void setup(){
  //------------motors  
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
  digitalWrite(LED_BUILD_IN,HIGH);
 //-----------ros---------------
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(blink_sub);
  
  nh.advertise(leftPwmPub);
  nh.advertise(rightPwmPub);

  nh.advertise(leftEncoderTickPub);
   nh.advertise(rightEncoderTickPub);
}

void loop(){
    if(!rosConnected())
        stop();
    
    //encoder
  
    static int posR = 0;
    encoderRight.tick();
    //invert because the gear spin contrary to the wheel so if the wheel goes forward the encoder goes backwards 
    int newPosR = encoderRight.getPosition()*-1;
   
    if (posR != newPosR)
    {   rightEncoderTick_msg.data = newPosR;
        rightEncoderTickPub.publish(&rightEncoderTick_msg);
        posR = newPosR;
    }

    static int posL = 0;
    encoderLeft.tick();
    int newPosL = encoderLeft.getPosition()*-1;
   
    if (posL != newPosL)
    {   leftEncoderTick_msg.data = newPosL;
        leftEncoderTickPub.publish(&leftEncoderTick_msg);
        posL = newPosL;
    }
    nh.spinOnce();

}