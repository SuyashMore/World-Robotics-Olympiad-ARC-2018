import super_servo_functions as super

if __name__=="__main__":
    super.init()
    super.enableAll()

    while True:
        a0=float(raw_input("Enter Angle0:"))
        a1=float(raw_input("Enter Angle1:"))
        a2=float(raw_input("Enter Angle2:"))
        a3=float(raw_input("Enter Angle3:"))
        a4=float(raw_input("Enter Angle4:"))

        raw_input("Enter Any Key to Move to Angles ")    

        super.move2angle(a0,a1,a2,a3,a4)


    
        