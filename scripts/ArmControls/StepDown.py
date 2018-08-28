import constants
import super_servo_functions as super
import inverseK as ki
import time

SERVO_SPEED =40
STEP_SIZE = 1.2 #in cm
STEP_DELAY = 0.80 #in seconds

if __name__=="__main__":
    super.init()

   
    super.enable(8)
    super.enable(9)
    super.enable(12)
    super.enable(15)
    super.enable(17)
    super.enable(16)
    
    super.setSpeed(8,SERVO_SPEED)
    super.setSpeed(9,int(SERVO_SPEED))
    super.setSpeed(12,SERVO_SPEED)
    super.setSpeed(15,int(SERVO_SPEED))
    super.setSpeed(17,SERVO_SPEED)
    super.setSpeed(16,SERVO_SPEED)

    x=float(raw_input("Enter Target x:"))
    y=float(raw_input("Enter Target y:"))
    z1=float(raw_input("Enter Initial z:"))
    z2 = float(raw_input("Enter Final z:s"))

    a0,a1,a2,a3,a4,isPossible = ki.process(x,y,z1)



    if isPossible==True:
        # print("Output Angles are:",a0,a1,a2,a3,a4)

        tfa0=constants.transform2ServoAngles(a0,0)
        tfa1=constants.transform2ServoAngles(a1,1)
        tfa2=constants.transform2ServoAngles(a2,2)
        tfa3=constants.transform2ServoAngles(a3,3)
        tfa4=constants.transform2ServoAngles(a4,4)



        a = raw_input("Enter Any Key to Move to Initial Position ")

        
        super.setAngle(8,tfa0)
        super.setAngle(12,tfa2)
        super.setAngle(15,tfa3)
        super.setAngle(17,tfa4)
        super.setAngle(9,tfa1)
        

        #beign stepping down
        raw_input(":Press Any Key to Begin Step Down:")

        currentz = z1
        dz = z2-z1
        while(currentz>z2):
            #decrease the Step Size
            currentz-=STEP_SIZE
            if (currentz<z2):
                currentz=z2
            a0,a1,a2,a3,a4,isPossible = ki.process(x,y,currentz)
            

            if isPossible:          #Execute the StepDown Process
                print("Current z at : ",currentz )
                tfa0=constants.transform2ServoAngles(a0,0)
                tfa1=constants.transform2ServoAngles(a1,1)
                tfa2=constants.transform2ServoAngles(a2,2)
                tfa3=constants.transform2ServoAngles(a3,3)
                tfa4=constants.transform2ServoAngles(a4,4)                


                super.setAngle(8,tfa0)
                super.setAngle(12,tfa2)
                super.setAngle(15,tfa3)
                super.setAngle(17,tfa4)
                super.setAngle(9,tfa1)

            else:
                pass
            #sleep
            time.sleep(STEP_DELAY)
        
        print("You have Reached your Desired Location")
    else:
        pass
            
