import servo_functions as servos
import constants
import fk3 as fk
import inverseK as ik
import time
import super_servo_functions as super

if __name__=="__main__":
	super.init()
	super.enableAll()
	super.setSpeedAll(250)
	
	FINAL_X =9.8700596687381434
	FINAL_Y =  -7.9926167264261485)
	INITITAL_Z =  -8.7000000000000348
	FINAL_Z = -13.5
		
		
	
	while(True):
		super.move2angle(0,-90,90,0,0)
		time.sleep(5)
		super.move2pos(FINAL_X, FINAL_Y, INITITAL_Z)
		time.sleep(5)


		
