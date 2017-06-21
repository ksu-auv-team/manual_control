#!/bin/bash
sleep 15
sudo chmod a+rw /dev/input/js0
rosparam set joy_node/dev "/dev/input/js0"
rosrun manual_control manual_control
