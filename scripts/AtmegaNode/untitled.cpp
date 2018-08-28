#pragma once

#include "containers.h"
#include<unistd.h>
#include "LineFollowing.cpp"


bool balanceWithTOF(float targetDistance,botData& newSensor,Motor& motor);
// Create An Global Instance of the gameState Object
gameState state;
int itr = 0;

bool exec4=false;
bool exec5=false;

bool stopFlag = false;
int stopFlagIterations = 0;
int maxStopFlagItr = 70;
bool armItr = false;

void navigate(botData& newSensor,botData& oldSensor,Motor& motor)
{
  state.updateDigiCounter(newSensor,oldSensor,motor);
  motor.reset();
	// Step 1 :
			// Go Forward until the Bot has Not Reached To the Starting Line (Passed 2 Lines)
 	if(state.digiCounter<2)
  	{
      itr=1;
    	motor.bot_Forward_withPWM(FORWARD_MOTION_PWM);

  	}
 	 // Step 2:
  			//Stop and  Turn Left
  if ((state.digiCounter >= 2) && state.executeStep2)
  	{
		  // Step 2.1:+
  			// (BOT_STOP)
  		if (state.step2Counter == 0)
  		{
        itr=2;
    		stopFlag=true;
        motor.bot_Stop();
    		state.step2Counter=1;
  		}

      	//SPOT-LEFT until Front Turn is Complete
  		// if (!newSensor.isFrontTurnComplete() && state.step2Counter==1)
      else if (state.step2Counter==1 && !newSensor.isFrontTurnComplete())
  		{
        itr=3;
    		motor.spot_Left_withPWM(SPOT_LEFT_PWM);
  		}
      else if(state.step2Counter==1)
      {
        motor.bot_Stop();
        stopFlag=true;
        itr=4;
        state.step2Counter=3;
      }
  		// Step 2.3:
  			// Wait for 1 second after the Turn is Complete (BOT_STOP)
  		else if (state.step2Counter==3)
  		{
    		state.executeStep2 = false;
    		state.executeStep3=true;
  		}
  	}

  	// Step 3:
  		// Go Forward To Stacking Form Unless the TOF-Reading is Received
	if (state.executeStep3)
   	{
      itr = 5;
      if(newSensor.tofFlag==false)
          followLine(newSensor,oldSensor,motor);
      else if(balanceWithTOF(200,newSensor,motor) && followLine(newSensor,oldSensor,motor))
        {
          motor.bot_Stop();
          // state.executeStep3=false;
          // exec4=true;

        }

   	}
    else if(exec4)
    {
      itr = 6;
      motor.bot_Stop();
      armItr=true;
      stopFlag=true;
      exec4=false;
      exec5=true;
      
    }
    else if(exec5)
    {
      if(newSensor.tofFront < 350)
      {
        motor.bot_Backward_withPWM(100);
      }
      else
      {
        motor.bot_Stop();
      }
    }
}


void mainLoop(botData& newSensor,botData& oldSensor,Motor& motor)
{
  if(!stopFlag)
    navigate(newSensor,oldSensor,motor);
  else if(armItr)
  {
    motor.bot_Stop();
    stopFlagIterations++;
    if(stopFlagIterations>=4000)
      {
        stopFlag=false;
        stopFlagIterations=0;
        armItr=false;
      }
  }
    else
    {
      motor.bot_Stop();
      // Loop through Stop for Certain Iterations
      stopFlagIterations++;
      if(stopFlagIterations>=maxStopFlagItr)
      {
        stopFlag=false;
        stopFlagIterations=0;
      }
    };


}

// Balances Bot at (targetDistance) from the TOF-Reading
bool balanceWithTOF(float targetDistance,botData& newSensor,Motor& motor)
{
  float delta = targetDistance-newSensor.tofFront;

  if(abs(delta) > TOF_ERROR_THRESH)
  {
    if(delta>0)
    {
      motor.bot_Backward_withPWM(100);
    }
    else
    {
      motor.bot_Forward_withPWM(100);
    }
    return false;
  }
  return true;
}
