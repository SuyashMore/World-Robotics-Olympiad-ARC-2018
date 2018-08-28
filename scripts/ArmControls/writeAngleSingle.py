import super_servo_functions as super
import constants

if __name__=="__main__":
	super.init()
	index = int(raw_input("Enter the Servo Motor Index(0-Bottom , 5 - Gripper:)"))
	super.enable(constants.servoIDArm[index])
	super.setSpeed(constants.servoIDArm[index],constants.servoSpeedArm)
	while True:

		angle = int(raw_input("Enter the Angle:"))

		super.setTransformedAngle(index,angle)

