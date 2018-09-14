#! /usr/bin/python

import rospy
from Jetson.msg import blkData
from Jetson.msg import toCam
from Jetson.msg import bot
import time
import run

pub = rospy.Publisher('blockColors', blkData, queue_size=10)

def callbackD(data):
	print("Request Received to the Camera Node for Location:",data)
	#Process the Data depending upon the Location
	x,y,z=run.give_one_letter()
	msg = blkData()
	msg.mode = 1
	msg.pos1 = x
	msg.pos2 = y
	msg.pos3 = z
	pub.publish(msg)



def listener():
	rospy.init_node("CamNode",anonymous=True)
	rospy.Subscriber("camTopic",toCam,callbackD)

	while not rospy.is_shutdown():
		rospy.spin()

if __name__ == "__main__":
	listener()          #Run the Listener Node
