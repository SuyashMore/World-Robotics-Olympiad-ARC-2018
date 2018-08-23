#include "ros/ros.h"

// include  Messages Libs
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
// include Custom Messages
#include "Jetson/ControlSignal.h"
#include "Jetson/CtrlSigResponse.h"


#define ROS_LOOP_RATE 100

void cmdCallback(const Jetson::CtrlSigResponse:::ConstPtr& res)
{

}



int main(int argc,char **argv)
{
	ros::init(argc,argv,"MasterNode");

	ros::NodeHandle n;

	ros::Publisher pub = n.advertise<Jetson::ControlSignal>("MasterOut",100);
	ros::Subscriber sub = n.subscribe("MasterIn",100,cmdCallback);

	ros::Rate loop_rate(ROS_LOOP_RATE);

	while(ros::ok())
	{
		ControlSignal command;
		// Process the command
		

		pub.publish(command);

		ros::spinOnce();

		loop_rate.sleep();
	}

	return 0;
}
