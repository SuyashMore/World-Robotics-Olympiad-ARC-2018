#include "ros/ros.h"

#include "Navigation.cpp"

Motor motor; 

ros::NodeHandle n;

ros::Publisher atmegaPub = n.advertise<std_msgs::String>("AtmegaIn",100);
	

void inputCallback(const std_msgs::String::ConstPtr& msg)
{	
	std_msgs::String msg;
	
	// motor.bot_Forward_withPWM(200);
	// motor.bot_Backward_withPWM(200);
	// motor.spot_Left_withPWM(200);
	// motor.spot_Right_withPWM(200);
	// motor.strafe_Right_withPWM(200)
	// motor.strafe_Left_withPWM(200);


	msg.data = motor.encrypt_message();
	atmegaPub.publish(msg);

}	



int main(int argc,char **argv)
{
	ros::init(argc,argv,"Atmega_listener");
	
	ros::spin();

	return 0;
}

