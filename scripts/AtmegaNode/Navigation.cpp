#pragma once

#include "containers.h"
#include "LineFollowing.cpp"


// Create An Global Instance of the gameState Object
gameState state;
int itr = 0;


bool temp =true;
bool temp2=true;

int strafeItr=0;
int maxStrafeItr = 190;

int tfi=0;
int maxTf = 20;

int xitr = 0;
int itBF = 120;


bool balanceSideAt(float targetDistance,botData& newSensor,Motor& motor)
{
 float delta = targetDistance-newSensor.tofSide;

  if(abs(delta) > TOF_ERROR_THRESH_SIDE)
  {
    if(delta>0)
    {
      motor.strafe_Right_withPWM(90);
    }
    else
    {
      motor.strafe_Left_withPWM(90);
    }
    return false;
  }
  return true; 


}

bool balanceWithTOF(float targetDistance,botData& newSensor,Motor& motor);

bool nav_2_MainLine(botData& newSensor,botData& oldSensor,Motor& motor)
{
	state.updateDigiCounter(newSensor,oldSensor,motor);
	motor.reset(); 

	if(state.digiCounter<1)
      {   
        cout<<"Currently Executing: Strafe Right 1"<<endl;
          motor.strafe_Right_withPWM(STRAFE_RIGHT_2_MAIN_LINE_PWM);
      }
      else if(state.digiCounter==1 && !newSensor.isFrontTurnComplete())
      {
        cout<<"Currently Executing: Strafe Right 2"<<endl;
          motor.strafe_Right_withPWM(STRAFE_RIGHT_2_MAIN_LINE_PWM);
      }
      else if(newSensor.isFrontTurnComplete())
      {
        cout<<"Currently Executing: Bot Stop"<<endl;
        motor.bot_Stop();
	stopFlag=true;
        return true;
      }

      return false;

}

// to Remove
bool nav_2_MainJunction_from_MainLine(botData& newSensor,botData& oldSensor,Motor& motor)
{
	if(state.digiCounter<3)
        {
          itr = 3;
          followLine(newSensor,oldSensor,motor);
        }
    else 
    {
    	return true;
    }
    return false;
}



// Go Forward One Junction
bool temp3=true;
bool nav_goForward_1_Junction(botData& newSensor,botData& oldSensor,Motor& motor)
{
	state.updateDigiCounter(newSensor,oldSensor,motor);
	motor.reset(); 

	if(temp3)
	{
		temp3=false;
		state.digiCounter=0;
	}

	if(state.digiCounter<1)
	{
    cout<<"Currently Executing: Follow Line"<<endl;
          followLine(newSensor,oldSensor,motor);
	}
	else
	{
		temp3=true;
        state.digiCounter=0;
		return true;
	}
	return false;
}


// Go Backward One Junction
bool temp4=true;
bool nav_goBackward_1_Junction(botData& newSensor,botData& oldSensor,Motor& motor)
{
	state.updateDigiCounter(newSensor,oldSensor,motor);
	motor.reset(); 

	if(temp4)
	{
		temp4=false;
		state.digiCounter=0;
	}

	if(state.digiCounter<1)
	{
    cout<<"Currently Executing: Follow Line Back"<<endl;
          followLineBack(newSensor,oldSensor,motor);
	}
	else
	{
		temp4=true;
        state.digiCounter=0;
		return true;
	}
	return false;
}




// Pickup From Supply Line
int temp01=true;
int tempturn=false;
int miniEx01=1;
int strafeItr01=0;
int strafeMode=1;
bool nav_PickupBlock_from__SupplyLine(botData& newSensor,botData& oldSensor,Motor& motor)
{
    state.updateDigiCounter(newSensor,oldSensor,motor);
    motor.reset(); 
	// Mini - Step 1 : Handle Rotation and Enable 90 degrees
	if(miniEx01==1)
	{
		if(newSensor.isFrontTurnComplete() && temp01)
        {
          cout<<"Currently Executing: Spot Left"<<endl;
          motor.spot_Left_withPWM(SPOT_LEFT_PWM);
        }
        else if(!newSensor.isFrontTurnComplete())
        {
          cout<<"Currently Executing: Spot Left"<<endl;
          temp01 = false;
	   tempturn=true;
          motor.spot_Left_withPWM(SPOT_LEFT_PWM);
        }
	else if(!newSensor.isBackTurnComplete() && tempturn)
	{
        motor.setPWM_all(0);
		motor.spot_Right();
		motor.setPWMof(MOTOR_BACK,170);
	}
        else
        {
          cout<<"Currently Executing: Bot Stop-Enabling Cordinator"<<endl;
          motor.bot_Stop();
          stopFlag=true;
          enableCordinator();
          miniEx01=2;
      }
  	}
  	//  Mini - Step 2 : Strafe Forward , Right , Forward and Pickup the Block
  	else if(miniEx01==2)
  	{

  		if(strafeMode == 1)			//Strafe Forward
  		{
        cout<<"Currently Executing: Strafe Forward"<<endl;
  			if(strafeItr01  <= PICKUP_1_ITR_MAX)
	        {
	          motor.bot_Forward_withPWM(STRAFE_PICKUP);
	          processPID(newSensor,oldSensor,motor);
	        }
	        else
	        	{strafeMode=2;
	        	strafeItr01=0;}
  		}
  		else if(strafeMode == 2)	//Strafe Right
  		{
        cout<<"Currently Executing: Strafe Right"<<endl;
  			if(strafeItr01  <=  PICKUP_2_ITR_MAX)
	        {
	          motor.strafe_Right_withPWM(STRAFE_PICKUP);
	        }
	        else
	        	{strafeMode=3;
	        	strafeItr01=0;}
  		}
  		else if(strafeMode == 3)	//Strafe Forward
  		{	
        cout<<"Currently Executing: Strafe Forward"<<endl;
  			if(strafeItr01  <=  PICKUP_3_ITR_MAX)
	        {
	          motor.bot_Forward_withPWM(STRAFE_PICKUP);
	        }
	        else
	        {
	        	strafeItr01=0;
	        	strafeMode=4;
	        }

  		}
  		else if(strafeMode == 4)
  		{
        cout<<"Currently Executing: Bot Stop(Pickup)"<<endl;
  			motor.bot_Stop();
	        stopFlag=true;
	        pickupBlock();

	        miniEx01 = 3;
			temp01=true;
  		}

  		strafeItr01++;
  	}

  	// Mini - Step 3 : Disable Cordinator and Strafe Left
  	else if(miniEx01==3)
  	{
  		if(temp01)
      	{
        	disableCordinator();
        	temp01=false;  
      	}
      
      	if(!newSensor.isFrontTurnComplete())
      	{
          cout<<"Currently Executing: Strafe Left(Till Back on Line)"<<endl;
        	motor.strafe_Left_withPWM(STRAFE_PICKUP);
      	}
      	else
      	{
	        // Reset the Digi-Counter
	        state.digiCounter=0;
	        temp01 =true;

	        miniEx01 = 4;
      	}	
  	}

  	// Mini - Step 4 : GO Back with Follow Line and the Spot Rotate Right
  	else if(miniEx01==4)
  	{

  		if(state.digiCounter<1)
        {
          cout<<"Currently Executing: Follow Line Back"<<endl;
          followLineBackpwm(newSensor,oldSensor,motor,FOLLOW_LINE_BACK_PWM);
      	}
      	else
      	{
          cout<<"Currently Executing: Spot Right "<<endl;
        	if(newSensor.isFrontTurnComplete() && temp01)
        	{
            	motor.spot_Right_withPWM(SPOT_ROTATE_PWM);
          	}
          	else if(!newSensor.isFrontTurnComplete())
          	{
            	temp01=false;
           		motor.spot_Right_withPWM(SPOT_ROTATE_PWM); 
          	}
          	else
          	{
          		miniEx01=1;
                        temp01=true;
				      strafeItr01=0;
				      strafeMode=1;
            	return true;
          	}
      	}	
  	}

  	return false;

}

bool nav_PickupBlock_from__SupplyLine2(botData& newSensor,botData& oldSensor,Motor& motor)
{
    state.updateDigiCounter(newSensor,oldSensor,motor);
    motor.reset(); 
    // Mini - Step 1 : Handle Rotation and Enable 90 degrees
    if(miniEx01==1)
    {
        if(newSensor.isBackTurnComplete() && temp01)
        {
          cout<<"Currently Executing: Spot Left"<<endl;
          motor.spot_Left_withPWM(SPOT_LEFT_PWM);
        }
        else if(!newSensor.isBackTurnComplete())
        {
          cout<<"Currently Executing: Spot Left"<<endl;
          temp01 = false;
          motor.spot_Left_withPWM(SPOT_LEFT_PWM);
        }
        else
        {
          cout<<"Currently Executing: Bot Stop-Enabling Cordinator"<<endl;
          motor.bot_Stop();
          stopFlag=true;
          enableCordinator();
          miniEx01=2;
      }
    }
    //  Mini - Step 2 : Strafe Forward , Right , Forward and Pickup the Block
    else if(miniEx01==2)
    {

      if(strafeMode == 1)         //Strafe Forward
        {
        cout<<"Currently Executing: Strafe Forward"<<endl;
            if(strafeItr01  <= PICKUP_1_ITR_MAX_2)
            {
              motor.bot_Forward_withPWM(STRAFE_PICKUP);
              processPID(newSensor,oldSensor,motor);
            }
            else
                {strafeMode=2;
                strafeItr01=0;}
        }
        else if(strafeMode == 2)    //Strafe Right
        {
        cout<<"Currently Executing: Strafe Right"<<endl;
            if(strafeItr01  <=  PICKUP_2_ITR_MAX)
            {
              motor.strafe_Right_withPWM(STRAFE_PICKUP);
            }
            else
                {strafeMode=3;
                strafeItr01=0;}
        }
        else if(strafeMode == 3)    //Strafe Forward
        {   
        cout<<"Currently Executing: Strafe Forward"<<endl;
            if(strafeItr01  <=  PICKUP_3_ITR_MAX)
            {
              motor.bot_Forward_withPWM(STRAFE_PICKUP);
            }
            else
            {
                strafeItr01=0;
                strafeMode=4;
            }

        }
        else if(strafeMode == 4)
        {
        cout<<"Currently Executing: Bot Stop(Pickup)"<<endl;
            motor.bot_Stop();
            stopFlag=true;
            pickupBlock();

            miniEx01 = 3;
            temp01=true;
        }

        strafeItr01++;
    }

    // Mini - Step 3 : Disable Cordinator and Strafe Left
    else if(miniEx01==3)
    {
        if(temp01)
        {
            disableCordinator();
            temp01=false;  
        }
      
        if(!newSensor.isFrontTurnComplete())
        {
          cout<<"Currently Executing: Strafe Left(Till Back on Line)"<<endl;
            motor.strafe_Left_withPWM(STRAFE_PICKUP);
        }
        else
        {
            // Reset the Digi-Counter
            state.digiCounter=0;
            temp01 =true;

            miniEx01 = 4;
        }   
    }

    // Mini - Step 4 : GO Back with Follow Line and the Spot Rotate Right
    else if(miniEx01==4)
    {

        if(state.digiCounter<1)
        {
          cout<<"Currently Executing: Follow Line Back"<<endl;
          followLineBackpwm(newSensor,oldSensor,motor,FOLLOW_LINE_BACK_PWM);
        }
        else
        {
          cout<<"Currently Executing: Spot Right "<<endl;
            if(newSensor.isFrontTurnComplete() && temp01)
            {
                motor.spot_Right_withPWM(SPOT_ROTATE_PWM);
            }
            else if(!newSensor.isFrontTurnComplete())
            {
                temp01=false;
                motor.spot_Right_withPWM(SPOT_ROTATE_PWM); 
            }
            else
            {
                miniEx01=1;
                        temp01=true;
                      strafeItr01=0;
                      strafeMode=1;
                return true;
            }
        }   
    }

    return false;

}

// Stack Block at Horizontal Distance From the Wall
int temp02=true;
int miniEx02=1;
int q=0;
bool stack_the_Block_from_MainJunction_at_hx(float targetDistance,botData& newSensor,botData& oldSensor,Motor& motor )
{
    state.updateDigiCounter(newSensor,oldSensor,motor);
    motor.reset(); 

	if(miniEx02==1)   			//Reach at an Balancing Distance from the TOF and Balance
	{
		if(newSensor.tofFront>(TOF_FRONT_BALANCE_DISTANCE+10))
        {
            cout<<"Currently Executing: Going Forward Till TOF:Forward"<<endl;
			// processPID(newSensor,oldSensor,motor);
            K_processPID(newSensor,oldSensor,motor,105,80,0.11);
			motor.bot_Forward_withPWMm(140);
            q=0;   
        }
        else if(newSensor.tofFront<(TOF_FRONT_BALANCE_DISTANCE-10))
        {
            cout<<"Currently Executing: Going Forward Till TOF:Backward"<<endl;
            K_processPID(newSensor,oldSensor,motor,105,80,0.11);
            motor.bot_Backward_withPWMm(140);   
            q=0;
        }
        else
        {
            q++;
            motor.bot_Stop();
        }

        if(q>=12)
        {
            q=0;
            miniEx02=2;
        }
	}
	else if(miniEx02==2)		// Align the Bot with Line
	{
        cout<<"Currently Executing: Correcting with Line"<<endl;
	motor.bot_Forward_withPWMm(0);
        K_processPID(newSensor,oldSensor,motor,105,80,0.11);
       if( abs(newSensor.errorFront) <= LF_THRESH && abs(newSensor.errorBack) <= LF_THRESH )
        {
          q++;
        }
        else
        {
          q=0;
	  cout<<"Resetting"<<endl;
        }
      
      if(q >=LF_MAX)
      {
        motor.bot_Stop();
        stopFlag=true;
        state.digiCounter=0;
        miniEx02=4;
        q=0;
        stackBlock();
      }	
	}
	else if(miniEx02==3)		//Add Aligning with the Wall
	{
        // cout<<"Currently Executing: Balancing Side"<<endl;
        // if(!balanceSideAt(targetDistance,newSensor,motor))
        // {
        //   miniEx02=4;
        //   stackBlock();
        // }
    }
	else if(miniEx02==4)		// Pull out the Arm and Push the Block in
	{
        cout<<"Currently Executing: Bot Back and Push"<<endl;
		if(q<= (PULL_AND_PUSH_ITR/2))
      	{
	        motor.bot_Backward_withPWM(80);
	        if(q==PULL_AND_PUSH_ITR/2)
	        {
	          motor.bot_Stop();
	          stopFlag=true;
	        }
      	}
      	else
      	{
        	motor.bot_Forward_withPWM(80);
      	}
      	q++;
      	if(q>PULL_AND_PUSH_ITR)
      	{
        	miniEx02=5;
            state.digiCounter=0;
      	}
	}
	else if(miniEx02==5)		//Return Back to the Junction
	{
        cout<<"Currently Executing: follow Line Back"<<endl;
		if(state.digiCounter<1)
      	{
        	followLineBackpwm(newSensor,oldSensor,motor,120);
      	}
      	else 
      	{
        	motor.bot_Stop();
        	temp02=true;
        	miniEx02=1;
        	q=0;
        	return true;
      	}

	}

	return false;
}


int miniEx03=1;
int temp03=true;
int strafeItr03=0;
int strafeMode3=1;
bool nav_Pickup_from_WhiteSpace(botData& newSensor,botData& oldSensor,Motor& motor)
{
    state.updateDigiCounter(newSensor,oldSensor,motor);
    motor.reset(); 
	if(miniEx03==1)    //Step 1: Spot Right
	{
		if(newSensor.isFrontTurnComplete() && temp03)
		{
			motor.spot_Right_withPWM(SPOT_ROTATE_PWM);
		}
		else if(!newSensor.isFrontTurnComplete())
		{
			temp03=false;
      motor.spot_Right_withPWM(SPOT_ROTATE_PWM);
		}
		else
		{
			miniEx03=2;
		}
	}
	else if(miniEx03==2) //Step 2: Go Forward Till TOF Sensor shows Infinity
	{
		if(newSensor.tofSide>TOF_SIDE_DISTANCE)
		{
			followLine(newSensor,oldSensor,motor);
		}
		else
		{
			motor.bot_Stop();
			stopFlag=true;
			miniEx03=3;
			temp03=true;
		}
	}
	else if(miniEx03==3)         //Step 3: Spot Rotate Left till Perpendicular to the Line
	{
		if(newSensor.isFrontTurnComplete() && temp03)
		{
			motor.spot_Left_withPWM(SPOT_LEFT_PWM);
		  state.digiCounter=0;
    }

		else if(!newSensor.isFrontTurnComplete() && state.digiCounter<1)
		{
			temp03=false;
      motor.spot_Left_withPWM(SPOT_LEFT_PWM);
		}
		else
		{
			motor.bot_Stop();
			miniEx03=4;
		}
	}
	else if(miniEx03==4)         //Step 4: Strafe Forward and Pickup the Block
	{
		if(strafeMode3 == 1)			//Strafe Forward
  		{
  			if(strafeItr03  <= PICKUP_1_ITR_MAX)
	        {
	          motor.bot_Forward_withPWM(STRAFE_PICKUP);
	          processPID(newSensor,oldSensor,motor);
	        }
	        else
	        	{strafeMode3=2;
	        	strafeItr03=0;}
  		}
  		else if(strafeMode3 == 2)	//Strafe Right
  		{
  			if(strafeItr03  <=  PICKUP_2_ITR_MAX)
	        {
	          motor.strafe_Right_withPWM(STRAFE_PICKUP);
	        }
	        else
	        	{strafeMode3=3;
	        	strafeItr03=0;}
  		}
  		else if(strafeMode3 == 3)	//Strafe Forward
  		{	
  			if(strafeItr03  <=  PICKUP_3_ITR_MAX)
	        {
	          motor.bot_Forward_withPWM(STRAFE_PICKUP);
	        }
	        else
	        {
	        	strafeItr03=0;
	        	strafeMode3=4;
	        }

  		}
  		else if(strafeMode3 == 4)
  		{
  			motor.bot_Stop();
	        stopFlag=true;
	        pickupBlock();

	        miniEx03 = 5;
	        temp03=true;
	        state.digiCounter=0;
  		}

  		strafeItr03++;
	}
	else if(miniEx03==5)         //Step 5: Strafe Back on the Line
	{
		if(state.digiCounter<1)
		{
			motor.bot_Backward_withPWM(100);
		}
		else if(newSensor.isFrontTurnComplete())
		{
			motor.spot_Left_withPWM(SPOT_LEFT_PWM);
		}
		else 
		{
			state.digiCounter=0;
			miniEx03=6;
		}
	}

	else if(miniEx03==6)         //Step 6 : Return Back to the Main Junction and Spot Rotate-Right
	{
		if(state.digiCounter<1)
		{
			followLine(newSensor,oldSensor,motor);
		}
		else if(newSensor.isFrontTurnComplete() && temp03)
		{
			motor.spot_Right_withPWM(SPOT_ROTATE_PWM);
		}
		else if(!newSensor.isFrontTurnComplete())
		{
			temp03=false;
			motor.spot_Right_withPWM(SPOT_ROTATE_PWM);
		}
		else
		{
			temp03=true;
			strafeItr03=0;
			strafeMode3=1;
			miniEx03=1;
			return true;
		}
	}
	return false;

}


int miniEx04=1;
int temp04=true;
int strafeItr04=0;
int strafeMode4=1;
bool nav_Pickup_from_Delivery_chute(botData& newSensor,botData& oldSensor,Motor& motor)
{
    state.updateDigiCounter(newSensor,oldSensor,motor);
    motor.reset(); 
	if(miniEx04==1)
	{
		if(newSensor.isFrontTurnComplete() && temp04)
		{
			motor.spot_Right_withPWM(SPOT_LEFT_PWM);
		}
		else if(!newSensor.isFrontTurnComplete())
		{
			temp04=false;
			motor.spot_Right_withPWM(SPOT_LEFT_PWM);
		}
		else
		{
			miniEx04=2;
			temp04=false;
		}

	}
	else if(miniEx04 == 2)
	{
		if(newSensor.tofFront < DELIVERY_CHUTE_STOP_DISTANCE)
		{
			followLine(newSensor,oldSensor,motor);
		}
		else if(balanceWithTOF(DELIVERY_CHUTE_STOP_DISTANCE,newSensor,motor) && K_processPID(newSensor,oldSensor,motor,80,70,0))
		{
			motor.bot_Stop();
			stopFlag=true;
			miniEx04=3;
			enableCordinator();
		}
	}
	else if(miniEx04 == 3)
	{
		// Add Delay
		miniEx04=4;
	}
	else if(miniEx04 == 4)
	{
		
	}
}



// Navigates to Pickup the Block from Supply Line
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
          motor.strafe_Right_withPWM(160);
      }
      else if(state.digiCounter==1 && !newSensor.isFrontTurnComplete())
      {
          itr=2;
          motor.strafe_Right_withPWM(160);
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
        if(strafeItr  <= int((maxStrafeItr)/3)    )
        {
          motor.bot_Forward_withPWM(100);
          processPID(newSensor,oldSensor,motor);
        }
        else if(strafeItr  <= int((maxStrafeItr)*2/3 ))
        {
          motor.strafe_Right_withPWM(100);
        }
        else
        {
          motor.bot_Forward_withPWM(100);
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
        temp=true;
      }

    }


    // Step 5:
        // Strafe Left Until the Bot is Back on Line

    else if(state.executeStep5)
    {
      if(temp)
      {
        disableCordinator();
        temp=false;  
      }
      
      if(!newSensor.isFrontTurnComplete())
      {
        itr=9;
        motor.strafe_Left_withPWM(90);
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
      }
    }


    // Step 6:
        // Bot Reverse Until Junction Counter == 1 and then Spot-Right
    else if(state.executeStep6)
    {
      if(state.digiCounter<1)
        {
          itr=11;
          followLineBackpwm(newSensor,oldSensor,motor,150);
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
          {
            processPID(newSensor,oldSensor,motor);
            motor.bot_Forward_withPWMm(150);
          }
      else if(balanceWithTOF(170,newSensor,motor) && K_processPID(newSensor,oldSensor,motor,105,80,0.11))

        {
          tfi++;
          itr=14;
          cout<<"Balancing with TOF"<<endl;
          if(tfi>=maxTf)
          {
            state.executeStep7=false;
            state.executeStep75=true;
            tfi=0;
          }
        }
    }

    else if (state.executeStep75)
    {
        cout<<"TFI:="<<tfi<<endl;
        K_processPID(newSensor,oldSensor,motor,105,80,0.11);
        motor.bot_Forward_withPWMm(0);
       if( abs(newSensor.errorFront) <= LF_THRESH && abs(newSensor.errorBack) <= LF_THRESH )
        {
          tfi++;
        }
        else
        {
          tfi=0;
	  cout<<"Resetting"<<endl;
        }
      
      if(tfi >=LF_MAX)
      {
        motor.bot_Stop();
        stopFlag=true;
        state.digiCounter=0;
        state.executeStep75=false;
        state.executeStep74=true;
        stackBlock();
      }
    }
        else if (state.executeStep74)
          if(balanceSideAt(60,newSensor,motor))
        {
            state.executeStep74=false;
            state.executeStep76=true;
        }
    else if(state.executeStep76)
    {
      if(xitr<= (itBF/2))
      {
        motor.bot_Backward_withPWM(80);
        if(xitr==itBF/2)
        {
          motor.bot_Stop();
          stopFlag=true;
        }
      }
      else
      {
        motor.bot_Forward_withPWM(80);
      }
      xitr++;
      if(xitr>itBF)
      {
        state.executeStep76=false;
        state.executeStep8=true;
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

// Navigates to Pickup the Block from White Spaces
void navigate3(botData& newSensor,botData& oldSensor,Motor& motor)
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
          motor.strafe_Right_withPWM(160);
      }
      else if(state.digiCounter==1 && !newSensor.isFrontTurnComplete())
      {
          itr=2;
          motor.strafe_Right_withPWM(160);
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
      // Go Forward Until digi-Count == 4 and Turn Right
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
          motor.spot_Right_withPWM(SPOT_LEFT_PWM);
        }
        else if(!newSensor.isFrontTurnComplete())
        {
          temp = false;
          itr=5;
          motor.spot_Right_withPWM(SPOT_LEFT_PWM);
        }
        else
        {
          itr=6;
          motor.bot_Stop();
          stopFlag=true;
          state.executeStep3=false;
          state.executeStep35=true;
          temp=true;
          temp2=true;
      }
    }

    else if(state.executeStep35)
    {
    	
    	if(newSensor.tofSide > 140 && temp)
    	{
    		followLine(newSensor,oldSensor,motor);
    	}
    	else if(temp)
    	{
    		stopFlag=true;
    		temp=false;
    	}
    	else if(newSensor.isFrontTurnComplete() && temp2)
    	{
    		state.digiCounter=0;
    		motor.spot_Left_withPWM(SPOT_LEFT_PWM);
    	}
    	else if(state.digiCounter<1)
    	{
    		temp2=false;
    		motor.spot_Left_withPWM(SPOT_LEFT_PWM);
    	}
    	else
    	{
    		motor.bot_Stop();
    		stopFlag=true;
    		state.executeStep35=false;
    		state.executeStep4=true;
    	}
    }

    // Step 4:
      // Go Forward for few Seconds and Strafe Right for few Iterations

    else if(state.executeStep4)
    {
      if(strafeItr<=maxStrafeItr)
      {
        itr=7;
        if(strafeItr  <= int((maxStrafeItr)/3)    )
        {
          motor.bot_Forward_withPWM(100);
          processPID(newSensor,oldSensor,motor);
        }
        else if(strafeItr  <= int((maxStrafeItr)*2/3 ))
        {
          motor.strafe_Right_withPWM(100);
        }
        else
        {
          motor.bot_Forward_withPWM(100);
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
        temp=true;
        state.digiCounter=0;
      }

    }


    // Step 5:
        // Strafe Left Until the Bot is Back on Line

    else if(state.executeStep5)
    {
      if(temp)
      {
        disableCordinator();
        temp=false;  
      }
      
      if(state.digiCounter<1)
      {
        itr=9;
        motor.bot_Backward_withPWMm(100);
      }
      else if(!newSensor.isFrontTurnComplete())
      {
      	motor.spot_Left_withPWM(100);
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
      }
    }


    // Step 6:
        // Bot Reverse Until Junction Counter == 1 and then Spot-Right
    else if(state.executeStep6)
    {
      if(state.digiCounter<1)
        {
          itr=11;
          followLine(newSensor,oldSensor,motor);
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
          {
            processPID(newSensor,oldSensor,motor);
            motor.bot_Forward_withPWMm(150);
          }
      else if(balanceWithTOF(170,newSensor,motor) && K_processPID(newSensor,oldSensor,motor,105,80,0.11))

        {
          tfi++;
          itr=14;
          cout<<"Balancing with TOF"<<endl;
          if(tfi>=maxTf)
          {
            state.executeStep7=false;
            state.executeStep75=true;
            tfi=0;
          }
        }
    }

    else if (state.executeStep75)
    {
        cout<<"TFI:="<<tfi<<endl;
        K_processPID(newSensor,oldSensor,motor,105,80,0.11);
        motor.bot_Forward_withPWMm(0);
       if( abs(newSensor.errorFront) <= LF_THRESH && abs(newSensor.errorBack) <= LF_THRESH )
        {
          tfi++;
        }
        else
        {
          tfi=0;
	  cout<<"Resetting"<<endl;
        }
      
      if(tfi >=LF_MAX)
      {
        motor.bot_Stop();
        stopFlag=true;
        state.digiCounter=0;
        state.executeStep75=false;
        state.executeStep76=true;
        stackBlock();
      }
    }

    else if(state.executeStep76)
    {
      if(xitr<= (itBF/2))
      {
        motor.bot_Backward_withPWM(80);
        if(xitr==itBF/2)
        {
          motor.bot_Stop();
          stopFlag=true;
        }
      }
      else
      {
        motor.bot_Forward_withPWM(80);
      }
      xitr++;
      if(xitr>itBF)
      {
        state.executeStep76=false;
        state.executeStep8=true;
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
            // navigates from home 2 stack the block with the block in Arm
      navigate2(newSensor,oldSensor,motor);
      
            // Navigates from home 2 pickup the block and Stack
      // navigate2 (newSensor,oldSensor,motor);
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
      motor.bot_Backward_withPWMm(BALANCE_WITH_TOF_PWM);
    }
    else
    {
      motor.bot_Forward_withPWMm(BALANCE_WITH_TOF_PWM);
    }
    return false;
  }
  return true;
}

