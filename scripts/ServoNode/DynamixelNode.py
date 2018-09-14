#! /usr/bin/python

import rospy
from Jetson.msg import Angles
from Jetson.msg import Position
from Jetson.msg import ControlSignal
from Jetson.msg import CtrlSigResponse
from Jetson.msg import Dyx2
from Jetson.msg import bot
import time

import super_servo_functions as super   #import the Servo Controller File


pickup=False
stack=False
cordinator=False


pub = rospy.Publisher('botData', bot, queue_size=10)

#handles the Angle Input
def callbackAngle(data):
	rospy.loginfo("Angles Received are %d , %d , %d , %d , %d , %d ." % (data.a0,data.a1,data.a2,data.a3,data.a4,data.aGrip) )

#handle the Inverse Kinematic data Input
def callbackPos(data):
	rospy.loginfo("Position Received are %d , %d , %d ." (data.x,data.y,data.z))

def callbackD(data):
	print("Callback Received!")
	global pickup
	global stack
	global cordinator
	pickup = data.pickUp
	stack = data.stack
	cordinator = data.cordinator
	mode = data.mode
	print(data)

	if(mode ==0):
		if(pickup):
			print("Picking Up the Block")
			super.cordinatorDisable()
			super.pickupXYZ()

		if(stack):
			print("Stacking Block")
			super.stackBlock()

		if (not pickup and not stack):
			print("Moving to Standard Position")
			super.move2standard()


		if(cordinator):
			print("Enabling Cordinator !")
			super.move2standard()
			super.cordinatorDisable()
		else:
			print("Disabling Cordinator !")
			super.cordinatorEnable()
	elif mode == 1:
		super.pickupAndPushPos() 			#Add Additional Arm Functions Here
	elif mode == 2:
		super.move2standard()
	elif mode == 11:
		super.disableAll()

	msg = bot()
	msg.nav = True
	pub.publish(msg)



def listener():
	rospy.init_node("Dynamixel_listener",anonymous=True)
	rospy.Subscriber("Servo_Angles",Angles,callbackAngle)
	rospy.Subscriber("Servo_Position",Position,callbackPos)
	rospy.Subscriber("Dyx",Dyx2,callbackD)

	while not rospy.is_shutdown():
		rospy.spin()





if __name__ == "__main__":
	super.init()  #Enable the AX-12 Communication Line 
	super.enableAll() #Enable Torque Control on All Servo Motors
	listener()          #Run the Listener Node
