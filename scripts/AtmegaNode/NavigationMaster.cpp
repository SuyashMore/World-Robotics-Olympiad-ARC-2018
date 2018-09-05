#pragma once

#include "Navigation.cpp"

void nav_Complete_1_Row(botData& newSensor,botData& oldSensor,Motor& motor)
{
	if(currentStepIndex == 1)		//Navigate to Main Line 
	{
		if(nav_2_MainLine(newSensor,oldSensor,motor))
		{
			currentStepIndex++;
		}
	}
	else if(currentStepIndex == 2)	//Go Forward One Junction
	{
		if(nav_goForward_1_Junction(newSensor,oldSensor,motor))
		{
			currentStepIndex++;
		}
	}
	else if( currentStepIndex ==3 )		//Go Forward One Junction
	{
		if(nav_goForward_1_Junction(newSensor,oldSensor,motor))
		{
			currentStepIndex++;
		}
	}
	else if(currentStepIndex==2)	//Rotate and the Pickup the Block from Supply Line and then Return Back to the Same
	{
		if(nav_Rotate_n_Pickup_block_from_MainJunction_Supply_and_return(newSensor,oldSensor,motor))
		{
			currentStepIndex++;
		}
	}
	else if(currentStepIndex==3)		//Stack the Block
	{
		if(stack_the_Block_from_MainJunction_at_hx(150,newSensor,motor))
		{
			currentStepIndex++;
		}

	}
	else if(currentStepIndex==4)
	{

	}

}