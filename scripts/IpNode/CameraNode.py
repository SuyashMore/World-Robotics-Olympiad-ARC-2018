#! /usr/bin/python

import rospy
import constants
from Jetson.msg import BlockData
from Jetson.msg import toCam
import time


pub = rospy.Publisher('blockColors', BlockData, queue_size=10)

def callbackD(data):
	print("Request Received to the Camera Node for Location:",data)
	location = data.location
	#Process the Data depending upon the Location
	# x=
	# y=
	# z=
	

	msg = BlockData()
	msg.mode = 1
	# msg.pos1 = x
	# msg.pos2 = y
	# msg.pos3 = z
	# msg.nav = True
	pub.publish(msg)



def listener():
	rospy.init_node("CamNode",anonymous=True)
	rospy.Subscriber("camTopic",toCam,callbackD)

	while not rospy.is_shutdown():
		rospy.spin()

if __name__ == "__main__":
	listener()          #Run the Listener Node
