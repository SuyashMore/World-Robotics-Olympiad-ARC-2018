#pragma once

#include "defines.h"
#include "utility.h"



struct botData
{
	bool lsaFront[8];
	bool lsaBack[8];
	int errorFront=0;
	int errorBack=0;
	int tofFront=0;
	int tofBack=0;
	bool digiLeft=0;
	bool digiRight=0;
	bool preserveHistoryF = false;
	bool preserveHistoryB = false;

	void printData()
	{
		std::cout<<"Front Sensors:";
		for(bool x : lsaFront)
			std::cout<<(bool)x<<" , ";
		std::cout<<"\nBack Sensors:";
		for(bool y : lsaBack)
			std::cout<<(bool)y<<" , ";


		std::cout<<"\nerrorFront:"<<errorFront<<std::endl;
		std::cout<<"errorBack:"<<errorBack<<std::endl;
		std::cout<<"Tof Front:"<<tofFront<<std::endl;
		std::cout<<"Tof Back:"<<tofBack<<std::endl;
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
		tofBack=b.tofBack;
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
		tofBack=b.tofBack;
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
		tofBack=0;
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


			// //Extract the Front Error 

			index = message.find(_3_MESSAGE)+1;
			length = message.find(_4_MESSAGE) - index;
			errorFront = stoi( message.substr( index,length) ) - 100 -4;

			// //Extract the Back Error

			index = message.find(_4_MESSAGE)+1;
			length = message.find(_5_MESSAGE) - index;
			errorBack =(-1)*( stoi( message.substr(index,length)) - 100 - 1);

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

			// //Extract thr TOF-2_data

			index = message.find(_8_MESSAGE)+1;
			length = message.find(_9_MESSAGE_END) - index;
			
			tofBack = stoi( message.substr(index,length));
		}

	bool isFrontAllWhite()
	{
		for(bool x:lsaFront)
			if(!x)
				return x;
		return true;
	}

	bool isBackAllWhite()
	{
		for(bool x:lsaBack)
			if(!x)
				return x;
		return true;
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
			if(x)
				out.append("1");
			else
				out.append("0");
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
			return out;
	}

	void setPWM(int f,int b,int l,int r)
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


	void BOT_STOP()
	{
		for(int i=0;i<4;i++)
			direction[i]=true;

	}
	void BOT_FORWARD()
	{
	  direction[MOTOR_LEFT] = true;
	  direction[MOTOR_RIGHT] = true;
	}

	void BOT_BACKWARD()
	{
	  direction[MOTOR_LEFT] = false;
	  direction[MOTOR_RIGHT] = false;
	}

	void SPOT_LEFT()            
	{
	  direction[MOTOR_FRONT] = true;
	  direction[MOTOR_RIGHT] = true;
	  direction[MOTOR_BACK] = true;
	  direction[MOTOR_LEFT] = true;
	}
	void SPOT_RIGHT()
	{
	  direction[MOTOR_FRONT] = false;
	  direction[MOTOR_RIGHT] = false;
	  direction[MOTOR_BACK] = false;
	  direction[MOTOR_LEFT] = false;
	}

};
