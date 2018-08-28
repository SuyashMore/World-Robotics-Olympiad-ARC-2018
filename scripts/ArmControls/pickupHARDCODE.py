import constants
import super_servo_functions as super
import time


FINAL_X = 11
FINAL_Y = -7
INITITALZ = -9
FINAL_Z = -12.5

SL4 = 2
SL3 = 1.0
SL2 = 0.8
SL1 = 0.15

ID_4_ANGLE = 22

if __name__=="__main__":
    super.init()
    super.enableAll()
    

    super.gripDisable()
    raw_input("Press  Any Key to Pickup")

    super.setSpeedAll(100)

    super.move2pos(17,-2,-2)
    super.setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL4)


    super.move2pos(14,-5,-5)
    super.setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL3)

    super.move2pos(12,-7,-7)
    super.setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL2)

    super.move2pos(11,-7,-8.5)
    super.setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL2)

    super.move2pos(FINAL_X,FINAL_Y,-9)
    super.setTransformedAngle(4,ID_4_ANGLE)
    super.setSpeedAll(140)

    time.sleep(SL1)
    
    super.move2pos(FINAL_X,FINAL_Y,-9.5)
    super.setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL1)


    super.move2pos(FINAL_X,FINAL_Y,-10)
    super.setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL1)


    super.move2pos(FINAL_X,FINAL_Y,-11)
    super.setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL1)

    super.move2pos(FINAL_X,FINAL_Y,-11.5)
    super.setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL1)

    super.move2pos(FINAL_X,FINAL_Y,-12)
    super.setTransformedAngle(4,ID_4_ANGLE)
    time.sleep(SL1)

    super.move2pos(FINAL_X,FINAL_Y,FINAL_Z)
    super.setTransformedAngle(4,ID_4_ANGLE)

    raw_input("Press Any Key to Enable Grip")
    super.gripEnable()
    time.sleep(SL3)

    raw_input("Press Any Key to Pickup the Block")
    # mov2angle(0,-90,90,0,0) 19,0,-6
    super.move2pos(FINAL_X+2,FINAL_Y/3,-6)
    time.sleep(SL1)
    super.move2pos(FINAL_X+2,FINAL_Y/2,-4)
    time.sleep(SL1)
    super.move2pos(FINAL_X+2.5,FINAL_Y/2,-2)
    time.sleep(SL1)
    super.move2pos(FINAL_X+2.5,FINAL_Y/3,0)
    time.sleep(SL1)
    super.move2pos(FINAL_X+2.5,0,2)
    time.sleep(SL1)

    super.move2angle(0,-20,0,-90,0)

    raw_input("Press Any Key to Release the Block")
    super.gripDisable()





