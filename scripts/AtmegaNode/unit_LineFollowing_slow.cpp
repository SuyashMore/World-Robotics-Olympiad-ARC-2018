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

// Handles the Decryption And Processing of the Message Received
void inputCallback(const std_msgs::String::ConstPtr& msg)
{
	// Check for Arm Signals
	if(enableArmControl)
	{
		navFlag=false;
		handleArmSignal();
	}
	navFlag=true;

	string m;
	m=msg->data.c_str();
	botData bt;
	bt.decrpty_message(m);
	bt.printData();
	state.printData();
	cout<<"Game State:"<<itr<<endl;

	// Process Only After The Servo-Node had Completed Processing
	if(navFlag) 			
	{

		// Print the Delay IWterations
		if(stopFlag)
			cout<<"Stop Flag -Iterations Remaining :"<<(maxStopFlagItr-stopFlagIterations)<<endl;
		cout<<"--------------------------------------------------------"<<endl;

		//followLine(bt,storage,motor);

		K_processPID(newSensor,oldSensor,motor,110,80,0.11);
  		motor.bot_Forward_withPWMm(140);
		
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
	}


}
