#include "ros/ros.h"

#include "LineFollowing.cpp"

// include Messages
#include "std_msgs/String.h"
#include "Jetson/ControlSignal.h"
#include "Jetson/CtrlSigResponse.h"

// Flag to Control the Output for the Motor
bool shouldPublish =false;


botData storage; //Used to Store History Data
Motor motor; 

// Handles the Decryption of the Message Received
void inputCallback(const std_msgs::String::ConstPtr& msg)
{
	
	ROS_INFO("I heard: [%s]", msg->data.c_str());
	string m;
	m=msg->data.c_str();
	botData bt;
	bt.decrpty_message(m);
	bt.printData();
	cout<<"-----------------------------------------------------------------------------"<<endl;


	loop(bt,storage,motor);
	// Process_data and then enable the Publish Flag
	shouldPublish = true;
	if(!bt.preserveHistoryF)
		storage.copyFront(bt);
	if(!bt.preserveHistoryB)
		storage.copyBack(bt);
}	



int main(int argc,char **argv)
{
	ros::init(argc,argv,"Atmega_listener");
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("AtmegaOut",100,inputCallback);

	ros::Publisher pub = n.advertise<std_msgs::String>("AtmegaIn",100)	;
	
	ros::Rate loop_rate(ROS_LOOP_RATE);

	while(ros::ok())
	{
		if(shouldPublish)
		{
			std_msgs::String msg;
			// // Modify the Contents
			msg.data = motor.encrypt_message();
			cout<<"Motor Output Data:"<<endl;
			motor.printData();

			cout<<"Writing : "<<msg.data<<endl;

			pub.publish(msg);

			shouldPublish = false;
		}

		ros::spinOnce();

		loop_rate.sleep();
	}	

	return 0;
}