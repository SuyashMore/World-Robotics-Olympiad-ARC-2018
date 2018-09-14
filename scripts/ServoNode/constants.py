# ttyUSB_USB2DYNAMIXEL = "/dev/ttyUSB3"
# ttyUSB_USB2DYNAMIXEL = "/dev/ttyUSB9"
# ttyUSB_USB2DYNAMIXEL = "/dev/ttyUSB6"
# ttyUSB_USB2DYNAMIXEL = "/dev/ttyUSB0"
ttyUSB_USB2DYNAMIXEL = "/dev/ttyUSB0"

# DXL_LIB_PATH = "/home/ajaykumar/DynamixelSDK/c/build/linux64/libdxl_x64_c.so"
# DXL_LIB_PATH = "/home/harsh/DynamixelSDK/c/build/linux64/libdxl_x64_c.so"
# DXL_LIB_PATH = "/home/nvidia/DynamixelSDK/c/build/linux_sbc/libdxl_sbc_c.so"
DXL_LIB_PATH = "/home/pratik/DynamixelSDK/c/build/linux64/libdxl_x64_c.so"

ENABLE_DXL_MESSAGES = False
ENABLE_DEBUG_MESSAGES = True
ENABLE_KINEMATIC_DEBUG_MESSAGES_MAT = False
ENABLE_KINEMATIC_DEBUG_MESSAGES_RES = True


#Link Lengths
L1=1.1+8.9151
L2=11.284
L3=7.635
L4=3.8
L5=14.70

#Servo Motor Parameters - Speed
servoSpeed = 200
servoSpeedArm = 50
servoSpeedStack = 200
servoSpeedCentre = 200
servoGripperSpeed = 350


#Servo Motor Resolution
# SERVO_RES = float(300)/1023
SERVO_RES = 0.29

#Servo Angles Transformation Functions
def transform2ServoAngles(angle,angleIndex):
    CompoundAngle=0
    0

    if angleIndex == 0:
        CompoundAngle= (((angle+325) / (SERVO_RES) * (3/2))+177)
    if angleIndex == 1:
        CompoundAngle= (((angle + 82) / (SERVO_RES))*2)+196        #Reduction in Gear Ratio
    if angleIndex == 2:
        CompoundAngle= (((angle-88+2) / (SERVO_RES))+497)
    if angleIndex == 3:
        CompoundAngle= (((angle +28) / (-SERVO_RES))) + 569
    if angleIndex == 4:
        CompoundAngle= (((angle+11) / (SERVO_RES))) + 461
    if angleIndex == 5:
        CompoundAngle= ((angle / (SERVO_RES)))
    return (int(CompoundAngle)%1023)

def transform2StandardAngles(angle,angleIndex):
    if angleIndex == 0:
        return ((((((angle - 177 ) * SERVO_RES ) * (1) )))  / (3/2)) -325
    if angleIndex == 1:
        return (((((angle - 196 ) * SERVO_RES ) * (1) ))/ 2) -82 #Reduction in Gear Ratio
    elif angleIndex == 2:
        max_Val = 170
        temp = (((angle-497)*SERVO_RES) ) * (1) +88-2
        return temp
    elif angleIndex == 3:
        return (((angle -569)*SERVO_RES) ) * (-1) -28
    elif angleIndex == 4:
        return (((angle - 461)*SERVO_RES) ) -11
    elif angleIndex == 5:
        return (((angle)*SERVO_RES) )



#Gripper Angles
GRIPCLOSE = 0
GRIPOPEN = 600

#Unique IDs for Each Servo

servoIDArm =[8,9,6,13,17,5]    #in ascending order from the bottom most Servo



#Standard Position ARM angles
standardArmAngle = [0,0,0,0,0,0]   #in ascending order from the bottom most Servo
