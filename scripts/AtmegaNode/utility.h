#pragma once

bool navFlag = true;


double Vmap(double input,double inLow,double inHigh,double outLow,double outHigh)
{
	if(input <= inLow)
		return outLow;
	if(input >= inHigh )
		return outHigh;

	return (outLow + input * (outHigh-outLow)/(inHigh-inLow));
}


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

void enableArm()
{
  enableArmControl=true;
}

void enableCordinator()
{
  enableArmControl=true;
  cordinator=true;
}
void disableCordinator()
{
  enableArmControl=true;
  pickup=true;
}
void pickupBlock()
{
  enableCordinator();
  enableArmControl=true;
  pickup=true;
}
void stackBlock()
{
  enableArmControl=true;
  stackBlk=true;
}
void move2standard()
{
  enableArmControl=true;
  pickup=true; 
}

