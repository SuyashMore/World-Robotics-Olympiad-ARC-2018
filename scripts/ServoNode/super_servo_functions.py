import servo_functions as servos
import constants
import fk3 as fk
import inverseK as ik
import time

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

def cordinatorEnable():
    setSpeed(7,100)
    setAngle(7,450)
    

def cordinatorDisable():
    setSpeed(7,100)
    setAngle(7,215)

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
    fk.process(a0,a1,a2,a3,a4)
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
    setTransformedAngle(5,constants.GRIPOPEN)
    

def gripDisable():
    setSpeed(constants.servoIDArm[5],constants.servoGripperSpeed)
    setTransformedAngle(5,constants.GRIPCLOSE)
    

def stackBlock():
    #Sleep Constants
    SL1 = 1
    SL2 = 1
    SL3 = 2
    SLS=2
    init()
    enableAll()
    setSpeedAll(50)

    # raw_input("Press Any Key to Enable Grip")
    gripEnable()   

    # raw_input("Press Any Key to Begin Motion")


    setTransformedAngle(3,-140)
    time.sleep(SL2)
    setTransformedAngle(1,-10)
    time.sleep(SL2)
    setTransformedAngle(2,60)
    time.sleep(SL1)
    setTransformedAngle(1,10)
    time.sleep(SL1)
    setTransformedAngle(2,55)
    time.sleep(SL1)
    setTransformedAngle(1,10)
    time.sleep(SL1)
    setTransformedAngle(2,60)
    time.sleep(SL3)
    gripDisable()
    time.sleep(SL3)
    setTransformedAngle(1,12) 

    # raw_input("Take the Bot Back ! ")

    setTransformedAngle(1,12)
    time.sleep(SL1)
    setTransformedAngle(2,50)
    time.sleep(SL1)
    setTransformedAngle(1,12)
    time.sleep(SL1)
    setTransformedAngle(2,46)
    time.sleep(SL1)
    setTransformedAngle(1,12)
    time.sleep(SL1)
    setTransformedAngle(2,45)
    time.sleep(SL1)
    setTransformedAngle(1,16)
    time.sleep(SL1)

def move2standard():
    init()

    enableAll()

    move2angle(0,-90,90,0,0)


def pickupXYZ():
    FINAL_X = 7.5
    FINAL_Y = -9
    INITITALZ = -9
    FINAL_Z = -13.5

    SL4 = 2
    SL3 = 1.0
    SL2 = 0.8
    SL1 = 0.45
    SLY = 3
    SLS=2
    SLE =5

    # ID_4_ANGLE = 22

    init()
    enableAll()
    

    gripDisable()
    # raw_input("Press  Any Key to Pickup")

    setSpeedAll(100)

    move2pos(FINAL_X,FINAL_Y,-9)
    #setTransformedAngle(4,ID_4_ANGLE)
    setSpeedAll(140)

    time.sleep(SLE)
    
    move2pos(FINAL_X,FINAL_Y,-9.5)
    #setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL1)


    move2pos(FINAL_X,FINAL_Y,-10)
    #setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL1)


    move2pos(FINAL_X,FINAL_Y,-11)
    #setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL1)

    move2pos(FINAL_X,FINAL_Y,-11.5)
    #setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL1)

    move2pos(FINAL_X,FINAL_Y,-12)
    #setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL1)

    move2pos(FINAL_X,FINAL_Y,FINAL_Z)
    #setTransformedAngle(4,ID_4_ANGLE)

    time.sleep(SL3)

    # raw_input("Press Any Key to Enable Grip")
    gripEnable()
    time.sleep(SL3)

    time.sleep(SLY)
    # mov2angle(0,-90,90,0,0) 19,0,-6
    move2pos(FINAL_X+3,FINAL_Y,-12)
    time.sleep(SLS)
    move2pos(FINAL_X+4,FINAL_Y/2,-9)
    time.sleep(SLS)
    move2pos(FINAL_X+5,FINAL_Y/2,-4)
    time.sleep(SLS)
    move2pos(FINAL_X+6,FINAL_Y/3,0)
    time.sleep(SL1)
    move2pos(FINAL_X+6.5,0,2)
    time.sleep(SL1)

    move2standard()






