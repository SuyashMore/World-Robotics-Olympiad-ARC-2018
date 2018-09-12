import servo_functions as servos
import constants
import fk3 as fk
import inverseK as ik
import time
import super_servo_functions as super

if __name__=="__main__":
	super.init()
	super.enableAll()
	super.setSpeedAll(200)
	
	FINAL_X =9.5
	FINAL_Y =  -8.9
	INITITAL_Z =  -7.5
	FINAL_Z = -11
		
		
	
	while(True):
		# super.move2angle(0,-90,90,0,0)
		# time.sleep(1)

		# super.move2pos(, FINAL_Y+4, 0)
		# time.sleep(1)

		# super.move2angle(0,-90,90,0,0)
		# time.sleep(1)

		super.move2angle(0,-90,90,0,0)
		time.sleep(1)

		super.move2pos(FINAL_X, FINAL_Y, INITITAL_Z)
		time.sleep(1)
		super.setTransformedAngle(4,20)
		time.sleep(3)

		
