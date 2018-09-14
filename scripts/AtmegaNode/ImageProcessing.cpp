#include "ros/ros.h"

#include "NavigationMaster.cpp"

// include Messages
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"

#include "Jetson/blkData.h"
#include "Jetson/toCam.h"


// Flag to Control the Output for the Motor
bool shouldPublish =false;

// Global Instance Variables
botData storage; //Used to Store History Data
Motor motor; 

void ipCallback(const Jetson::blkData::ConstPtr& msg);

ros::Publisher camPub;


int main(int argc,char **argv)
{
	ros::init(argc,argv,"Atmega_listener");
	ros::NodeHandle n;
	ros::Subscriber camSub = n.subscribe("blockColors",100,ipCallback);

	camPub = n.advertise<Jetson::toCam>("camTopic",100);
	
	ros::spin();

	return 0;
}



void ipCallback(const Jetson::blkData::ConstPtr& msg)
{
	navFlag=true;
	int BlockColor[6];    // Judge , Supply1 ,supply 2, white 1,white 2,white 3
	BlockColor[0]=msg->pos3;		//Judge piece
	BlockColor[1]=msg->pos1;		//Supply 1
	BlockColor[2]=msg->pos2;		//Supply 2
}

