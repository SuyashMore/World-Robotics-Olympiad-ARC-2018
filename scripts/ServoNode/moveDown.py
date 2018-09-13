import super_servo_functions as super	

import time
if __name__=="__main__":
    super.init()

    super.enableAll()
    super.setSpeedAll(250)
    c2 = 115.461
    c1 = -32.1
    itr = 0
    while itr<16:
        # six = float(raw_input("two?"))
        # Nine = float(raw_input("one?"))
        # raw_input("")
        super.setTransformedAngle(2,c2)
        super.setTransformedAngle(1,c1)
        if(itr <=6):
            time.sleep(0.7)
        else:
            time.sleep(0.2)
        itr+=1
        c2 -= 1
        c1 +=1.5



    # super.move2angle(0,-90,90,0,0)
    # super.move2standard()



        
