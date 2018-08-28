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
	cout<<"Nav_flag = "<<navFlag<<endl;

	// Process Only After The Servo-Node had Completed Processing
	if(navFlag) 			
		{
			mainLoop(bt,storage,motor);
	// Process_data and then enable the Publish Flag
	shouldPublish = true;
	if(!bt.preserveHistoryF)
		storage.copyFront(bt);
	if(!bt.preserveHistoryB)
		storage.copyBack(bt);
	}
}	



int main(int argc,char **argv)
{
	ros::init(argc,argv,"Atmega_listener");
	ros::NodeHandle n;

	ros::Subscriber atmegaSub = n.subscribe("AtmegaOut",100,inputCallback);
	ros::Subscriber botDataSub = n.subscribe("botData",100,botCallBack);

	ros::Publisher atmegaPub = n.advertise<std_msgs::String>("AtmegaIn",100)	;
	ros::Publisher servoPub = n.advertise<Jetson::Dyx>("Dyx",100)	;
	
	ros::Rate loop_rate(ROS_LOOP_RATE);

	while(ros::ok())
	{
		if(shouldPublish)
		{
			std_msgs::String msg;
			
			msg.data = motor.encrypt_message();
			atmegaPub.publish(msg);

			// Turn of the Publish Flag (Only Operates on Live-Incomming Data)
			shouldPublish = false;
		}


		if(cordinator || pickup || stackBlock)
		{
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
		

		ros::spinOnce();

		loop_rate.sleep();
	}
	return 0;
}

