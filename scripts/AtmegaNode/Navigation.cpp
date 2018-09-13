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
	     //stopFlag=true;
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
    state.digiCounterR=0;
	}

	if(state.digiCounterR<1)
	{
    cout<<"Currently Executing: Follow Line Back"<<endl;
          followLineBack(newSensor,oldSensor,motor);
	}
	else
	{
		temp4=true;
    state.digiCounterR=0;
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


// Stack Block at Horizontal Distance From the Wall
int temp02=true;
int miniEx02=1;
int miniTemp = 0;
int q=0;
int d=0;
int historyError = 0;
int direction = DIR_NULL; //Stores the Direction Variable to Return Back on the Line
bool stack_the_Block_from_MainJunction_at_hx(float targetDistance,botData& newSensor,botData& oldSensor,Motor& motor,int slideDir = DIR_NULL )
{
    state.updateDigiCounter(newSensor,oldSensor,motor);
    motor.reset(); 

  	if(miniEx02==1)   			//Reach at an Balancing Distance from the TOF and Balance
  	{
  		if(newSensor.tofFront>(TOF_FRONT_BALANCE_DISTANCE+TOF_ERROR_THRESH))
          {
              cout<<"Currently Executing: Going Forward Till TOF:Forward"<<endl;
  			// processPID(newSensor,oldSensor,motor);
              K_processPID(newSensor,oldSensor,motor,110,80,0.11);
  			motor.bot_Forward_withPWMm(140);
              q=0;   
          }
          else if(newSensor.tofFront<(TOF_FRONT_BALANCE_DISTANCE-TOF_ERROR_THRESH))
          {
              cout<<"Currently Executing: Going Forward Till TOF:Backward"<<endl;
              K_processPID(newSensor,oldSensor,motor,110,80,0.11);
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
      K_processPID(newSensor,oldSensor,motor,105,90,0.5);
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
        miniEx02=3;
        q=0;
        stopFlag=true;
        if(newSensor.tofSide>targetDistance)
        {
          direction=DIR_LEFT;
        }
        else
        {
          direction=DIR_RIGHT;
        }

      }	
  	}
  	else if(miniEx02==3)		//Aligning with the Wall
  	{

         cout<<"Currently Executing: Correcting with Side"<<endl;
          if(newSensor.tofSide > targetDistance)
          {
              motor.strafe_Left_withPWM(110);
          }
          else if(newSensor.tofSide < targetDistance)
          {
              motor.strafe_Right_withPWM(110);
          }
          if(abs(newSensor.tofSide - targetDistance) <=8)
          {

              motor.bot_Stop();
              motor.setPWM_all(0);
              q++;
          }
          if(q>=24)
          {
              q=0;
              miniEx02=4;
              stackBlock();
              stopFlag=true;
          }
    }
  	else if(miniEx02==4)		// Pull out the Arm and Push the Block in
  	{
          cout<<"Currently Executing: Bot Back and Push"<<endl;
  		    if(q<= (PULL_AND_PUSH_ITR/2))    //Move the Bot Backward 
        	{
  	        motor.bot_Backward_withPWM(100);
  	        if(q==PULL_AND_PUSH_ITR/2)
  	        {
  	          motor.bot_Stop();
              arm_pushAndPullPosition();      //Sets the Arm Sightly Above the Normal Level So that it can Push the Block Back in
  	          stopFlag=true;
  	        }
        	}
        	else
        	{
          	motor.bot_Forward_withPWM(100);
        	}
        	q++;
        	if(q>PULL_AND_PUSH_ITR)
        	{
          	miniEx02=5;
              state.digiCounter=0;
              temp02=true;
              stopFlag=true;
              q=0;
        	}
  	}
  	else if(miniEx02==5)		//Return Back to the Junction
  	{
      if(q<3)
      {
        motor.bot_Backward_withPWM(120);
        q++;
      }

        if(!newSensor.isFrontTurnComplete() && temp02)
        {
          cout<<"Getting Back on Line"<<endl;
          if(direction==DIR_LEFT)
          {
            motor.strafe_Right_withPWM(100);
          }
          else
          {
            motor.strafe_Left_withPWM(100);
          }
        }
        else if(temp02)
        {
          temp02=false;
          miniEx02=6;
          state.digiCounterR=0;
          state.digiCounter=0;
          q=0;
        }

  	}
    else if(miniEx02==6)
    {
      cout<<"Currently Executing: follow Line Back"<<endl;
      if(state.digiCounter<1)
          {
            followLineBackpwm(newSensor,oldSensor,motor,140);
          }
          else 
          {
            motor.bot_Stop();
            temp02=true;
            miniEx02=1;
            q=0;
            d=0;
            direction=DIR_NULL;
            state.digiCounterR=0;
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
		if(  abs(newSensor.tofSide - WHITE_SPACE_BLOCK_DIST) > WHITE_SPACE_ERROR_THRESH )
		{
			followLine(newSensor,oldSensor,motor);
		}
		else
		{
			motor.bot_Stop();
			stopFlag=true;
			miniEx03=3;
			temp03=true;
      state.digiCounter=0;
		}
	}
	else if(miniEx03==3)         //Step 3: Spot Rotate Left till Perpendicular to the Line
	{
		if(newSensor.isFrontTurnComplete() && temp03)
		{
			motor.spot_Left_withPWM(SPOT_LEFT_PWM);
		  state.digiCounter=0;
    }

		else if(state.digiCounter<1)
		{
			temp03=false;
      motor.spot_Left_withPWM(SPOT_LEFT_PWM);
		}
		else
		{
			motor.bot_Stop();
      stopFlag=true;
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
		else if(!newSensor.isFrontTurnComplete() || !newSensor.isBackTurnComplete())
		{
      if(!newSensor.isFrontTurnComplete())
      {
        motor.spot_Left_withPWM(SPOT_LEFT_PWM);
      }
      else if(!newSensor.isBackTurnComplete())
      {
        motor.setPWM_all(0);
        motor.spot_Right();
        motor.setPWMof(MOTOR_BACK,120);
      }
			
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
		else if(!newSensor.isFrontTurnComplete() || !newSensor.isBackTurnComplete())
		{
			temp03=false;
      if(!newSensor.isFrontTurnComplete())
			{
        motor.spot_Right_withPWM(SPOT_ROTATE_PWM);
      }
      else if(!newSensor.isBackTurnComplete())
      {
        motor.setPWM_all(0);
        motor.spot_Left();
        motor.setPWMof(MOTOR_BACK,120);
      }
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
int r=0;
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
    if(newSensor.tofFront>(DELIVERY_CHUTE_STOP_DISTANCE)*1.5)
    {
      followLine(newSensor,oldSensor,motor);
    }
    else if(newSensor.tofFront>(DELIVERY_CHUTE_STOP_DISTANCE+30))
    {
      cout<<"Currently Executing: Going Forward Till TOF:Forward"<<endl;
      // processPID(newSensor,oldSensor,motor);
      K_processPID(newSensor,oldSensor,motor,95,80,0.11);
      motor.bot_Forward_withPWMm(100);
      r=0;   
    }
    else if(newSensor.tofFront<(DELIVERY_CHUTE_STOP_DISTANCE-30))
    {
      cout<<"Currently Executing: Going Forward Till TOF:Backward"<<endl;
      K_processPID(newSensor,oldSensor,motor,95,80,0.11);
      motor.bot_Backward_withPWMm(101);   
      r=0;
    }
    else
    {
     r++;
    }
    if(r>10)
    {
      miniEx04=3;
      r=0;
    }

	}
	else if(miniEx04 == 3)
	{
    stopFlag=true;
		miniEx04=4;
	}
	else if(miniEx04 == 4)
	{
		if(strafeMode4==1)
    {
      if(strafeItr04 <= 2 * PICKUP_1_ITR_MAX)
      {
        motor.strafe_Right_withPWM(STRAFE_PICKUP);
      }
      else
      {
        strafeMode4++;
        strafeItr04=0;
      }
    }
    else if(strafeMode4 == 2)
    {
      if(strafeItr04 <=  2*PICKUP_2_ITR_MAX/2)
      {
        motor.bot_Forward_withPWM(STRAFE_PICKUP);
      }
      else
      {
        strafeMode4++;
        strafeItr04=0;
      }

    }
    else if(strafeMode4==3)
    {
      if(strafeItr04 <=PICKUP_3_ITR_MAX)
      {
        motor.strafe_Right_withPWM(STRAFE_PICKUP);
      }
      else
      {
        strafeMode4++;
      }

    }
    else if(strafeMode4==4)
    {
      miniEx04=5;
    }
    strafeItr04++;
	}
  else if(miniEx04==5)
  {
    if(!newSensor.isFrontTurnComplete())
    {
      motor.strafe_Left_withPWM(STRAFE_PICKUP);
    }
    else{
      state.digiCounter=0;
      state.digiCounterR=0;
      miniEx04=6;
    }
  }
  else if(miniEx04==6)
  {
      if(state.digiCounterR<1)
      {
        followLineBack(newSensor,oldSensor,motor);
      }
      else if(newSensor.isFrontTurnComplete() && temp03)
      {
        motor.spot_Left_withPWM(SPOT_ROTATE_PWM);
      }
      else if(!newSensor.isFrontTurnComplete() || !newSensor.isBackTurnComplete())
      {
        temp03=false;
        if(!newSensor.isFrontTurnComplete())
        {
          motor.spot_Left_withPWM(SPOT_ROTATE_PWM);
        }
        else if(!newSensor.isBackTurnComplete())
        {
          motor.setPWM_all(0);
          motor.spot_Right();
          motor.setPWMof(MOTOR_BACK,120);
        }
      }
      else
      {
        temp04=true;
        strafeItr04=0;
        strafeMode4=1;
        miniEx04=1;
        return true;
      }
  }
  return false;
  
}

int miniEx05=1;
bool temp05=true;
bool tempturn5=false;
bool goHome(botData& newSensor,botData& oldSensor,Motor& motor)			//Go to Home Position from the Junction behind Main Junction
{
  state.updateDigiCounter(newSensor,oldSensor,motor);
  motor.reset(); 
  // Mini - Step 1 : Handle Rotation and Enable 90 degrees
  if(miniEx05==1)
  {
    if(newSensor.isFrontTurnComplete() && temp01)
      {
        cout<<"Currently Executing: Spot Left"<<endl;
        motor.spot_Left_withPWM(SPOT_LEFT_PWM);
      }
      else if(!newSensor.isFrontTurnComplete())
      {
        cout<<"Currently Executing: Spot Left"<<endl;
        temp05 = false;
        tempturn5=true;
        motor.spot_Left_withPWM(SPOT_LEFT_PWM);
      }
     else if(!newSensor.isBackTurnComplete() && tempturn5)
      {
        motor.setPWM_all(0);
        motor.spot_Right();
        motor.setPWMof(MOTOR_BACK,170);
      }
      else
      {
        motor.bot_Stop();
        stopFlag=true;
        miniEx05=2;
    }
  }
  else if(miniEx05==2)      //Mini Step 2 :Balance with Front Wall
  {
    if(newSensor.tofFront > (HOME_FRONT_X+HOME_ERROR_THRESH))
    {
      cout<<"Currently Executing: Going Forward Till TOF:Forward"<<endl;
      // processPID(newSensor,oldSensor,motor);
      K_processPID(newSensor,oldSensor,motor,110,80,0.11);
      motor.bot_Forward_withPWMm(140);
      q=0;   
    }
    else if(newSensor.tofFront<(HOME_FRONT_X-HOME_ERROR_THRESH))
    {
      cout<<"Currently Executing: Going Forward Till TOF:Backward"<<endl;
      K_processPID(newSensor,oldSensor,motor,110,80,0.11);
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
      miniEx05=3;
    }
  }
  else if(miniEx05=3)       //Mini Step 3 : Balance With Side Wall
  {
  	if(newSensor.tofSide > (HOME_SIDE_X+HOME_ERROR_THRESH))
    {
      cout<<"Currently Executing: Going Forward Till TOF:Forward"<<endl;
      motor.strafe_Left_withPWM(140);
      q=0;   
    }
    else if(newSensor.tofFront<(HOME_SIDE_X-HOME_ERROR_THRESH))
    {
      cout<<"Currently Executing: Going Forward Till TOF:Backward"<<endl;
      motor.strafe_Right_withPWM(140);   
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
      miniEx05=4;
    }	 
  }
  if(miniEx05==4)
  {
  	return true;
  }
  return false;
}

