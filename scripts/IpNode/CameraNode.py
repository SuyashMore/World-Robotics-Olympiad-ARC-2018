#! /usr/bin/python

import rospy
import constants
from Jetson.msg import BlockData
import time


pub = rospy.Publisher('blockColors', BlockData, queue_size=10)

def callbackD(data):
	pickup = data.pickUp
	stack = data.stack
	cordinator = data.cordinator
	mode = data.mode
	print(data)

	msg = bot()
	# msg.nav = True
	pub.publish(msg)



def listener():
	rospy.init_node("CamNode",anonymous=True)
	rospy.Subscriber("camTopic",Angles,callbackAngle)

	while not rospy.is_shutdown():
		rospy.spin()

if __name__ == "__main__":
	listener()          #Run the Listener Node
