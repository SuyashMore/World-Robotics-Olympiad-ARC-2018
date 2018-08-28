#! /usr/bin/python

import rospy
from Jetson.msg import ControlSignal
from Jetson.msg import CtrlSigResponse
import constants as const

pub = rospy.Publisher('Control_Signals', ControlSignal, queue_size=const.QUEUE_SIZE)

#handles the Command Acknowledge
def cmdCallback(data):
	rospy.loginfo("Response Received from '%s' , Acknowledge = %d" % (data.address,data.acknowledge))


def MasterLoop():
	rospy.init_node("Master_Node",anonymous=True)
	rospy.Subscriber("Ctrl_Sig_Responses",CtrlSigResponse,cmdCallback)

	rospy.spin()

if __name__ == "__main__":
	try:
		MasterLoop()			#Run the Master Node
	except rospy.ROSInterruptException:
		pass


def startPub():
	pass
