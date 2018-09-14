import super_servo_functions as super	

if __name__=="__main__":
    super.init()

    super.enableAll()
    super.setSpeedAll(250)
    super.move2angle(0,-90,90,0,0)
    super.move2standard_norm()
