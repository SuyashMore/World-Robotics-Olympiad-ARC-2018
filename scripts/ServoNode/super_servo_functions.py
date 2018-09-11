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
    print("Disabling All Torques !!")
    for ids in constants.servoIDArm:
        disable(ids)
    disable(7)

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
    tfa1=constants.transform2ServoAngles(a1-2,1)
    tfa2=constants.transform2ServoAngles(a2,2)
    tfa3=constants.transform2ServoAngles(a3,3)  
    tfa4=constants.transform2ServoAngles(a4+2,4)
    
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

def disableTorque():
    disableAll()
    disable(7)


def stackBlockOld():
    #Sleep Constants
    SL1 = 2
    SL2 = 1
    SL3 = 2
    SLS=2
    init()
    enableAll()
    setSpeedAll(50)

    # raw_input("Press Any Key to Enable Grip")
    gripEnable()   

    # raw_input("Press Any Key to Begin Motion")


    setTransformedAngle(3,-10)
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

def pickupAndPushPos():
    move2angle(0,12,45,-140,0)


def stackBlock():
    #Sleep Constants
    SL1 = 1
    SL2 = 3
    SL3 = 0.5
    SLS=2
    init()
    enableAll()
    setSpeedAll(150)

    # raw_input("Press Any Key to Enable Grip")
    gripEnable()   
    time.sleep(2)

    # raw_input("Press Any Key to Begin Motion")


    setTransformedAngle(3,-130)
    time.sleep(SL3)

    setTransformedAngle(1,-30)
    time.sleep(SL3)


    setTransformedAngle(2,30)
    time.sleep(SL3)


    setTransformedAngle(1,-20)
    time.sleep(SL3)

    # raw_input("Take the Bot Back ! ")

    move2angle(0,20,20,-140,0)
    time.sleep(SL3)
    gripDisable()
    time.sleep(SL2)

    setTransformedAngle(2,45)
    time.sleep(SL3)

   

def move2standard():
    init()

    enableAll()
    setSpeedAll(150)    

   # move2angle(0,-90,90,0,0)   
    move2angle(0,-90,90,0,0)

def pickupXYZ():
    FINAL_X =9.2
    FINAL_Y = -8.4
    INITIAL_Z = -9
    FINAL_Z = -13
        
    SL4 = 0.4

    SL3 = 1.0
    SL2 = 0.3
    SL1 = 0.5 # WAS 0.15 AND CHANGED TO 0
    SLY = 1.6
    SLS=0.4
    # SLS=1.1
    SLE =5


    init()
    enableAll()
    
    gripDisable()
    # raw_input("Press  Any Key to Pickup")

    setSpeedAll(250)

    # move2angle(-39,-16,123,-103,30)    similar to below co-ordinate
    
    # move2pos(8.8438761521539782,-7.161629699568385,-9.105261027785847)
    # time.sleep(SLY)

    # move2pos(9,-6.5,-9)
    # time.sleep(SLY)
    
    # move2pos(9,-7,-9)
    # time.sleep(SLY)
   
    # move2pos(9.5,-7,-9)
    # time.sleep(SLY)
    
    # move2pos(9.7,-7,-9)
    # time.sleep(SLY)


    # move2pos(9.7,-7.5,-9)
    # time.sleep(SLY)

    # move2pos(9.7,-7.5,-9)
    # time.sleep(SLY)


    # move2pos(9.8,-7.6,-9)
    # time.sleep(SLY)

    # move2pos(9.8,-7.5,-9)
    # time.sleep(SLY)

    # move2pos(9.9,-7.5,-9)
    # time.sleep(SLY)

    # move2pos(9.9,-7.8,-9.5)
    # time.sleep(SLY)

    # move2pos(9.9,-7.8,-9.9)
    # time.sleep(SLY)

   
    # move2pos(9.9,-7.8,-12)
    # time.sleep(SLY)
     # p = INITIAL_
     # Z
    # while p >FINAL_Z :    
    #     move2pos(8.7,-6.4,p)
    #     setAngle(17,600)
    #     p=p-0.2

    
    move2pos(FINAL_X,FINAL_Y,INITIAL_Z)
    time.sleep(SLY)


    setTransformedAngle(4,35)
    time.sleep(SLY)



    # setTransformedAngle(4,35)
    # time.sleep(SLY)

    # move2pos(FINAL_X,FINAL_Y,-8.9)
    # time.sleep(SLY)
    
    setSpeedAll(150)
    for i in range (-90,-131,-3):
        move2pos(FINAL_X,FINAL_Y,((float)(i)/10))
        setTransformedAngle(4,35)
        time.sleep(SL2-0.1)


    # time.sleep(SL3)
    # move2pos(FINAL_X,FINAL_Y,-13)
    # time.sleep(SLY)
    time.sleep(1)

    

    gripEnable()
    time.sleep(SL3)

    setSpeedAll(150)

    # mov2angle(0,-90,90,0,0) 19,0,-6
    move2pos(FINAL_X+7,FINAL_Y,-9)
    time.sleep(SLS)
    move2pos(FINAL_X+7,FINAL_Y/2,-7)
    time.sleep(SLS)
    move2pos(FINAL_X+7,FINAL_Y/2,-2)
    time.sleep(SLS)
    move2pos(FINAL_X+6.5,FINAL_Y/3,0)
    time.sleep(SL1)
    move2pos(FINAL_X+6,0,2)
    time.sleep(SL1)

    move2angle(0,-45,0,-45,0)
    time.sleep(SL4)

    move2standard()






