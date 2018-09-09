#pragma once

#include "defines.h"
#include "utility.h"

int Lidar=0;


struct botData
{
	bool lsaFront[8];
	bool lsaBack[8];
	int errorFront=0;
	int errorBack=0;
	int tofFront=0;
	int tofSide=0;
	bool digiLeft=0;
	bool digiRight=0;
	bool preserveHistoryF = false;
	bool preserveHistoryB = false;
	bool tofFlag = false;
	bool BackMonitorFlag = true;
	bool BackFlag = false;


	void printData()
	{
		std::cout<<"Front Sensors:";
		for(bool x : lsaFront)
			std::cout<<(bool)x<<" , ";
		std::cout<<" # errorFront:"<<errorFront<<std::endl;
		std::cout<<"Back Sensors:";
		for(bool y : lsaBack)
			std::cout<<(bool)y<<" , ";
		std::cout<<"# errorBack:"<<errorBack<<std::endl;

		std::cout<<"Tof Front:"<<tofFront<<std::endl;
		 std::cout<<"Tof Side:"<<tofSide<<std::endl;
		std::cout<<"digiLeft:"<<digiLeft<<std::endl;
		std::cout<<"digiRight:"<<digiRight<<std::endl;
	}

	void copyFront(botData& b)
	{
		for(int i=0;i<8;i++)
		{
			lsaFront[i]=b.lsaFront[i];
		}


		errorFront = b.errorFront;
		errorBack=b.errorBack;
		tofFront=b.tofFront;
		tofSide=b.tofSide;
		digiLeft=b.digiLeft;
		digiRight=b.digiRight;
		preserveHistoryF=b.preserveHistoryF;
		preserveHistoryB=b.preserveHistoryB;
	}
	void copyBack(botData& b)
	{
		for(int i=0;i<8;i++)
		{
			lsaBack[i]=b.lsaBack[i];
		}


		errorFront = b.errorFront;
		errorBack=b.errorBack;
		tofFront=b.tofFront;
		tofSide=b.tofSide;
		digiLeft=b.digiLeft;
		digiRight=b.digiRight;
		preserveHistoryF=b.preserveHistoryF;
		preserveHistoryB=b.preserveHistoryB;	
	}

	void initZero()
	{
		for(int i=0;i<8;i++)
		{
			lsaFront[i]=0;
			lsaBack[i]=0;
		}
		errorFront = 0;
		errorBack=0;
		tofFront=0;
		tofSide=0;
		digiLeft=0;
		digiRight=0;
		preserveHistoryF=false;
		preserveHistoryB=false;	
	}

	void decrpty_message(string message)
		{
			// Extract the Forward LSA Sensor Data
			int itr =0;
			int index =message.find(_1_MESSAGE)+1;
			int length =  message.find(_2_MESSAGE);
			for(int i=index;i<length;i++)
			{
				lsaFront[itr] = stoi(message.substr(i,1));
				itr++;
			}

			// Extract the Back LSA Sensor Data
			itr=0;
			index = message.find(_2_MESSAGE)+1;
			length = message.find(_3_MESSAGE);
			for(int i=index;i<length;i++)
			{
				lsaBack[itr] = stoi(message.substr(i,1));
				itr++;
			}

			if(BackMonitorFlag)
			{
				if(isBackAnyWhite())
					BackFlag=true;
			}


			// //Extract the Front Error 

			index = message.find(_3_MESSAGE)+1;
			length = message.find(_4_MESSAGE) - index;
			errorFront = stoi( message.substr( index,length) ) ;

			// //Extract the Back Error

			index = message.find(_4_MESSAGE)+1;
			length = message.find(_5_MESSAGE) - index;
			// errorBack = stoi( message.substr(index,length)) ;
			// Jugaad
			errorBack = stoi( message.substr(index,length)) - 800 ;

			// //Extract the Left Digi-Data

			int temp = message.find(_5_MESSAGE) + 1;
			digiLeft = stoi ( message.substr( temp,1 ) );


			// //Extract the Right Digi-Data

			temp = message.find(_6_MESSAGE) + 1;
			digiRight = stoi ( message.substr( temp,1 ) );	

			// //Extract the TOF-1_data

			index = message.find(_7_MESSAGE)+1;
			length = message.find(_8_MESSAGE) - index;
			tofFront = stoi( message.substr(index,length));

			if(tofFront==0)
				tofFront=999999;
			if(tofFront>= TOF_FLAG_MIN_THRESH && tofFront<=TOF_FLAG_MAX_THRESH)
				tofFlag=true;

			
			// //Extract thr TOF-2_data

			index = message.find(_8_MESSAGE)+1;
			length = message.find(_9_MESSAGE_END) - index;
			tofSide = stoi( message.substr(index,length));
		}

	bool isFrontAllWhite()
	{
		for(bool x:lsaFront)
			if(x)
				return (!x);
		return true;
	}
	bool isFrontAllBlack()
	{
		for(bool x:lsaFront)
			if(!x)
				return x;
		return true;
	}

	bool isFrontAnyWhite()
	{
		for(bool x:lsaFront)
			if(x)
				return (!x);
		return true;
	}

	bool isFrontAnyBlack()
	{
		for(bool x:lsaFront)
			if(x)
				return (x);
		return false;
	}


	bool isBackAllWhite()
	{
		for(bool x:lsaBack)
			if(x)
				return (!x);
		return true;
	}

	bool isBackAnyWhite()
	{
		for(bool x:lsaBack)
			if(x)
				return (!x);
		return false;
	}

	bool isBackAnyBlack()
	{
		for(bool x:lsaBack)
			if(x)
				return (x);
		return false;
	}

	bool isFrontTurnComplete()
	{
  		if (lsaFront[3] || lsaFront[4] || lsaFront[5])
    		return true;
  		else
    		return false;
	}
	bool isBackTurnComplete()
	{
  		if (lsaBack[3] || lsaBack[4] || lsaBack[5])
    		return true;
  		else
    		return false;
	}

	void enable_monitor_Back()
	{
		BackMonitorFlag=true;
		BackFlag=false;
	}
	void disable_monitor_Back()
	{
		BackMonitorFlag=false;
		BackFlag=false;
	}

	bool getMonitoredVal_Back()
	{
		return BackFlag;
	}


};


struct Motor
{
	bool direction[4];
	int PWM[4];
	int delay_in_ms = 0;

	// Initialise Constructor
	Motor()
	{
		for(int i=0;i<4;i++)
		{
			direction[i] = false;
			PWM[i] = 0; 
		}
		delay_in_ms=0;
	}

	void reset()
	{
		for (int x:PWM)
			x=0;
		delay_in_ms=0;
	}

	void printData()
	{
		std::cout<<"Direction(Front,Right,Back,Left):";
		for(bool x:direction)
			std::cout<<x<<" , ";
		std::cout<<"\nPWM(Front,Right,Back,Left):";
		for(int x:PWM)
			std::cout<<x<<" , ";
		std::cout<<""<<std::endl;
		std::cout<<"Delay in ms:"<<delay_in_ms<<std::endl;
	}

	string encrypt_message()
	{
		string out = _OUTM_DIR ;

		// Append the Direction of Each Motor
		for(bool x:direction)
		{
			out.append(x?"1":"0");
		}

		out.append(_OUTM_PWM); 

		// Append the PID of Each Motor
			out.append(to_string(PWM[0]));
			out.append("a");
			out.append(to_string(PWM[1]));
			out.append("b");
			out.append(to_string(PWM[2]));
			out.append("c");
			out.append(to_string(PWM[3]));
			out.append("d");
		// Append the Delay
			out.append(to_string(delay_in_ms));
			out.append(_OUT_DELAY);
			return out;
	}

	void setPWM_all(int pwm)
	{
		PWM[0]=pwm;
		PWM[1]=pwm;
		PWM[2]=pwm;
		PWM[3]=pwm;
	}

	void setPWM_ofEach(int f,int r,int b,int l)
	{
		PWM[0]=f;
		PWM[1]=r;
		PWM[2]=b;
		PWM[3]=l;
	}

	void setPWMof(int index,int PWMVal)
	{
		PWM[index]=PWMVal;
	}


	void bot_Stop()
	{
		for(int i=0;i<4;i++)
			direction[i]=true;
		setPWM_all(0);

	}


	void bot_Forward()
	{
	  direction[MOTOR_LEFT] = true;
	  direction[MOTOR_RIGHT] = true;
	}

	void bot_Forward_withPWM(int pwm)
	{
		bot_Forward();
   		setPWMof(MOTOR_RIGHT,pwm);
   		setPWMof(MOTOR_LEFT,pwm);
   		setPWMof(MOTOR_BACK,0);
   		setPWMof(MOTOR_FRONT,0);
	}
	
	void bot_Forward_withPWMm(int pwm)
	{
		bot_Forward();
   		setPWMof(MOTOR_RIGHT,pwm);
   		setPWMof(MOTOR_LEFT,pwm);
	}
		void bot_Backward_withPWM(int pwm)
	{
		bot_Backward();
   		setPWMof(MOTOR_RIGHT,pwm);
   		setPWMof(MOTOR_LEFT,pwm);
   		setPWMof(MOTOR_BACK,0);
   		setPWMof(MOTOR_FRONT,0);
	}

	void bot_Backward_withPWMm(int pwm)
	{
		bot_Backward();
   		setPWMof(MOTOR_RIGHT,pwm);
   		setPWMof(MOTOR_LEFT,pwm);
	}


	void bot_Backward()
	{
	  direction[MOTOR_LEFT] = false;
	  direction[MOTOR_RIGHT] = false;
	}

	void spot_Left()
	{
	  direction[MOTOR_FRONT] = true;
	  direction[MOTOR_RIGHT] = true;
	  direction[MOTOR_BACK] = true;
	  direction[MOTOR_LEFT] = false;
	}

	void spot_Left_withPWM(int pwm)            
	{
		spot_Left();
		setPWM_all(pwm);
	}

	void spot_Right_withPWM(int pwm)            
	{
		spot_Right();
		setPWM_all(pwm);
	}	


	void spot_Right()
	{
	  direction[MOTOR_FRONT] = false;
	  direction[MOTOR_RIGHT] = false;
	  direction[MOTOR_BACK] = false;
	  direction[MOTOR_LEFT] = true;
	}
	void strafe_Right()
	{
	  direction[MOTOR_FRONT] = false;
	  direction[MOTOR_RIGHT] = false;
	  direction[MOTOR_BACK] = true;
	  direction[MOTOR_LEFT] = false;	
	}
	void strafe_Left()
	{
		direction[MOTOR_FRONT] = true;
	  direction[MOTOR_RIGHT] = false;
	  direction[MOTOR_BACK] = false;
	  direction[MOTOR_LEFT] = false;		
	}

	void strafe_Right_withPWM(int pwm)
	{
	  strafe_Right();
	  setPWM_ofEach(pwm,0,pwm,0);	
	}

	void strafe_Left_withPWM(int pwm)
	{
	  strafe_Left();
	  setPWM_ofEach(pwm,0,pwm,0);	
	}

};


struct gameState
{
  int digiCounter=0;
  int digiCounterR=0;
  int r=0;
  int t=0;
  int reading_tof_digital=0;
  int reading_tof_analog=0;

  int currentStepIndex=1;

  bool executeStep1=true;
  bool executeStep2=true;
  int step2Counter=0;

  bool executeStep3=false;
  bool executeStep35=false;
  bool executeStep36=false;
  bool executeStep4=false;
  bool executeStep5=false;
  bool executeStep6=false;
  bool executeStep7=false;
  bool executeStep74=false;
  bool executeStep75=false;
  bool executeStep76=false;
  bool executeStep77=false;
  bool executeStep8=false;
  bool executeStep9=false;
  bool executeStep10=false;
  bool executeStep11=false;
  bool executeStep12=false;
  bool executeStep13=false;
  bool executeStep14=false;
  bool executeStep15=false;
  bool executeStep16=false;
  bool executeStep17=false;

  void printData()
  {
  	cout<<"digiCounter Left : "<<digiCounter<<endl;
  	cout<<"digiCounter Right :"<<digiCounterR<<endl;
  }

  void updateDigiCounter(botData& newSensor,botData& oldSensor,Motor& motor)
	{
	  if ( newSensor.digiLeft == 1 && oldSensor.digiLeft == 0)
	  		digiCounter++;
	  if(newSensor.digiRight == 1 && oldSensor.digiRight == 0)
	  		digiCounter++;
	}
  
};


struct Blocks
{
	int Location[6];
	void placeBlocks(int a,int b,int c,int d,int e,int f)
	{
		for(int i=0;i<6;i++)
		{
			Location[i]=a;
		}
	}
};