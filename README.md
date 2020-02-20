# World Robotics Olympiad - Advanced Robotics Challenge 2018

## Team : SRA-VJTI


[Problem Statement](https://github.com/SuyashMore/World-Robotics-Olympiad-ARC-2018/blob/master/WRO-2018-ARC-Tetrastack-game-rule.pdf)

![image](https://github.com/SuyashMore/World-Robotics-Olympiad-ARC-2018/blob/master/Images/IMG_20180915_141652.jpg)


For Installation and Dependencies Follow
 
http://wiki.ros.org/kinetic/Installation/Ubuntu
http://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/overview/
https://docs.opencv.org/3.4/d2/de6/tutorial_py_setup_in_ubuntu.html





Build and Run
```shell
# Catkin Build System on ROS Kinetic to compile Package
catkin_make  

# Package Name : Jetson ("package.xml")
# Run the Folloiwng Commands in Seperate Terminals
rosrun Jetson AtmegaNode
rosrun Jetson DynamixelNode.py
rosrun Jetson CameraNode.py
rosrun rosserial_python serial_node.py #Com with microcontroller
```

Hardware Stack:

[Nvidia Jetson TX2 Developer Kit](https://developer.nvidia.com/embedded/jetson-tx2-developer-kit)

[Atmega-128 microcontroller ](https://www.microchip.com/wwwproducts/en/ATMEGA128)

[DYNAMIXEL AX-12A Smart Servo for Robotic Manipulator](http://www.robotis.us/ax-12a/)


Video:

[![Video](http://img.youtube.com/vi/DvEpwS4OvB4/0.jpg)](https://youtu.be/DvEpwS4OvB4)

