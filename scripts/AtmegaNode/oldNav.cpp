

// Navigate to Stack the Block in Hand
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
