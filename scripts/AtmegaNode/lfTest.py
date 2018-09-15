#! /usr/bin/python

import rospy
from Jetson.msg import Vector5
import time


pub = rospy.Publisher('slowLf', Vector5, queue_size=10)


def listener():
	a0 = float(raw_input("Enter x:"))
	a1 = float(raw_input("Enter y:"))
	a2 = float(raw_input("Enter z:"))
	# a3 = float(raw_input("Enter u:"))
	# a4 = float(raw_input("Enter v:"))

	msg = Vector5()
	msg.x=a0
	msg.y=a1
	msg.z=a2
	# msg.u=a3
	# msg.v=a4
	rospy.init_node('debug_Lf_talker', anonymous=True)
	time.sleep(2)

	while not rospy.is_shutdown():
		msg = Vector5()
		msg.x=a0
		msg.y=a1
		msg.z=a2
		# msg.u=a3
		# msg.v=a4
		pub.publish(msg)
		rospy.spin()





if __name__ == "__main__":
	listener()          #Run the Listener Node
