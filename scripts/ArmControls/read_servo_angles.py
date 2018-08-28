import servo_functions as servos
import time

if __name__ == '__main__':
    
    # Open port
    print("Opening Port!")
    if servos.enable_port():
    	#take Id for the Servos as Input
        botId = input("Enter The Bot ID:")
        print("disabling Torque on the Servo Id [%d]",botId)
        servos.disable_bot(botId)
        
        try:
            while True:
                servos.read_pos(botId,1)
        except KeyboardInterrupt:
            pass
        
        print("\n[+] Disabling")
        dynamixel.closePort(port_num)

