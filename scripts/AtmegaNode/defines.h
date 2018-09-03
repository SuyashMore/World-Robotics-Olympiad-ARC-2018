#pragma once

#include<iostream>
#include<sstream>
#include<string>

using namespace std;

// Ros Spin Rate (spins/second)
#define ROS_LOOP_RATE 40
#define LF_THRESH 100
#define LF_MAX 500

// PWM Settings
#define FORWARD_MOTION_PWM 200
#define SPOT_LEFT_PWM 100

// Delays(ms)
#define DELAY_BOT_TURN 1000

// Flag Params
#define TOF_FLAG_MIN_THRESH 20
#define TOF_FLAG_MAX_THRESH 210


// PWM MAP VARs
#define F_MOTOR_MAP_INLOW 0
#define F_MOTOR_MAP_INHIGH 3500
#define F_MOTOR_MAP_OUTLOW 70 
#define F_MOTOR_MAP_OUTHIGH 160

#define B_MOTOR_MAP_INLOW  0
#define B_MOTOR_MAP_INHIGH 3500
#define B_MOTOR_MAP_OUTLOW 50
#define B_MOTOR_MAP_OUTHIGH 160

// TOF Params(cm)
#define TOF_ERROR_THRESH 8
#define BALANCE_WITH_TOF_PWM 100

// UNIT TEST PWM
#define UNIT_PWM  200

// Atmega-Output Message : f0000000b00000000w00s00l0r0t000y000e
#define _1_MESSAGE 'f'
#define _2_MESSAGE 'b'
#define _3_MESSAGE 'w'
#define _4_MESSAGE 's'
#define _5_MESSAGE 'l'
#define _6_MESSAGE 'r'
#define _7_MESSAGE 't'
#define _8_MESSAGE 'y'
#define _9_MESSAGE_END 'e'

// Motor Index
#define MOTOR_FRONT 0
#define MOTOR_RIGHT 1
#define MOTOR_BACK 2
#define MOTOR_LEFT 3


//Atmega-Input Message : D1010P111a222b333c444d
// (Front View of Each Motor:- 
				// 1 (front motor):(clock)/(anti-clock) 
				// 2  (right motor):(clock)/(anti-clock) 
				// 3  (back motor):(clock)/(anti-clock) 
				// 4  (left motor):(anti-clock)/(clock) 
#define _OUTM_DIR "D"
#define _OUTM_PWM "P"
#define _OUT_DELAY "m"
