import servo_functions as servo

if __name__ == "__main__":
	servo.enable_port()
	while True:
		id = input("Enter Bot ID:")
		print(servo.read_torque(id)