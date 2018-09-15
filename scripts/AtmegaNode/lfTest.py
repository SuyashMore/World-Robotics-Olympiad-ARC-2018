#! /usr/bin/python

import rospy
from Jetson.msg import Vector5f
import time





def listener():
	rospy.init_node('debug_Lf_talker', anonymous=True)
	pub = rospy.Publisher('slowLf', Vector5f, queue_size=10)
	a0 = float(input("Enter x:"))
	a1 = float(input("Enter y:"))
	a2 = float(input("Enter z:"))
	# a3 = float(raw_input("Enter u:"))
	# a4 = float(raw_input("Enter v:"))

	
	time.sleep(2)

	while not rospy.is_shutdown():
		msg = Vector5f()
		msg.x=a0
		msg.y=a1
		msg.z=a2
		# msg.u=a3
		# msg.v=a4
		pub.publish(msg)
		rospy.spin()





if __name__ == "__main__":
	listener()          #Run the Listener Node
