#include "ros/ros.h"

#include "NavigationMaster.cpp"

// include Messages
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"

#include "Jetson/ControlSignal.h"
#include "Jetson/CtrlSigResponse.h"

#include "Jetson/Dyx2.h"
#include "Jetson/bot.h"

// #include "Jetson/blkData.h"
// #include "Jetson/toCam.h"


// Flag to Control the Output for the Motor
bool shouldPublish =false;

// Global Instance Variables
botData storage; //Used to Store History Data
Motor motor; 

void botCallBack(const Jetson::bot::ConstPtr& msg);
void handleArmSignal();
void inputCallback(const std_msgs::String::ConstPtr& msg);
// void ipCallback(const Jetson::blkData::ConstPtr& msg);
void btCallback(const std_msgs::Int16::ConstPtr& msg);


ros::Publisher atmegaPub ;
ros::Publisher servoPub ;
ros::Publisher camPub;


int main(int argc,char **argv)
{
	ros::init(argc,argv,"Atmega_listener");
	ros::NodeHandle n;
	ros::Subscriber atmegaSub = n.subscribe("AtmegaOut",100,inputCallback);
	ros::Subscriber botDataSub = n.subscribe("botData",100,botCallBack);
	// ros::Subscriber camSub = n.subscribe("blockColors",100,ipCallback);
	ros::Subscriber buttonSub = n.subscribe("buttons",100,btCallback);


	atmegaPub = n.advertise<std_msgs::String>("AtmegaIn",100);
	servoPub = n.advertise<Jetson::Dyx2>("Dyx",100);
	// camPub = n.advertise<Jetson::toCam>("camTopic",100);
	
	ros::spin();

	return 0;
}

	
// Handles Control Back to the Node After Processing the Arm
void botCallBack(const Jetson::bot::ConstPtr& msg)
{
	if(msg->nav)
		navFlag=true;
}

void btCallback(const std_msgs::Int16::ConstPtr& msg)
{
		handleButtons(msg->data);
		isButtonDataReceived=true;
		move2standardNorm();

}

// void ipCallback(const Jetson::blkData::ConstPtr& msg)
// {
// 	navFlag=true;
// 	int BlockColor[6];    // Judge , Supply1 ,supply 2, white 1,white 2,white 3
// 	BlockColor[0]=msg->pos3;		//Judge piece
// 	BlockColor[1]=msg->pos1;		//Supply 1
// 	BlockColor[2]=msg->pos2;		//Supply 2
// }



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

	string m;
	m=msg->data.c_str();
	botData bt;
	bt.decrpty_message(m);
	bt.printData();
	state.printData();
	cout<<"Game State:"<<itr<<endl;


	// if(camFlag)
	// {
	// 	navFlag=false;
	// 	Jetson::toCam msg;
	// 	camPub.publish(msg);

	// }

	// Process Only After The Servo-Node had Completed Processing
	// if(navFlag && !camFlag)	

	if(isButtonDataReceived)
	{
		printPlaceVector();
		if(navFlag)			
		{

			// Print the Delay Iterations
			if(stopFlag)
				cout<<"Stop Flag -Iterations Remaining :"<<(maxStopFlagItr-stopFlagIterations)<<endl;
			cout<<"--------------------------------------------------------"<<endl;

		
			masterLoop(bt,storage,motor);
			
			// Publish Motor Data Back to the Atmega Node
			std_msgs::String msg;
			msg.data = motor.encrypt_message();
			atmegaPub.publish(msg);

				// Handle the Preseve History Calls
			if(!bt.preserveHistoryF)
				storage.copyFront(bt);
			if(!bt.preserveHistoryB)
				storage.copyBack(bt);
		}
		else if (!navFlag)
		{
			cout<<"Processing Arm !!!!!"<<endl;
		}
		// else if (camFlag)
		// {
		// 	cout<<"Processing Camera !!!!!"<<endl;
		// }
	}
	else
	{
		cout<<"Waiting for Button Input !!"<<endl;
	}
}


