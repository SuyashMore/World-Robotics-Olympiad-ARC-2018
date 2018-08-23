#! /usr/bin/python

import rospy
from Jetson.msg import Angles
from Jetson.msg import Position
from Jetson.msg import ControlSignal
from Jetson.msg import CtrlSigResponse

import super_servo_functions as super 	#import the Servo Controller File


#handles the Angle Input
def callbackAngle(data):
	rospy.loginfo("Angles Received are %d , %d , %d , %d , %d , %d ." % (data.a0,data.a1,data.a2,data.a3,data.a4,data.aGrip) )

#handle the Inverse Kinematic data Input
def callbackPos(data):
	rospy.loginfo("Position Received are %d , %d , %d ." (data.x,data.y,data.z))


def listener():
	rospy.init_node("Dynamixel_listener",anonymous=True)
	rospy.Subscriber("Servo_Angles",Angles,callbackAngle)
	rospy.Subscriber("Servo_Position",Position,callbackPos)

	rospy.spin()

if __name__ == "__main__":
	# super.init()	#Enable the AX-12 Communication Line 
	# super.enableAll()	#Enable Torque Control on All Servo Motors
	listener()			#Run the Listener Node