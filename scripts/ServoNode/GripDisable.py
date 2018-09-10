import constants
import super_servo_functions as super



if __name__=="__main__":
	super.init()
	super.enable(constants.servoIDArm[5])
	super.gripEnable()
