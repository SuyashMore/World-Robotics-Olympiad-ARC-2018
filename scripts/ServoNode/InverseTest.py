import super_servo_functions as super
if __name__=="__main__":
    super.init()

    super.enableAll()
    while True:
        x=float(raw_input("Enter Target x:"))
        y=float(raw_input("Enter Target y:"))
        z=float(raw_input("Enter Target z:"))

        a0,a1,a2,a3,a4,isPossible = super.processIK(x,y,z)
        super.setSpeedAll(250)
        if isPossible:
            print("Output Angles are:",a0,a1,a2,a3,a4)

            a = raw_input("Enter Any Key to Move to Angles ")

            super.move2angle(a0,a1,a2,a3,a4)
            super.setTransformedAngle(4,30)

        else:
            pass
            