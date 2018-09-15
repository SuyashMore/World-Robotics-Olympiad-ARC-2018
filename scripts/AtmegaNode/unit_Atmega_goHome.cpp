#include "ros/ros.h"

#include "Navigation.cpp"

// include Messages
#include "std_msgs/String.h"
#include "Jetson/ControlSignal.h"
#include "Jetson/CtrlSigResponse.h"

#include "Jetson/Dyx2.h"
#include "Jetson/bot.h"

// Flag to Control the Output for the Motor
bool shouldPublish =false;

// Global Instance Variables
botData storage; //Used to Store History Data
Motor motor; 



	
void botCallBack(const Jetson::bot::ConstPtr& msg);
void handleArmSignal();
void inputCallback(const std_msgs::String::ConstPtr& msg);

ros::Publisher atmegaPub ;
ros::Publisher servoPub ;

int main(int argc,char **argv)
{
	ros::init(argc,argv,"Atmega_listener");
	ros::NodeHandle n;
	ros::Subscriber atmegaSub = n.subscribe("AtmegaOut",100,inputCallback);
	ros::Subscriber botDataSub = n.subscribe("botData",100,botCallBack);


	atmegaPub = n.advertise<std_msgs::String>("AtmegaIn",100);
	servoPub = n.advertise<Jetson::Dyx2>("Dyx",100);
	
	ros::spin();

	return 0;
}

	
// Handles Control Back to the Node After Processing the Arm
void botCallBack(const Jetson::bot::ConstPtr& msg)
{
	if(msg->nav)
		navFlag=true;
}


void handleArmSignal()
{	
	cout<<"-------------------------Latching Data to Servo-Node --------------------------------------"<<endl;
	Jetson::Dyx2 servo;
	servo.cordinator=cordinator;
	servo.pickUp=pickup;
	servo.stack=stackBlk;
	servo.mode = mode;
	servoPub.publish(servo);
	
	if(mode==0)
	{
		navFlag=false;
	}
	else
	{
		mode=0;
		navFlag=true;
	}
	enableArmControl=false;
	
	if(pickup)
		pickup=false;
	if(stackBlk)
		stackBlk=false;
}


// //Modify This Variable for Debugging Purpose
// state.currentStepIndex=0;		

void stackBlock_withPID(botData& newSensor,botData& oldSensor,Motor& motor)
{
	if(state.currentStepIndex==1)		//Stack the Block
	{
		cout<<"Navigation Step:"<<1<<endl;
		if(goHome(newSensor,oldSensor,motor))
		{
			state.currentStepIndex++;
		}

	}
	else if(state.currentStepIndex==2)
	{
		cout<<"Navigation Step:"<<2<<endl;
		stopFlag=true;
	}
	
}

void masterLoopStack(botData& newSensor,botData& oldSensor,Motor& motor)
{
	if(!stopFlag)
    {
            // navigates from gome 2 stack the block with the block in Arm
	cout<<"Hello"<<endl;
      stackBlock_withPID(newSensor,oldSensor,motor);


      
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



// Handles the Decryption And Processing of the Message Received
void inputCallback(const std_msgs::String::ConstPtr& msg)
{
	// Check for Arm Signals
	if(enableArmControl)
	{
		navFlag=false;
		handleArmSignal();
	}

	string m;
	m=msg->data.c_str();
	botData bt;
	bt.decrpty_message(m);
	bt.printData();
	cout<<stopFlag<<endl;
	state.printData();
	cout<<"Game State:"<<itr<<endl;
	// Process Only After The Servo-Node had Completed Processing
	if(navFlag) 			
	{

		// Print the Delay Iterations
		if(stopFlag)
			cout<<"Stop Flag -Iterations Remaining :"<<(maxStopFlagItr-stopFlagIterations)<<endl;
		cout<<"--------------------------------------------------------"<<endl;

		masterLoopStack(bt,storage,motor);
		
		//goHome(bt,storage,motor);
		// Process_data and then enable the Publish Flag
		
		std_msgs::String msg;
			
		msg.data = motor.encrypt_message();
		atmegaPub.publish(msg);

			// Handle the Preseve History Calls
		if(!bt.preserveHistoryF)
			storage.copyFront(bt);
		if(!bt.preserveHistoryB)
			storage.copyBack(bt);
	}
	else
	{
		cout<<"Processing Arm !!!!!"<<endl;
		std_msgs::String msg;
		motor.bot_Stop();
		motor.setPWM_all(0);
		msg.data = motor.encrypt_message();
		atmegaPub.publish(msg);		
	}


}
