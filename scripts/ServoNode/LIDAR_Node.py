#!/usr/bin/env python

import serial
import constants
import rospy
from std_msgs.msg import Int16


ser = serial.Serial(constants.ttyUSB_LIDAR,constants.LIDAR_BAUD)


def talker():
    pub = rospy.Publisher('LIDAR',Int16,queue_size=100)
    rospy.init_node('',anonymous=True)
    rate = rospy.Rate(100)
    while not rospy.is_shutdown():
        data = int(ser.readline())
        pub.publish(data)
        rate.sleep()

if __name__ == "__main__":
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
