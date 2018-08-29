#include "ros/ros.h"
#include <unistd.h>

#include "Navigation.cpp"

#include "Jetson/Dyx.h"



ros::Publisher atmegaPub ;	

int main(int argc,char **argv)
{
	ros::init(argc,argv,"Debug_Node_arm");

	ros::NodeHandle n;

	atmegaPub = n.advertise<Jetson::Dyx>("Dyx",100);
		
	usleep(1000000);
	
		Jetson::Dyx msg;
		msg.cordinator=false;
		msg.pickUp=false;
		msg.stack=false;
		atmegaPub.publish(msg);
	
		ros::spinOnce()	;

	return 0;
}
