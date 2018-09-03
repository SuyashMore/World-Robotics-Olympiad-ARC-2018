#pragma once

#include "containers.h"
#include "LineFollowing.cpp"



// Create An Global Instance of the gameState Object
gameState state;
int itr = 0;


bool temp =true;
bool temp2=true;

int strafeItr=0;
int maxStrafeItr = 60;


bool balanceWithTOF(float targetDistance,botData& newSensor,Motor& motor);

// Navigate to Stack the Block
void navigate(botData& newSensor,botData& oldSensor,Motor& motor)
{
  state.updateDigiCounter(newSensor,oldSensor,motor);
  motor.reset();
	// Step 1 :
			// Go Forward until the Bot has Not Reached To the Starting Line (Passed 2 Lines)
  if(state.executeStep1)
  {
     	if(state.digiCounter<1)
      { 	
          itr=1;
        	motor.strafe_Right_withPWM(FORWARD_MOTION_PWM);
      }
      else if(state.digiCounter==1 && !newSensor.isFrontTurnComplete())
      {
          itr=2;
          motor.strafe_Right_withPWM(FORWARD_MOTION_PWM);
      }
      else if(newSensor.isFrontTurnComplete())
      {
        state.executeStep1=false;
        state.executeStep3=true;
        motor.bot_Stop();
        stopFlag=true;
      }
  }

  	// Step 3(no Step 2):
  		// Go Forward To Stacking Form Unless the TOF-Reading is Received
	else if (state.executeStep3)
   	{
      itr = 3;
      if(newSensor.tofFlag==false)
          followLine(newSensor,oldSensor,motor);
      else if(balanceWithTOF(200,newSensor,motor) && followLine(newSensor,oldSensor,motor))
        {
          motor.bot_Stop();
          state.executeStep3=false;
          state.executeStep4=true;
        }

   	}
    // Send Signal to Stack the Block
  else if(state.executeStep4)
    {
      itr=4;
      stackBlock();
      state.executeStep4=false;
      state.executeStep5=true;
    }
    // Bot-Stop after Executing All the Steps
  else if(state.executeStep5)
    {
      itr=5;
      motor.bot_Stop();
      state.executeStep5=false;
      state.executeStep6=true;
    }
  else if(state.executeStep6)
    {
      if(newSensor.tofFront < 400)
      {
        followLineBackpwm(newSensor,oldSensor,motor,90);
      }
      else 
      {
        motor.bot_Stop();
      }
    }
}

// Navigates to Pickup the Block
void navigate2(botData& newSensor,botData& oldSensor,Motor& motor)
{
  state.updateDigiCounter(newSensor,oldSensor,motor);
  motor.reset();

  // Step 1 :
      // Go Forward until the Bot has Not Reached To the Starting Line (Passed 2 Lines)
  if(state.executeStep1)
  {
      if(state.digiCounter<1)
      {   
          itr=1;
          motor.strafe_Right_withPWM(FORWARD_MOTION_PWM);
      }
      else if(state.digiCounter==1 && !newSensor.isFrontTurnComplete())
      {
          itr=2;
          motor.strafe_Right_withPWM(FORWARD_MOTION_PWM);
      }
      else if(newSensor.isFrontTurnComplete())
      {
        state.executeStep1=false;
        state.executeStep3=true;
        motor.bot_Stop();
        stopFlag=true;
      }
  }


    // Step 3:
      // Go Forward Until digi-Count == 4 and Turn Left
  if (state.executeStep3)
    {
        if(state.digiCounter<3)
        {
          itr = 3;
          followLine(newSensor,oldSensor,motor);
        }
        else if(temp2)
        {
          temp2=false;
          motor.bot_Stop();
          stopFlag=true;
        }
        else if(newSensor.isFrontTurnComplete() && temp)
        {

          itr=4;
          motor.spot_Left_withPWM(SPOT_LEFT_PWM);
        }
        else if(!newSensor.isFrontTurnComplete())
        {
          temp = false;
          itr=5;
          motor.spot_Left_withPWM(SPOT_LEFT_PWM);
        }
        else
        {
          itr=6;
          motor.bot_Stop();
          stopFlag=true;
          state.executeStep3=false;
          state.executeStep4=true;
          enableCordinator();
      }
    }

    // Step 4:
      // Go Forward for few Seconds and Strafe Right for few Iterations

    else if(state.executeStep4)
    {
      if(strafeItr<=maxStrafeItr)
      {
        itr=7;
        if(strafeItr  <= int((maxStrafeItr)/2)    )
        {
          motor.bot_Forward_withPWM(120);
          processPID(newSensor,oldSensor,motor);
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
        stopFlag=true;
        pickupBlock();
        state.executeStep5=true;
      }

    }


    // Step 5:
        // Strafe Left Until the Bot is Back on Line

    else if(state.executeStep5)
    {
      if(!newSensor.isFrontTurnComplete())
      {
        itr=9;
        motor.strafe_Left_withPWM(100);
      }
      else
      {
        itr=10;
        state.executeStep5=false;
        state.executeStep6=true;
        // Reset the Digi-Counter
        state.digiCounter=0;
        stopFlag=true;
        temp =true;
        disableCordinator();
      }
    }


    // Step 6:
        // Bot Reverse Until Junction Counter == 1 and then Spot-Right
    else if(state.executeStep6)
    {
      if(state.digiCounter<1)
        {
          itr=11;
          followLineBackpwm(newSensor,oldSensor,motor,100);
      }

      else
      {

          if(newSensor.isFrontTurnComplete() && temp)
          {
            itr=12;
            motor.spot_Right_withPWM(100);
          }
          else if(!newSensor.isFrontTurnComplete())
          {
            itr=13;
            temp=false;
           motor.spot_Right_withPWM(100); 
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
    else if(state.executeStep7)
    {

      if(newSensor.tofFlag==false)
          followLine(newSensor,oldSensor,motor);
      else if(balanceWithTOF(220,newSensor,motor) && followLine(newSensor,oldSensor,motor))
        {
          itr=14;
          motor.bot_Stop();
          stopFlag=true;

          state.digiCounter=0;

          state.executeStep7=false;
          state.executeStep8=true;
          stackBlock();
        }
    }
    //Step:8 ----> Bot-Stop
    else if(state.executeStep8)
    {
      itr=15;
      motor.bot_Stop();
      stopFlag=true;

      state.executeStep8=false;
      state.executeStep9=true;
    }
    // Step:9 ------>Return back to the Junction

    else if(state.executeStep9)
    {
      if(state.digiCounter<2)
      {
        itr=16;
        followLineBackpwm(newSensor,oldSensor,motor,80);
      }
      else 
      {
        itr=17;
        motor.bot_Stop();
        state.executeStep9=false;
        state.executeStep10=true;
      }
    }
    else if(state.executeStep10)
    {
      if(!newSensor.isFrontAllBlack())
      {
        followLineBackpwm(newSensor,oldSensor,motor,80);
      }
      else
      {
        state.executeStep10=false;
        state.executeStep11=true;
      }
    }
    else if(state.executeStep11)
    {
      if(newSensor.isFrontAllBlack())
      {
        followLine(newSensor,oldSensor,motor);
      }
      else
      {
        stopFlag=true;
        state.executeStep11=false;
        state.executeStep12=true;
        state.digiCounter=0;
      }
    }
    else if(state.executeStep12)
    {
      if(state.digiCounter<2)
      {
        motor.strafe_Left_withPWM(100);
      }
      else
      {
        if(newSensor.digiLeft==1)
        {
          motor.strafe_Right_withPWM(80);
        }
        else
        {
          motor.bot_Stop();
        }
      }
    }


    
}

void mainLoop(botData& newSensor,botData& oldSensor,Motor& motor)
{
  if(!stopFlag)
    {
            // navigates from gome 2 stack the block with the block in Arm
      navigate2(newSensor,oldSensor,motor);
      
            // Navigates from home 2 pickup the block and Stack
      // navigate2(newSensor,oldSensor,motor);
    }
  else
    {
      motor.bot_Stop();
      // Loop through Stop for Certain Iterations
      handle_delay();
    }
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
