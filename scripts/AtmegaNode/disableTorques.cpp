#include "ros/ros.h"
#include <unistd.h>

#include "Navigation.cpp"

#include "Jetson/Dyx2.h"



ros::Publisher atmegaPub ;	

int main(int argc,char **argv)
{
	ros::init(argc,argv,"Debug_Node_arm");

	ros::NodeHandle n;

	atmegaPub = n.advertise<Jetson::Dyx2>("Dyx",100);
		
	usleep(1000000);
		
	Jetson::Dyx2 msg;
	msg.cordinator=false;
	msg.pickUp=true;
	msg.stack=false;
	msg.mode=11;
	atmegaPub.publish(msg);

	ros::spinOnce()	;

	return 0;
}
