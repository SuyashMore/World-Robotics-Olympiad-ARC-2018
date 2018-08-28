#pragma once

#include "containers.h"
#include "LineFollowing.cpp"


// Create An Global Instance of the gameState Object
gameState state;
int itr = 0;

bool stopFlag = false;
int stopFlagIterations = 0;
int maxStopFlagItr = 70;
bool armItr = false;

bool cordinator=false;
bool pickup=false;
bool stackBlock=false;

bool navFlag = true;

int strafeItr=0;
int maxStrafeItr = 40;
bool temp =true;

void setDelayItr(int num)
{
  maxStopFlagItr=num;
}

bool balanceWithTOF(float targetDistance,botData& newSensor,Motor& motor);

// Navigate to Stack the Block
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
          state.executeStep3=false;
        }

   	}
    // Send Signal to Stack the Block
    if(state.executeStep4)
    {
      itr=6;
      stackBlock=true;
      state.executeStep4=false;
      state.executeStep5=true;
    }
    // Bot-Stop after Executing All the Steps
    if(state.executeStep5)
    {
      itr=7;
      motor.bot_Stop();
    }

}

// Navigates to Pickup the Block
void navigate2(botData& newSensor,botData& oldSensor,Motor& motor)
{
  state.updateDigiCounter(newSensor,oldSensor,motor);
  motor.reset();


 // Step 1 : Go Forward and Turn Left
  if(state.executeStep1)
  {
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

  }

    // Step 3:
      // Go Forward Until digi-Count == 4 and Turn Left
  if (state.executeStep3)
    {
        if(state.digiCounter<4)
        {
          itr = 5;
          followLine(newSensor,oldSensor,motor);
        }  
        else if(newSensor.isFrontTurnComplete() && temp)
        {
          itr=6;
          motor.spot_Left_withPWM(SPOT_LEFT_PWM);
        }
        else if(!newSensor.isFrontTurnComplete())
        {
          temp = false;
          itr=7;
          motor.spot_Left_withPWM(SPOT_LEFT_PWM);
        }
        else
        {
          state.executeStep3=false;
          state.executeStep4=true;
          cordinator=true;
      }

    }

    // Step 4:
      // Go Forward for few Seconds and Strafe Right for few Iterations

    if(state.executeStep4)
    {
      if(strafeItr<=maxStrafeItr)
      {
        itr=8;
        if(strafeItr  <= int((maxStrafeItr)/2)    )
        {
          motor.bot_Forward_withPWM(100);
        }
        else
        {
          motor.strafe_Right_withPWM(100);
        }
        strafeItr++;
      }
      
      if(strafeItr > maxStrafeItr)
      {
        state.executeStep4=false;
        itr=8;
        motor.bot_Stop();
        // stopFlag=true;
        state.executeStep5=true;
        pickup=true;
      }

    }


    // Step 5:
        // Strafe Left Until the Bot is Back on Line

    if(state.executeStep5)
    {
      if(!newSensor.isFrontTurnComplete())
      {
        motor.strafe_Left_withPWM(100);
      }
      else
      {
        state.executeStep5=false;
        state.executeStep6=true;
        // Reset the Digi-Counter
        state.digiCounter=0;
        temp =false;
        cordinator=false;
      }
    }


    // Step 6:
        // Bot Reverse Until Junction Counter == 1 and then Spot-Right
    if(state.executeStep6)
    {
      if(state.digiCounter<1)
        motor.bot_Backward_withPWM(100);
      else
      {
          if(newSensor.isFrontTurnComplete() && temp)
          {
            motor.strafe_Right_withPWM(100);
          }
          else if(!newSensor.isFrontTurnComplete())
          {
            temp=false;
           motor.strafe_Right_withPWM(100); 
          }
          else
          {
            state.executeStep6=false;
            state.executeStep7=true;
          }
      }
    }

    // Step 7:
        // Bot Forward Until Reached at and Desired Distance from the Stacking Form
    if(state.executeStep7)
    {
      if(newSensor.tofFlag==false)
          followLine(newSensor,oldSensor,motor);
      else if(balanceWithTOF(200,newSensor,motor) && followLine(newSensor,oldSensor,motor))
        {
          motor.bot_Stop();
          state.executeStep7=false;
          state.executeStep8=true;
          stackBlock=true;
        }
    }
    // Bot-Stop
    if(state.executeStep8)
    {
      motor.bot_Stop();
    }


    
}

void mainLoop(botData& newSensor,botData& oldSensor,Motor& motor)
{
  if(!stopFlag)
    {
      
            // navigates from gome 2 stack the block with the block in Arm
      navigate(newSensor,oldSensor,motor);
      


              // Navigates from home 2 pickup the block and Stack
      // navigate2(newSensor,oldSensor,motor);
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
      motor.bot_Backward_withPWM(BALANCE_WITH_TOF_PWM);
    }
    else
    {
      motor.bot_Forward_withPWM(BALANCE_WITH_TOF_PWM);
    }
    return false;
  }
  return true;
}
