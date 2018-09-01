import constants
import super_servo_functions as super



if __name__=="__main__":
	super.init()
	super.enable(constants.servoIDArm[5])
	while True:
		raw_input("press any key to grab the block")
		super.gripEnable()
		raw_input("press any key to release the block")
		super.gripDisable()
