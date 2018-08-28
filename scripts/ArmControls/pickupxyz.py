import constants
import super_servo_functions as super
import time



if __name__=="__main__":
    super.init()
    super.enableAll()
    

    super.gripDisable()
    raw_input("Press  Any Key to Pickup")

    super.setSpeedAll(50)

    super.move2pos(19,0,0)
    time.sleep(1)


    super.move2pos(16,-2,0)
    time.sleep(0.7)

    super.move2pos(14,-4,0)
    time.sleep(0.25)

    super.move2pos(12.0,-6,0)
    time.sleep(0.25)

    super.move2pos(11.5,-6.5,0)
    super.setTransformedAngle(4,15)
    super.setSpeedAll(100)

    time.sleep(0.3)
    
    super.move2pos(11.5,-6.5,0)
    super.setTransformedAngle(4,15)
    time.sleep(0.3)


    super.move2pos(11.5,-6.5,0)
    super.setTransformedAngle(4,15)
    time.sleep(0.3)


    super.move2pos(11.5,-6.5,0)
    super.setTransformedAngle(4,15)
    time.sleep(0.3)

    super.move2pos(11.5,-6.5,0)
    super.setTransformedAngle(4,15)
    super.move2pos(11.5,-6.5,0)
    super.setTransformedAngle(4,15)

    raw_input("Press Any Key to Enable Grip")
    super.gripEnable()

    raw_input("Press Any Key to Pickup the Block")
    # mov2angle(0,-90,90,0,0) 19,0,-6
    super.move2pos(19,0,)
    time.sleep(0.25)
    super.move2pos(19,0,)
    time.sleep(0.25)
    super.move2pos(19,0,)
    time.sleep(0.25)
    super.move2pos(19,0,0)
    time.sleep(0.25)
    super.move2pos(19,0,)
    time.sleep(0.25)

    super.move2angle(0,-20,15,-90,0)

    raw_input("Press Any Key to Release the Block")
    super.gripDisable()





