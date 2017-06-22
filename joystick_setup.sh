#!/bin/bash
rosparam set joy_node/dev "/dev/input/js0"
echo "joystick setup"
rosrun joy joy_node
echo "joystick publishing"
