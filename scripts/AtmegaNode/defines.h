#pragma once

#include<iostream>
#include<sstream>
#include<string>

using namespace std;

// Ros Spin Rate (spins/second)
#define ROS_LOOP_RATE 40
#define LF_THRESH 700
#define LF_MAX 7

// PWM Settings
#define FORWARD_MOTION_PWM 200
#define SPOT_LEFT_PWM 100

// Home Position Params
#define HOME_FRONT_X 40
#define HOME_SIDE_X 40
#define HOME_ERROR_THRESH 8

// Delays(ms)
#define DELAY_BOT_TURN 1001

// Flag Params
#define TOF_FLAG_MIN_THRESH 20
#define TOF_FLAG_MAX_THRESH 210

// Side TOF PARAMS

#define WHITE_SPACE_BLOCK_DIST 240
#define WHITE_SPACE_ERROR_THRESH 50

#define SIDE_MIDDLE 615
#define SIDE_1 410
#define SIDE_2 460
#define SIDE_3 560
#define SIDE_4 560
#define SIDE_5 610
#define SIDE_6 660
#define SIDE_7 760
#define SIDE_8 690

#define DIR_LEFT 1
#define DIR_RIGHT 2
#define DIR_NULL 0


// PWM MAP VARs
#define F_MOTOR_MAP_INLOW 0
#define F_MOTOR_MAP_INHIGH 3500
#define F_MOTOR_MAP_OUTLOW 70 
#define F_MOTOR_MAP_OUTHIGH 160

#define B_MOTOR_MAP_INLOW  0
#define B_MOTOR_MAP_INHIGH 3500
#define B_MOTOR_MAP_OUTLOW 70
#define B_MOTOR_MAP_OUTHIGH 160

#define STRAFE_RIGHT_2_MAIN_LINE_PWM 120
#define STRAFE_PICKUP 100
#define SPOT_ROTATE_PWM 100
#define FOLLOW_LINE_BACK_PWM 150

// Iterator Limits
#define PICKUP_1_ITR_MAX 40
#define PICKUP_1_ITR_MAX_2 80
#define PICKUP_2_ITR_MAX 30
#define PICKUP_3_ITR_MAX 30

// Stacking Params
#define TOF_FRONT_BALANCE_DISTANCE 190
#define PULL_AND_PUSH_ITR 90

// Block Params
#define TOF_SIDE_DISTANCE 120
#define DELIVERY_CHUTE_STOP_DISTANCE 200

// TOF Params(cm)
#define TOF_ERROR_THRESH 10
#define TOF_ERROR_THRESH_SIDE 8
#define BALANCE_WITH_TOF_PWM 140

// UNIT TEST PWM
#define UNIT_PWM  200

// Block Shape And Color
#define COLOR_NULL 		6
#define COLOR_RED 		0
#define COLOR_BLUE 		1
#define COLOR_GREEN 	2
#define COLOR_YELLOW 	3
#define COLOR_VIOLET 	4
#define COLOR_ORANGE    5

#define JUDGEPART 0
#define SUPPLY1 1
#define SUPPLY2 2
#define WHITE1 3
#define WHITE2 4
#define WHITE3 5
#define CHUTE 6


int BlockColor[6];    // Judge , Supply1 ,supply 2, white 1,white 2,white 3
int NavigationOrder[20];
int currentNavI=0;
int maxNav = 0;

#define MAX_BLOCKS 2
int TETRASTACK_ORDER[6][4] = 
{	//Main Color - {1,2,3,4,5,6,..}(Block to be Placed In Order)
	{COLOR_BLUE , COLOR_YELLOW , COLOR_ORANGE , COLOR_BLUE },  		//COLOR_RED
	{COLOR_ORANGE , COLOR_BLUE ,COLOR_ORANGE , COLOR_VIOLET }, 		//COLOR_BLUE
	{COLOR_BLUE , COLOR_ORANGE , COLOR_YELLOW , COLOR_BLUE},   		//COLOR_GREEN
	{COLOR_BLUE , COLOR_BLUE , COLOR_YELLOW ,COLOR_NULL },			//COLOR_YELLOW
	{COLOR_YELLOW , COLOR_BLUE , COLOR_VIOLET , COLOR_YELLOW },		//COLOR_VIOLET
	{COLOR_BLUE , COLOR_YELLOW , COLOR_VIOLET , COLOR_YELLOW }		//COLOR_ORANGE
};

int hx_ORDER[6][4] = 
{
	//Main Color - {1,2,3,4,5,6,..}(Block to be Placed In Order)
	{ SIDE_3, SIDE_1 , SIDE_3 , SIDE_8 },  		//COLOR_RED
	{SIDE_2 , SIDE_5 ,SIDE_3 , SIDE_6 }, 		//COLOR_BLUE
	{SIDE_3 , SIDE_7 , SIDE_4 , SIDE_1},   		//COLOR_GREEN
	{SIDE_3 , SIDE_7 , SIDE_3 ,COLOR_NULL },			//COLOR_YELLOW
	{SIDE_3 , SIDE_1 , SIDE_3 , SIDE_6 },		//COLOR_VIOLET
	{SIDE_7 , SIDE_7 , SIDE_7 , SIDE_7 }		//COLOR_ORANGE	
};

int floor_ORDER[6][4] = 
{
	//Main Color - {1,2,3,4,5,6,..}(Block to be Placed In Order)
	{ 1, 1 , 2, 2},  		//COLOR_RED
	{1 ,1 ,2 ,2 }, 		//COLOR_BLUE
	{1 , 1 , 2 , 2},   		//COLOR_GREEN
	{1 , 1 , 2 ,COLOR_NULL },			//COLOR_YELLOW
	{1, 1 , 2 , 2 },		//COLOR_VIOLET
	{SIDE_7 , SIDE_7 , SIDE_7 , SIDE_7 }		//COLOR_ORANGE	

};

int orienatation_ORDER[6][4] = 			//to Modify
{
	//Main Color - {1,2,3,4,5,6,..}(Block to be Placed In Order)
	{ 1, 1 , 2, 2},  		//COLOR_RED
	{1 ,1 ,2 ,2 }, 		//COLOR_BLUE
	{1 , 1 , 2 , 2},   		//COLOR_GREEN
	{1 , 1 , 2 ,COLOR_NULL },			//COLOR_YELLOW
	{1, 1 , 2 , 2 },		//COLOR_VIOLET
	{SIDE_7 , SIDE_7 , SIDE_7 , SIDE_7 }		//COLOR_ORANGE	
};



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

