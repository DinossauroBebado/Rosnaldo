#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <Arduino.h>

#include <Main/config.h>
#include <RotaryEncoder.h>
#define LOOP_TIME        200000  
#define CANAL_R  0
#define CANAL_L  1
#define PWM_MIM 150
#define PWM_MAX 1023
#define SATURATION 1020


unsigned int counter_left=0;
unsigned int counter_right = 0;
float radius = RADIUS; //wheel radius
float pi = 3.1415;
float L =DISTANCE; //distance between wheels

bool _connect = false ;

RotaryEncoder encoderRight(ENCODERRA, ENCODERRB);
RotaryEncoder encoderLeft(ENCODERLA, ENCODERLB);


ros::NodeHandle  nh;
std_msgs::Float32 left_wheel_vel;
ros::Publisher left_wheel_vel_pub("/left_wheel_velocity", &left_wheel_vel);

std_msgs::Float32 right_wheel_vel;
ros::Publisher right_wheel_vel_pub("/right_wheel_velocity", &right_wheel_vel);

geometry_msgs::Twist sensor_vel;
ros::Publisher sensor_vel_pub("/sensor_velocity", &sensor_vel);

bool rosConnected(){
    bool connected = nh.connected();
    if(_connect != connected){
        _connect = connected;
        digitalWrite(LED_BUILD_IN,!connected);
    }
    return connected;
}



 void timerIsr()
{
    //stop the timer
  //Left Motor Speed 
  left_wheel_vel.data = float(counter_left)*2*5/8;
  left_wheel_vel_pub.publish(&left_wheel_vel);
  right_wheel_vel.data = float(counter_right)*2*pi*5/8;
  right_wheel_vel_pub.publish(&right_wheel_vel);
  sensor_vel.linear.x = radius*(left_wheel_vel.data + right_wheel_vel.data)/2;
  sensor_vel.linear.y = 0;
  sensor_vel.linear.z = 0;
  sensor_vel.angular.x = 0;
  sensor_vel.angular.y = 0;
  sensor_vel.angular.z = radius*(left_wheel_vel.data + right_wheel_vel.data)/L;
  sensor_vel_pub.publish(&sensor_vel);
  counter_right=0;
  counter_left=0;
 
}
 
//recieve comands already for each wheel 
void cmdLeftWheelCB( const std_msgs::Int16& msg)
{
  if(msg.data >= 0)
  {
    
    ledcWrite(CANAL_L,msg.data);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);  
  }
  else
  {
    ledcWrite(CANAL_L,-msg.data);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }
}

void cmdRightWheelCB( const std_msgs::Int16& msg)
{
  
  if(msg.data >= 0)
  {
    ledcWrite(CANAL_R,msg.data);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);  
  }
  else
  {
     ledcWrite(CANAL_R,msg.data);
     digitalWrite(BIN1, HIGH);
     digitalWrite(BIN2, LOW);
  }
}

void stop(){
    digitalWrite(AIN1,LOW);
    digitalWrite(AIN2,LOW);
    digitalWrite(BIN1,LOW);
    digitalWrite(BIN2,LOW); 

    ledcWrite(CANAL_L,0);
    ledcWrite(CANAL_R,0);
}

ros::Subscriber<std_msgs::Int16> subCmdLeft("cmd_left_wheel", cmdLeftWheelCB );
ros::Subscriber<std_msgs::Int16> subCmdRight("cmd_right_wheel",cmdRightWheelCB );

//receive the twsit msg and figure out the speed of each wheel 
void cmdVelCB( const geometry_msgs::Twist& twist)
{
  int gain = 900;
  float left_wheel_data = gain*(twist.linear.x - twist.angular.z*L);
  float right_wheel_data = gain*(twist.linear.x + twist.angular.z*L);
  if(left_wheel_data >= 0)
  { 
    ledcWrite(CANAL_L,abs(left_wheel_data));
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);  
  }
  else
  {
    ledcWrite(CANAL_L,abs(left_wheel_data));
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }
  if(right_wheel_data >= 0)
  {
    ledcWrite(CANAL_R,abs(right_wheel_data));
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);  
  }
  else
  {
     ledcWrite(CANAL_R,abs(right_wheel_data));
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
}
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", cmdVelCB);


void setup() {
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


  //Setup for encoders
 
 
  
  nh.initNode();
  nh.subscribe(subCmdRight);
  nh.subscribe(subCmdLeft);
  nh.subscribe(subCmdVel);
  nh.advertise(left_wheel_vel_pub);
  nh.advertise(right_wheel_vel_pub);
  nh.advertise(sensor_vel_pub);

}

void loop() 
{
     if(!rosConnected())
        stop();
    
    //encoder
  
    encoderRight.tick();
    //invert because the gear spin contrary to the wheel so if the wheel goes forward the encoder goes backwards 
    int counter_right = -encoderRight.getPosition();
   
   
    encoderLeft.tick();
    int counter_left = -encoderLeft.getPosition();
   
    

    left_wheel_vel.data = float(counter_left)*((2*pi*RADIUS)/TICKS);
    left_wheel_vel_pub.publish(&left_wheel_vel);
    right_wheel_vel.data = float(counter_right)*((2*pi*RADIUS)/TICKS);
    right_wheel_vel_pub.publish(&right_wheel_vel);
    sensor_vel.linear.x = radius*(left_wheel_vel.data + right_wheel_vel.data)/2;
    sensor_vel.linear.y = 0;
    sensor_vel.linear.z = 0;
    sensor_vel.angular.x = 0;
    sensor_vel.angular.y = 0;
    sensor_vel.angular.z = radius*(left_wheel_vel.data + right_wheel_vel.data)/L;
    sensor_vel_pub.publish(&sensor_vel);
    counter_right=0;
    counter_left=0;
    nh.spinOnce();

}



