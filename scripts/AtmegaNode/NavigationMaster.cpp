#pragma once

#include "Navigation.cpp"


// //Modify This Variable for Debugging Purpose
// state.currentStepIndex=0;		

void nav_Complete_1_Row(botData& newSensor,botData& oldSensor,Motor& motor)
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
			state.currentStepIndex++;
		}
	}
	else if( state.currentStepIndex ==3 )		//Go Forward One Junction
	{
		cout<<"Navigation Step:"<<3<<endl;
		if(nav_goForward_1_Junction(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}
	}
	else if(state.currentStepIndex==2)	//Rotate and the Pickup the Block from Supply Line and then Return Back to the Same
	{
		cout<<"Navigation Step:"<<4<<endl;
		if(nav_PickupBlock_from__SupplyLine(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}
	}
	else if(state.currentStepIndex==3)		//Stack the Block
	{
		cout<<"Navigation Step:"<<5<<endl;
		if(stack_the_Block_from_MainJunction_at_hx(150,newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}

	}
	else if(state.currentStepIndex==4)
	{
		cout<<"Navigation Step:"<<6<<endl;
		if(nav_goBackward_1_Junction(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}
	}
	else
	{
		motor.bot_Stop();
	}
	// else if(state.currentStepIndex==5)
	// {
	// 	if(nav_PickupBlock_from__SupplyLine(newSensor,oldSensor,motor))
	// 	{
	// 		state.currentStepIndex++;
	// 	}
	// }
	// else if(state.currentStepIndex==6)
	// {
	// 	if(nav_goForward_1_Junction(newSensor,oldSensor,motor))
	// 	{
	// 		state.currentStepIndex++;
	// 	}
	// }
	// else if(state.currentStepIndex==7)
	// {
	// 	if(stack_the_Block_from_MainJunction_at_hx(150,newSensor,oldSensor,motor))
	// 	{
	// 		state.currentStepIndex++;
	// 	}
	// }

}

void masterLoop(botData& newSensor,botData& oldSensor,Motor& motor)
{
	if(!stopFlag)
    {
            // navigates from gome 2 stack the block with the block in Arm
      nav_Complete_1_Row(newSensor,oldSensor,motor);
      
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
