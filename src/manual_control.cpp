#include "ros/ros.h"
#include <sensor_msgs/Joy.h>
#include <mavros_msgs/OverrideRCIn.h>
#include <mavros_msgs/Mavlink.h>
#include <mavros_msgs/RCIn.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros/ActuatorControl.h>
#include <iostream>

// Motor Configuration
// FRONT
//
//(1)---(2)
//---------
//(3)---(4)
//---------
//(5)---(6)
//
// BACK

float motor1;
float motor2;
float motor3;
float motor4;
float motor5;
float motor6;

enum MODE
{
	HOLD
	FORWARD
	REVERSE
	ROTATE_LEFT
	ROTATE_RIGHT
	TO_SURFACE
	TO_FLOOR
}
MODE current_mode = HOLD;
double start_time;

using namespace std;

void joystick_callback(const sensor_msgs::Joy& msg)
{
		
	}

int main(int argc, char **argv)
{
	//start Manual Control Node
	ros::init(argc, argv, "manual_control");
	ros::NodeHandle n;
	start_time = ros::Time::now().toSec();
	
	//subscribe to Joystick
	ros::Subscriber joystick_input = n.subscribe("/sensor_msgs/Joy", 10, joystick_callback);
	
	//define Joystick Controls
	
	//publish to Mavros Actuator Controls
	ros::Publisher actuator_controls_pub = nh.advertise<mavros::ActuatorControl>("/mavro/actuator_controls", 1000);
	mavros_msgs::OverrideRCIn MAV_MSG;
	ros::Rate loop_rate(10);
	
	while(ros::ok())
	{
		mavros::ActuatorControl actuator+control_msg;
		nh.param<float>
	}
	return 0;
}
