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


def setAngles_for_pickup(a0,a1,a2,a3,a4):

    tfa0=constants.transform2ServoAngles(a0,0)
    tfa1=constants.transform2ServoAngles(a1,1)
    tfa2=constants.transform2ServoAngles(a2,2)
    tfa3=constants.transform2ServoAngles(a3,3)  
    tfa4=constants.transform2ServoAngles(22,4)
    
    setAngle(constants.servoIDArm[4],tfa4)
    setAngle(constants.servoIDArm[3],tfa3)
    setAngle(constants.servoIDArm[2],tfa2)
    setAngle(constants.servoIDArm[1],tfa1)
    setAngle(constants.servoIDArm[0],tfa0)
    print("Servo Angles Written Are Norm:",a0,a1,a2,a3,a4)
    print("Servo Angles Written Are :",tfa0,tfa1,tfa2,tfa3,tfa4)



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
    print("Servo Angles Written Are :",tfa0,tfa1,tfa2,tfa3,tfa4)


def setAngles_rev(a0,a1,a2,a3,a4):

    tfa0=constants.transform2ServoAngles(a0,0)
    tfa1=constants.transform2ServoAngles(a1,1)
    tfa2=constants.transform2ServoAngles(a2,2)
    tfa3=constants.transform2ServoAngles(a3,3)  
    tfa4=constants.transform2ServoAngles(a4,4)
    
    setAngle(constants.servoIDArm[0],tfa0)
    time.sleep(1.5)
    setAngle(constants.servoIDArm[1],tfa1)
    setAngle(constants.servoIDArm[2],tfa2)
    setAngle(constants.servoIDArm[3],tfa3)
    setAngle(constants.servoIDArm[4],tfa4)
    print("Servo Angles Written Are :",tfa0,tfa1,tfa2,tfa3,tfa4)

def processIK(x,y,z):
    return ik.process(x,y,z)

def cordinatorEnable():
    init()
    enableAll()
    setSpeed(1,100)
    setAngle(1,215)
    

def cordinatorDisable():
    init()
    enableAll()
    setSpeed(1,100)
    setAngle(1,505)

#moves to x,y,z and returns an boolean value whether the location is reachable or not
def move2pos(x,y,z):
    a0,a1,a2,a3,a4,isPossible = ik.process(x,y,z)

    if isPossible==True:
        setAngles_for_pickup(a0,a1,a2,a3,a4)       
    else:
        pass

    return isPossible
    
def processFK(a0,a1,a2,a3,a4):
    return fk.process(a0,a1,a2,a3,a4)

def move2angle(a0,a1,a2,a3,a4):
    fk.process(a0,a1,a2,a3,a4)
    setAngles(a0,a1,a2,a3,a4)

def move2angleS(a0,a1,a2,a3,a4):
    setAngle(13,a3)
    setAngle(8,a0)
    setAngle(9,a1)
    setAngle(6,a2)
    setAngle(17,a4)    

def startHomePosition():
    setAngles(0,-110,-10,-155,0)


#Hard-Coded Standard Position for Arm
def setPositionStandard():
    pass

def setPositionTopView():
    pass

def setPickupPosition():
    pass

def gripEnable():
    setSpeed(constants.servoIDArm[5],constants.servoGripperSpeed)
    setAngle(5,constants.GRIPOPEN)
    

def gripDisable():
    setSpeed(constants.servoIDArm[5],constants.servoGripperSpeed)
    setAngle(5,constants.GRIPCLOSE)

def disableTorque():
    disableAll()
    disable(7)


def pickupAndPushPos():
    # move2angle(-5,910,32,-140,0)
    gripEnable() 
    time.sleep(1.2)
    

def stackBlock():
    #Sleep Constants
    SL1 = 1
    SL2 = 3
    SL3 = 0.5
    SLS=2
    init()
    enableAll()
    setSpeedAll(90)

    # # raw_input("Press Any Key to Enable Grip")
    gripEnable()   
    time.sleep(2)

    # raw_input("Press Any Key to Begin Motion")

    setTransformedAngle(0,-5)
    setTransformedAngle(3,-130)
    time.sleep(SL3)

    setTransformedAngle(1,-30)
    time.sleep(SL3)



    setTransformedAngle(2,30)
    time.sleep(SL3)


    setTransformedAngle(1,-20)
    time.sleep(SL3)

    # raw_input("Take the Bot Back ! ")

    move2angle(-5,20,20,-140,0)
    time.sleep(3)
    gripDisable()
    time.sleep(SL2)
    

    setTransformedAngle(2,35)
    time.sleep(SL3)
    setTransformedAngle(1,17)

   
def move2standard_norm():
    init()
    enableAll()
    setSpeedAll(100)    
    print("move2standard-Normalized")
    move2angle(0,-90,70,-10,0) 

    
def move2standard():
    init()

    enableAll()
    setSpeedAll(100)

    # move2angleS(108,555,569,738,602)
    FINAL_X =10.3
    FINAL_Y = -11
    INITIAL_Z = -7.3
    setTransformedAngle(4,30)
    move2pos(FINAL_X,FINAL_Y,INITIAL_Z-0.6)

def pickupXYZ():
    FINAL_X =10.3
    FINAL_Y = -11
    INITIAL_Z = -7.3
    FINAL_Z = -11.5

    SL4 = 0.4

    SL3 = 1.0
    SL2 = 0.005
    SL1 = 0.5 # WAS 0.15 AND CHANGED TO 0
    SLY = 0.5
    SLS=0.4
    # SLS=1.1
    SLE =0.9


    init()
    enableAll()
    
    # move2standard()
    move2pos(FINAL_X,FINAL_Y,INITIAL_Z-0.3)
    gripDisable()
    time.sleep(2)

    setSpeedAll(80)

    # move2pos(12,-8.2,-6.5)
    # time.sleep(SLY)
    
    move2pos(FINAL_X,FINAL_Y,INITIAL_Z)
    time.sleep(SLY)

  
 
    # raw_input(" ")
    setSpeedAll(150)
    for i in range (-73,-115,-2):
        move2pos(FINAL_X,FINAL_Y,((float)(i)/10))
        time.sleep(SL2)



   # time.sleep(1)

    gripEnable()
    time.sleep(1.4)

    setSpeedAll(80)
    
    setTransformedAngle(1,-70)
    time.sleep(0.3)
    setTransformedAngle(2,80)
    setTransformedAngle(0,0)
    setTransformedAngle(4,0)
    time.sleep(0.4)
    move2standard_norm()

    cordinatorDisable()


def compressArm():
    init()
    enableAll()
    print("Compressing arm !!! 1")
    move2standard_norm()
    time.sleep(3)
    print("Compressing arm !!! 2")
    setAngles(0,-110,-10,-155,0)
    pass



if __name__=="__main__":
    while True:
        init()
        enableAll()
        raw_input("Enable Cord")
        setSpeed(1,100)
        setAngle(1,210)
        raw_input("Disable Cord")
        setSpeed(1,100)
        setAngle(1,450)







