#pragma once

#include "containers.h"



void calculate_pid(botData& newSensor,botData& oldSensor,Motor& motor)
{
 	  bool preserveHistoryF =false;
  	bool preserveHistoryB = false;

  	int frontpwm=0;
  	int backpwm=0;

  	
 	  double weightedSumFront = 0;
 	  double weightedSumBack = 0; 
 	  double sumfront = 0; 
  	double sumback = 0;

    int fronterror = newSensor.errorFront;
    int backerror = newSensor.errorBack;

    int signedErrorF = fronterror;
    int signedErrorB = backerror;

    if (newSensor.isFrontAllWhite())
    {
      newSensor.preserveHistoryF = true;
      // Maximize Error with History-Direction
      if (oldSensor.lsaFront[0])
        signedErrorF = -22; 
      else if (oldSensor.lsaFront[7])
        signedErrorF = 22;  
    }

    if (newSensor.isBackAllWhite())
    {
        newSensor.preserveHistoryB=true;
        // Maximize Error with History-Direction
        if (oldSensor.lsaBack[0])
          signedErrorB = 26;
        else if (oldSensor.lsaBack[7])
          signedErrorB = -26;
    }

    if (signedErrorF < 0)
    {	// left
      frontpwm = abs(signedErrorF);
      motor.direction[MOTOR_FRONT] = true;
    }
    else 
    {	//right
      frontpwm = abs(signedErrorF);
      motor.direction[MOTOR_FRONT] = false;
    }
    
    if (signedErrorB < 0)
    {	//left
      backpwm = abs(signedErrorB);
      motor.direction[MOTOR_BACK] = true;
    }
    else {	//right
      backpwm = abs(signedErrorB);
      motor.direction[MOTOR_BACK] = false;
    }
    // cout<<"frontpwm without MApping:"<<frontpwm<<endl;
    // cout<<"backpwm without MApping:"<<backpwm<<endl;

    motor.PWM[MOTOR_FRONT] = Vmap(frontpwm, 0, 22, 80, 105);
    motor.PWM[MOTOR_BACK] = Vmap(backpwm, 0, 14, 80, 105);

    // cout<<"frontpwm after Mapping:"<<motor.PWM[MOTOR_FRONT]<<endl;
    // cout<<"backpwm after Mapping:"<<motor.PWM[MOTOR_BACK]<<endl;
}


void loop(botData& newSensor,botData& oldSensor,Motor& motor)
{
   calculate_pid(newSensor,oldSensor,motor); 
   motor.BOT_FORWARD();
   motor.setPWMof(MOTOR_RIGHT,200);
   motor.setPWMof(MOTOR_LEFT,200);
}
