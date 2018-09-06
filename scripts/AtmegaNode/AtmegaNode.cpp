#include "ros/ros.h"

#include "NavigationMaster.cpp"

// include Messages
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"

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
void handleArmSignal();
void inputCallback(const std_msgs::String::ConstPtr& msg);
void LidarCallBack(const std_msgs::Int16::ConstPtr& msg);

ros::Publisher atmegaPub ;
ros::Publisher servoPub ;



int main(int argc,char **argv)
{
	ros::init(argc,argv,"Atmega_listener");
	ros::NodeHandle n;
	ros::Subscriber atmegaSub = n.subscribe("AtmegaOut",100,inputCallback);
	ros::Subscriber botDataSub = n.subscribe("botData",100,botCallBack);
	ros::Subscriber lidarSub = n.subscribe("LIDAR_Data",100,LidarCallBack);


	atmegaPub = n.advertise<std_msgs::String>("AtmegaIn",100);
	servoPub = n.advertise<Jetson::Dyx>("Dyx",100);
	
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
	Jetson::Dyx servo;
	servo.cordinator=cordinator;
	servo.pickUp=pickup;
	servo.stack=stackBlk;

	servoPub.publish(servo);
	navFlag=false;
	enableArmControl=false;

	if(pickup)
		pickup=false;
	if(stackBlk)
		stackBlk=false;
}

int cbr=0;
int cbrate=0;

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
	cout<<"Digi-Counter:"<<state.digiCounter<<endl;
	cout<<"Game State:"<<itr<<endl;
	cout<<"Callback-Rate"<<cbrate<<endl;

	// Process Only After The Servo-Node had Completed Processing
	if(navFlag) 			
	{

		// Print the Delay Iterations
		if(stopFlag)
			cout<<"Stop Flag -Iterations Remaining :"<<(maxStopFlagItr-stopFlagIterations)<<endl;
		cout<<"--------------------------------------------------------"<<endl;

	
		// mainLoop(bt,storage,motor);
		masterLoop(bt,storage,motor);
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
	}
}
void LidarCallBack(const std_msgs::Int16::ConstPtr& msg)
{
	Lidar = msg->data;
}


