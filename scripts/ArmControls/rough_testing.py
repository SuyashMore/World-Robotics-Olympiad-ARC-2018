import constants
import super_servo_functions as super
import time

#Sleep Constants
SL1 = 1
SL2 = 1

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
    super.setTransformedAngle(1,20)
    time.sleep(SL1)
    super.setTransformedAngle(2,60)
    time.sleep(SL1)

    super.setTransformedAngle(1,27) 
    super.gripDisable()
    time.sleep(0.5)
    super.gribEnable()
    super.setTransformedAngle(3,-138)
    super.gripDisable()
    time.sleep(0.5)
    super.gribEnable()
    super.gripDisable()
    time.sleep(0.5)
    super.gribEnable()
    super.gripDisable()
    time.sleep(0.5)
    super.gribEnable()
    time.sleep(0.5)
    super.gripDisable()
    time.sleep(0.5)
    super.gribEnable()
    time.sleep(0.5)
    super.gripDisable()
    time.sleep(0.5)
    super.gribEnable()
    time.sleep(0.5)
    super.gripDisable()
    
    super.gribEnable()




