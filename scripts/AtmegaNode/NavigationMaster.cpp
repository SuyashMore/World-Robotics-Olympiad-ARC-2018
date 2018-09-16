#pragma once
#include "Navigation.cpp"



// //Modify This Variable for Debugging Purpose
// state.currentStepIndex=0;		

int currentNavStep = 0;
int Target_Location=0;
int navIterator=0;
int currentBlockColor = 0;

bool NavLogic(botData& newSensor,botData& oldSensor,Motor& motor)
{
	if(NavigationOrder[currentNavStep] == SUPPLY2)
	{
		bool ret = nav_PickupBlock_from__SupplyLine(newSensor,oldSensor,motor);
		if(ret)
		{
			currentBlockColor= BlockColor[2];
			navIterator++;
		}
			
		return ret;
	}
	else if(NavigationOrder[currentNavStep] == SUPPLY1)
	{
		if(navIterator==1)
		{
			bool ret = nav_goBackward_1_Junction(newSensor,oldSensor,motor);
			if(ret)
				navIterator++;
			return ret;
		}
		else if(navIterator==2)
		{
			bool ret = nav_PickupBlock_from__SupplyLine(newSensor,oldSensor,motor);
			if(ret)
			{
				currentBlockColor= BlockColor[1];
				navIterator++;
			}
				
			return ret;
		}
		else if(navIterator==3)
		{
			bool ret = nav_goForward_1_Junction(newSensor,oldSensor,motor);
			if(ret)
				navIterator=0;;
			return ret;
		}
	}
	else if(NavigationOrder[currentNavStep] == JUDGEPART)
	{
		int judgeBlock = BlockColor[0];
		int targetHX = hx_ORDER[judgeBlock][requiredBlockIndex];
		stack_the_Block_from_MainJunction_at_hx(targetHX,newSensor,oldSensor,motor);
	}
	
	else if(NavigationOrder[currentNavStep] == WHITE1)
	{

	}
	else if(NavigationOrder[currentNavStep] == WHITE2)
	{

	}
	else if(NavigationOrder[currentNavStep] == WHITE3)
	{

	}
	else if(NavigationOrder[currentNavStep] == CHUTE)
	{

	}
}

bool NavWithButtons(botData& newSensor,botData& oldSensor,Motor& motor)
{
		if(state.currentStepIndex == 1)		//Navigate to Main Line 
	{
		cout<<"Navigation Step:"<<1<<endl;
		if(nav_2_MainLine(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;

		}
	}
	else if(state.currentStepIndex == 2)	//Go Forward One Junction
	{
		cout<<"Navigation Step:"<<2<<endl;
		if(nav_goForward_1_Junction(newSensor,oldSensor,motor))
		{
			move_Arm_down();
			state.currentStepIndex++;
		}
	}
	else if(state.currentStepIndex == 3)	//Go Forward One Junction
	{
		cout<<"Navigation Step:"<<3<<endl;
		if(nav_goForward_1_Junction(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}
	}
	else if(state.currentStepIndex==4)	//Rotate and the Pickup the Block from Supply Line and then Return Back to the Same
	{
		cout<<"Navigation Step:"<<4<<endl;
		if(nav_PickupBlock_from__SupplyLine(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}
	}
	else if(state.currentStepIndex==5)		//Stack the Block
	{
		cout<<"Navigation Step:"<<5<<endl;
		if(stack_the_Block_from_MainJunction_at_hx(cvt2HX(placeVector[0]),newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}

	}
	else if(state.currentStepIndex == 6)	//Go Forward One Junction
	{
		cout<<"Navigation Step:"<<6<<endl;
		if(nav_goBackward_1_Junction(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}
	}
	else if(state.currentStepIndex==7)
	{
		cout<<"Navigation Step:"<<7<<endl;
		if(nav_PickupBlock_from__SupplyLine(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}
		
	}
	else if(state.currentStepIndex==8)
	{
		cout<<"Navigation Step:"<<8<<endl;
		if(nav_goForward_1_Junction(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}
	}
	else if(state.currentStepIndex==9)
	{
		cout<<"Navigation Step:"<<9<<endl;
		if(stack_the_Block_from_MainJunction_at_hx(cvt2HX(placeVector[1]),newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}
	}
	else if(state.currentStepIndex==10)
	{
		cout<<"Navigation Step:"<<10<<endl;
		if(nav_goBackward_1_Junction(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}
		
	}
	else if(state.currentStepIndex==11)
	{
		// cout<<"Navigation Step:"<11<<endl;
		if(goHome(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}
		
	}
	else
	{
		motor.bot_Stop();
	}

}


void nav_Complete_1_Row(botData& newSensor,botData& oldSensor,Motor& motor)
{
	if(state.currentStepIndex == 1)		//Navigate to Main Line 
	{
		cout<<"Navigation Step:"<<1<<endl;
		if(nav_goBackward_1_Junction(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}
	}
	else
	{
		motor.bot_Stop();
	}

}

void allAtmegaNode(botData& newSensor,botData& oldSensor,Motor& motor)
{
	if(isButtonDataReceived)
	{
		if(!stopFlag)
	    {
	      NavWithButtons(newSensor,oldSensor,motor);
	    }
	  	else
	    {
	      motor.bot_Stop();
	      handle_delay();		// Loop through Stop for Certain Iterations
	    }
    }	
}

void masterLoop(botData& newSensor,botData& oldSensor,Motor& motor)
{
	if(!stopFlag)
    {
      NavWithButtons(newSensor,oldSensor,motor);
    }
  else
    {
      motor.bot_Stop();
      handle_delay();		// Loop through Stop for Certain Iterations
    }
}

