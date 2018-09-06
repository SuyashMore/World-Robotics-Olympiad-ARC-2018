#!/usr/bin/env python

import serial
import time
import constants

ser = serial.Serial(constants.ttyUSB_LIDAR,constants.LIDAR_BAUD)
ser.timeout = 0.001
start = time.time()
itr = 0;

while True:
	if(time.time()-start)>=1:
		start=time.time()
		# print("Reading Rate:",itr)
		itr=0
	dist = ser.readline()
	if(len(dist) > 0):
		itr+=1
		print(dist)