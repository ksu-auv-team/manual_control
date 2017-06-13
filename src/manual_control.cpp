#include "ros/ros.h"
#include <ros/console.h>
#include <sensor_msgs/Joy.h>
#include <mavros_msgs/OverrideRCIn.h>
#include <mavros_msgs/Mavlink.h>
#include <mavros_msgs/RCIn.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/ActuatorControl.h>
#include <iostream>
#include <vector>
#include <std_msgs/Float32MultiArray.h>

#define ROLL_CHAN 	0
#define PITCH_CHAN 	1
#define THROT_CHAN 	2
#define YAW_CHAN 	3
#define MODES_CHAN	4

#define HIGH_PWM	2000
#define MID_PWM 	1500
#define LOW_PWM 	1000

using namespace std;

//float axes_input;
float axes_input[8];

ros::Publisher pub_mavros;
//figure out how to call functions from inside of other functions
//float scale(float input){
	//return 500*input+1500;
//}
void joystick_callback(const sensor_msgs::Joy::ConstPtr& msg)
{
	for (int i=0; i < 8; i++)
	{
		axes_input[i] = msg->axes[i];
		ROS_INFO_STREAM("BREAK");
		ROS_INFO_STREAM(axes_input[0]);
		ROS_INFO_STREAM(axes_input[1]);
		ROS_INFO_STREAM(axes_input[2]);
		ROS_INFO_STREAM(axes_input[3]);
		ROS_INFO_STREAM(axes_input[4]);
		ROS_INFO_STREAM(axes_input[5]);
		ROS_INFO_STREAM(axes_input[6]);
		ROS_INFO_STREAM(axes_input[7]);
		ROS_INFO_STREAM(axes_input[8]);
	}
}

/*void up_down()
{
	ros::NodeHandle nh;
	if(axes_input[8] = 0){
		nh.setParam("/chan_5", 0.0);
		nh.setParam("/chan_6", 0.0);
	}
	else if(axes_input[8] = 1){
		nh.setParam("/chan_5", 1.0);
		nh.setParam("/chan_6", 1.0);
	}
	else if(axes_input[8] = -1){
		nh.setParam("/chan_5", -1.0);
		nh.setParam("/chan_6", -1.0);
	}
	else {
		nh.setParam("/chan_5", 0.0);
		nh.setParam("/chan_6", 0.0);
	}
	
}
*/

int main(int argc, char **argv)
{	
	//if need to check status of sub, if it needs to be sent commans write an if statement to send commands of 1500, just like an RC transmitter would
	//start Manual Control Node
	ros::init(argc, argv, "manual_control");
	ros::NodeHandle nh;
	ros::Rate RC_COMM_RATE(45);
	//float chan_5;
	//float chan_6;
	
	//subscribe to Joystick
	ros::Subscriber joystick_input = nh.subscribe("joy", 10, joystick_callback);

	//publish Mavros Actuator Controls
	//ros::Publisher actuator_controls_pub = nh.advertise<mavros_msgs::ActuatorControl>("/mavros/actuator_controls", 1000);
	//ros::Rate loop_rate(10);	

	//use callback function to modify global array to equal array axes
	
	//publish MAV_MSG controls
	pub_mavros = nh.advertise<mavros_msgs::OverrideRCIn>("mavros/rc/override", 1);
	mavros_msgs::OverrideRCIn MAV_MSG;
		
	while(ros::ok())
	{
		//pixhawk ust be in stablize mode
		//pitch is forward back
		//roll is side to side
		//throttle is up down
		
		//set channel equal to value of the joystick and then change it to fit between (1000,2000) for pwm signals
		MAV_MSG.channels[ROLL_CHAN] = ((axes_input[0])*500)+1500;
		MAV_MSG.channels[PITCH_CHAN] = ((axes_input[1])*500)+1500;
		MAV_MSG.channels[THROT_CHAN] = ((axes_input[4])*500)+1500;
		MAV_MSG.channels[YAW_CHAN] = ((axes_input[3])*500)+1500;
		MAV_MSG.channels[MODES_CHAN] = HIGH_PWM;
	
		//Z-axis movement
		//Actuator Controls
		//mavros_msgs::ActuatorControl actuator_control_msg;
		
		// FRONT    INDEXED
		//--2---1--|--1---0--
		//---------|--------
		//--6---5--|--5---4--
		//---------|---------
		//--4---3--|--3---2--
		
		//send initial signal of 0 to MAIN 
		//nh.param<float>("chan_5", chan_5, 0.0);
		//nh.param<float>("chan_6", chan_6, 0.0);		
		
		/*send to control group 0:
        MAIN 1 = 0:roll
        MAIN 2 = 1:pitch
        MAIN 3 = 2:yaw
        MAIN 4 = 3:throttle
        MAIN 5 = 4:flaps
        MAIN 6 = 5:spoilers
        MAIN 7 = 6:airbrakes
        MAIN 8 = 7:landing gear
        see https://pixhawk.ethz.ch/mavlink/#SET_ACTUATOR_CONTROL_TARGET
        and https://pixhawk.org/dev/mixing
        */
        //For Actuator Controls, each main out pin is mapped out from 1-8, indexed from 0-7, and they are named as above
		//actuator_control_msg.header.stamp = ros::Time::now();
		//actuator_control_msg.group_mix = 0;
		//actuator_control_msg.controls[4] = chan_5;
		//actuator_control_msg.controls[5] = chan_6;
		
		//Pixhawk will reject OFFBOARD command unless there are messages being sent
		//actuator_controls_pub.publish(static_input);
		
		pub_mavros.publish(MAV_MSG);
		//actuator_controls_pub.publish(actuator_control_msg);
		ros::spinOnce();
		//loop_rate.sleep();
		RC_COMM_RATE.sleep();
	}
	return 0;
}
