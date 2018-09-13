#include "ros/ros.h"

#include "NavigationMaster.cpp"

// include Messages

#include "Jetson/blkData.h"
#include "Jetson/toCam.h"

void ipCallback(const Jetson::blkData::ConstPtr& msg);

ros::Publisher camPub;


int main(int argc,char **argv)
{
	ros::init(argc,argv,"Atmega_listener");
	ros::NodeHandle n;
	ros::Subscriber camSub = n.subscribe("blockColors",100,ipCallback);

	camPub = n.advertise<Jetson::toCam>("camTopic",100);
	usleep(1000000);
	
    Jetson::toCam msg;
    msg.location = 1;

    camPub.publish(msg);

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
    cout<<"Colors Received Are : "<<BlockColor[0]<<","<<BlockColor[1]<<","<<BlockColor[2]<<endl;
}


