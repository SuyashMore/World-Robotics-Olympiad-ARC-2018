#include "ros/ros.h"
#include "std_msgs/String.h"

#include "Navigation.cpp"

Motor motor; 

ros::Publisher atmegaPub ;	


void inputCallback(const std_msgs::String::ConstPtr& msg);

int main(int argc,char **argv)
{
	ros::init(argc,argv,"debug_Node_Motor");

	ros::NodeHandle n;

	atmegaPub = n.advertise<std_msgs::String>("AtmegaIn",100);
		
	while(ros::ok())
	{
		std_msgs::String msg;
		msg.data = motor.encrypt_message();
		atmegaPub.publish(msg);

		motor.bot_Backward_withPWM(UNIT_PWM);
	
		ros::spinOnce()	;

	}

	return 0;
}
