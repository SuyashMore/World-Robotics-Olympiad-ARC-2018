#include "ros/ros.h"

#include "Navigation.cpp"

// include Messages
#include "std_msgs/String.h"
#include "Jetson/ControlSignal.h"
#include "Jetson/CtrlSigResponse.h"

#include "Jetson/Dyx.h"
#include "Jetson/bot.h"

// Flag to Control the Output for the Motor
bool shouldPublish =false;

// Global Instance Variables
botData storage; //Used to Store History Data
Motor motor; 


	
void botCallBack(const Jetson::bot::ConstPtr& msg);
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
	servoPub = n.advertise<Jetson::Dyx>("Dyx",100);
	
	ros::spin();

	return 0;
}

	

void botCallBack(const Jetson::bot::ConstPtr& msg)
{
	if(msg->nav)
		navFlag=true;
}




// Handles the Decryption And Processing of the Message Received
void inputCallback(const std_msgs::String::ConstPtr& msg)
{
	
	// ROS_INFO("I heard: [%s]", msg->data.c_str());
	string m;
	m=msg->data.c_str();
	botData bt;
	bt.decrpty_message(m);
	bt.printData();
	cout<<"Digi-Counter:"<<state.digiCounter<<endl;
	cout<<"Game State:"<<itr<<endl;


	// Print the Delay Iterations
	if(stopFlag)
		cout<<"Stop Flag -Iterations Remaining :"<<(maxStopFlagItr-stopFlagIterations)<<endl;
	cout<<"--------------------------------------------------------"<<endl;


	// Print the Nav Flag

	// Process Only After The Servo-Node had Completed Processing
		if(navFlag) 			
		{
			mainLoop(bt,storage,motor);
		// Process_data and then enable the Publish Flag
		
			std_msgs::String msg;
			
			msg.data = motor.encrypt_message();
			atmegaPub.publish(msg);

		}
		else
		{
			cout<<"Processing ARm !!!!!"<<endl;
		}

		if(cordinator | pickup | stackBlock)
		{	
			cout<<"-------------------------Latching Data to Servo-Node --------------------------------------"<<endl;
			Jetson::Dyx servo;
			servo.cordinator=cordinator;
			servo.pickUp=pickup;
			servo.stack=stackBlock;

			cordinator=false;
			pickup=false;
			stackBlock=false;

			servoPub.publish(servo);
			navFlag=false;
		}


		// Handle the Preseve History Calls
		if(!bt.preserveHistoryF)
			storage.copyFront(bt);
		if(!bt.preserveHistoryB)
			storage.copyBack(bt);

}