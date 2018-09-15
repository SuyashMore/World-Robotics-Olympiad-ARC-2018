#pragma once

// #include "ImageProcessing.cpp"
#include "defines.h"


double Vmap(double input,double inLow,double inHigh,double outLow,double outHigh)
{
	if(input <= inLow)
		return outLow;
	if(input >= inHigh )
		return outHigh;

	return (outLow + input * (outHigh-outLow)/(inHigh-inLow));
}

void setDelayItr(int num)
{
  maxStopFlagItr=num;
}

void handle_delay()
{
    stopFlagIterations++;
    if(stopFlagIterations>=maxStopFlagItr)
    {
        stopFlag=false;
        stopFlagIterations=0;
    }
}

bool cordinator=false;
bool pickup=false;
bool stackBlk=false;
bool enableArmControl=false;
int mode=0;

void enableArm()
{
  enableArmControl=true;
  mode=0;
}

void enableCordinator()
{
  enableArmControl=true;
  cordinator=true;
  pickup=false;
  stackBlk=false;
  mode=0;
}
void disableCordinator()
{
  enableArmControl=true;
  cordinator=false;
  pickup=false;
  stackBlk=false;
  mode=0;
}
void pickupBlock()
{
  enableArmControl=true;
  cordinator=true;
  pickup=true;
  stackBlk=false;
  mode=0;
}
void stackBlock()
{
  enableArmControl=true;
  pickup=false;
  cordinator=false;
  stackBlk=true;
  mode=0;
}
void move2standard()
{
  enableArmControl=true;
  pickup=false; 
  mode=0;
}

void arm_pushAndPullPosition()
{
	disableCordinator();
	enableArmControl=true;
	mode = 1;
}

void move_Arm_down()
{
	disableCordinator();
	enableArmControl=true;
	mode = 2;
}

void move2standardNorm()
{
	disableCordinator();
	enableArmControl=true;
	mode = 3;	
}

void compressArm()
{
	disableCordinator();
	enableArmControl=true;
	mode = 4;	
}

int requiredBlockIndex = 0;
void fillNavMap()
{
	int judgePiece = BlockColor[0];		//Extract the Judge Piece Color and store it in a variable
	
	int navIndex = 0;									//Holds the Maximum Navigation Steps Required for the Entire Game

	bool foundColor=false;						//Flag to Signal if it has found and Color on the Play-Sheet


// Perform this Operation for each Required Block
	while (requiredBlockIndex < MAX_BLOCKS && (TETRASTACK_ORDER[judgePiece][requiredBlockIndex] != COLOR_NULL) )
	{
		int nextRequiredColor = TETRASTACK_ORDER[judgePiece][requiredBlockIndex];		//Collects the Next Required Piece
			
		//Perform Linear Search for Each Required Color on the Map on 6 Places
		for(int i=1;i<6;i++)
		{
			if(nextRequiredColor == BlockColor[i]) 		//Checks if the required Color is equal to the Block Color at Various Location on the play-Sheet
			{
				NavigationOrder[navIndex++] = i;			// i <- Represents the Location on the Map
				BlockColor[i] = COLOR_NULL;					//Delete the Block From the Map
				foundColor=true;										//Enable the found_Color Flag
				break;															//Break Out of the "FOR" loop once found the Color
			}
		}


		if(!foundColor)													//If Color is Not Found on the Map,Go for CHUTE
		{
			NavigationOrder[navIndex++] = CHUTE;
		}
	
		foundColor=false;
		NavigationOrder[navIndex++]=JUDGEPART;	// Stack the BLOCK After Every Block is Picked Up

		requiredBlockIndex+=1;
	}

	maximum_Blocks_2_pickup = navIndex;
	requiredBlockIndex=0;
}

void printNavMap()
{
	cout<<"Pickup Order :"<<endl;
	for(int i=0;i<maximum_Blocks_2_pickup;i++)
	{
		switch(NavigationOrder[i])
		{
			case JUDGEPART:
				// cout<<"Stacking Form"<<endl;
				break;
			case SUPPLY1:
				cout<<"Supply 1"<<endl;
				break;
			case SUPPLY2:
				cout<<"Supply 2"<<endl;
				break;
			case WHITE1:
				cout<<"White 1"<<endl;
				break;
			case WHITE2:
				cout<<"White 2"<<endl;
				break;
			case WHITE3:
				cout<<"White 3"<<endl;
				break;
			case CHUTE:
				cout<<"Delivery Chute"<<endl;
				break;
		}
	}
}

int placeVector[6];

int printPlaceVector()
{
	cout<<"Placing Blocks at : ";
	for(int i=0;i<3;i++)
	{
		switch(placeVector[i])
		{
			case 1:
				cout<<"1 , ";
				break;
			case 2:
				cout<<"2 , ";
				break;
			case 3:
				cout<<"3 , ";
				break;
			case 4:
				cout<<"4 , ";
				break;
			case 5:
				cout<<"5 , ";
				break;
			case 6:
				cout<<"6 , ";
				break;
			case 7:
				cout<<"7 , ";
				break;
			case 8:
				cout<<"8 , ";
				break;
		}
	}
	cout<<endl;
}


int cvt2HX(int num)
{
	switch(num)
	{
		case 1:
			return SIDE_1;
			break;
		case 2:
			return SIDE_2;
			break;
		case 3:
			return SIDE_3;
			break;
		case 4:
			return SIDE_4;
			break;
		case 5:
			return SIDE_5;
			break;
		case 6:
			return SIDE_6;
			break;
		case 7:
			return SIDE_7;
			break;
		case 8:
			return SIDE_8;
			break;
	}
}

bool isButtonDataReceived = false;

void handleButtons(int input)
{
	int num =input;
	placeVector[0] = num %10;
	num/=10;
	placeVector[1] = num %10;
	num/=10;
	placeVector[2] = num % 10;


}