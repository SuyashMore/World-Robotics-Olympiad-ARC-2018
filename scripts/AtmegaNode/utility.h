#pragma once

#include "ImageProcessing.cpp"

double Vmap(double input,double inLow,double inHigh,double outLow,double outHigh)
{
	if(input <= inLow)
		return outLow;
	if(input >= inHigh )
		return outHigh;

	return (outLow + input * (outHigh-outLow)/(inHigh-inLow));
}

bool navFlag = true;
bool camFlag=true;
bool stopFlag = false;
int stopFlagIterations = 0;
int maxStopFlagItr = 70;

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
  mode=0;
}
void disableCordinator()
{
  enableArmControl=true;
  cordinator=false;
  mode=0;
}
void pickupBlock()
{
  enableCordinator();
  enableArmControl=true;
  pickup=true;
  mode=0;
}
void stackBlock()
{
  enableArmControl=true;
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

int requiredBlockIndex = 0;
void fillNavMap()
{
	int judgePiece = BlockColor[0];
	
	int navIndex = 0;
	bool foundColor=false;
	//Perform Linear Search for Each Required Color on the Map
	while (requiredBlockIndex < MAX_BLOCKS)
	{
		int nextRequiredColor = TETRASTACK_ORDER[judgePiece][requiredBlockIndex];
	  	for(int i=1;i<6;i++)
	  	{
	    	if(nextRequiredColor == BlockColor[i])
	    	{
	      	NavigationOrder[navIndex] = i;
	      	navIndex++;
	      	BlockColor[i] = COLOR_NULL;
	      	foundColor=true;
	      	break;
	    	}
	  	}
	  	if(!foundColor)
	  	{
	    	NavigationOrder[navIndex] = CHUTE;
	    	navIndex++;
	  	}
	  	foundColor=false;
			NavigationOrder[navIndex++]=JUDGEPART;
	  	requiredBlockIndex++;
	}
	requiredBlockIndex=0;
}