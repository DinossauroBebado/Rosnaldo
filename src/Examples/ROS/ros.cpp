/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

// ROS 
// roscore
// rosrun rosserial_python serial_node.py /dev/ttyUSB0
//rostopic pub toggle_led std_msgs/Empty --once

#include <Main/config.h> 
#include<Arduino.h>
#include <ros.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;

void messageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(LED_BUILD_IN, HIGH-digitalRead(LED_BUILD_IN));   // blink the led
}

ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );

void setup()
{ 
  pinMode(LED_BUILD_IN, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}
