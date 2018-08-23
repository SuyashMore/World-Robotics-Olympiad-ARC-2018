import servo_functions as servos
import constants
import fk3 as fk
import inverseK as ik

def init():
	return servos.enable_port()

def enable(ID):
	return servos.enable_bot(ID)

#enable all the Assigned Servo Motors
def enableAll():
	for ids in constants.servoIDArm:
		enable(ids)
		setSpeed(ids,constants.servoSpeedArm)


def disable(ID):
	return  servos.disable_bot(ID)

def disableAll():
	for ids in constants.servoIDArm:
		disable(ids)

def setSpeed(ID,Speed): #(0-1023)
	return servos.set_speed(ID,Speed)

def setSpeedAll(speed):
	for ids in constants.servoIDArm:
		setSpeed(ids,speed)

#writes the Servo Angle Value(UnMapped)
def setAngle(ID,Angle): #( _ , 0-1023)
	return servos.write_pos(ID,Angle)

#Writes the Angle to the Mapped Servo Accepted Values
def setTransformedAngle(index,Angle):#(_,0-360)
	return setAngle(constants.servoIDArm[index],constants.transform2ServoAngles(Angle,index))


#gets the Servo Angle Value (Unmapped)
def getAngle(ID):
		return servos.read_pos(ID,0)


#gets Mapped Angle Values from Servo Received Values
def getAngleTransformed(index):#(0-360)
	# Apply the Transformation
	return constants.transform2StandardAngles(getAngle(constants.servoIDArm[index]),index)


def setAngles(a0,a1,a2,a3,a4):

	tfa0=constants.transform2ServoAngles(a0,0)
	tfa1=constants.transform2ServoAngles(a1,1)
	tfa2=constants.transform2ServoAngles(a2,2)
	tfa3=constants.transform2ServoAngles(a3,3)
	tfa4=constants.transform2ServoAngles(a4,4)
	
	setAngle(constants.servoIDArm[0],tfa0)
	setAngle(constants.servoIDArm[1],tfa1)
	setAngle(constants.servoIDArm[2],tfa2)
	setAngle(constants.servoIDArm[3],tfa3)
	setAngle(constants.servoIDArm[4],tfa4)

def processIK(x,y,z):
	return ik.process(x,y,z)


#moves to x,y,z and returns an boolean value whether the location is reachable or not
def move2pos(x,y,z):
	a0,a1,a2,a3,a4,isPossible = ik.process(x,y,z)

	if isPossible==True:
		setAngles(a0,a1,a2,a3,a4)       
	else:
		pass

	return isPossible
	
def processFK(a0,a1,a2,a3,a4):
	return fk.process(a0,a1,a2,a3,a4)

def move2angle(a0,a1,a2,a3,a4):
	# fk.process(a0,a1,a2,a3,a4)
	setAngles(a0,a1,a2,a3,a4)


#Hard-Coded Standard Position for Arm
def setPositionStandard():
	pass

def setPositionTopView():
	pass

def setPickupPosition():
	pass

def gripEnable():
	setSpeed(constants.servoIDArm[5],constants.servoGripperSpeed)
	setTransformedAngle(5,constants.GRIPCLOSE)
	

def gripDisable():
	setSpeed(constants.servoIDArm[5],constants.servoGripperSpeed)
	setTransformedAngle(5,constants.GRIPOPEN)
	