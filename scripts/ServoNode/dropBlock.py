import constants
import super_servo_functions as super
import time

#Sleep Constants
SL1 = 1
SL2 = 1
SL3 = 2

if __name__=="__main__":
    super.init()
    super.enableAll()
    super.setSpeedAll(50)

    raw_input("Press Any Key to Enable Grip")
    super.gripEnable()   

    raw_input("Press Any Key to Begin Motion")


    super.setTransformedAngle(3,-140)
    time.sleep(SL2)
    super.setTransformedAngle(1,-10)
    time.sleep(SL2)
    super.setTransformedAngle(2,60)
    time.sleep(SL1)
    super.setTransformedAngle(1,10)
    time.sleep(SL1)
    super.setTransformedAngle(2,55)
    time.sleep(SL1)
    super.setTransformedAngle(1,10)
    time.sleep(SL1)
    super.setTransformedAngle(2,60)
    time.sleep(SL3)
    super.gripDisable()
    time.sleep(SL3)
    super.setTransformedAngle(1,12) 

    raw_input("Take the Bot Back ! ")

    super.setTransformedAngle(1,12)
    time.sleep(SL1)
    super.setTransformedAngle(2,50)
    time.sleep(SL1)
    super.setTransformedAngle(1,12)
    time.sleep(SL1)
    super.setTransformedAngle(2,46)
    time.sleep(SL1)
    super.setTransformedAngle(1,12)
    time.sleep(SL1)
    super.setTransformedAngle(2,45)
    time.sleep(SL1)
    super.setTransformedAngle(1,16)
    






