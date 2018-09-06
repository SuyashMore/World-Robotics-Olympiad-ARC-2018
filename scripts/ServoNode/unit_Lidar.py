#!/usr/bin/env python

import serial
import constants

ser = serial.Serial(constants.ttyUSB_LIDAR,constants.LIDAR_BAUD)

while True:
    print(ser.readline())