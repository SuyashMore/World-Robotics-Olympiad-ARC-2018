#pragma once

#include "containers.h"


void processPID(botData& newSensor,botData& oldSensor,Motor& motor)
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
    
    motor.PWM[MOTOR_FRONT] = Vmap(frontpwm, F_MOTOR_MAP_INLOW, F_MOTOR_MAP_INHIGH, F_MOTOR_MAP_OUTLOW, F_MOTOR_MAP_OUTHIGH);
    motor.PWM[MOTOR_BACK] = Vmap(backpwm, B_MOTOR_MAP_INLOW, B_MOTOR_MAP_INHIGH, B_MOTOR_MAP_OUTLOW, B_MOTOR_MAP_OUTHIGH);
}

bool followLine(botData& newSensor,botData& oldSensor,Motor& motor)
{
   processPID(newSensor,oldSensor,motor);
   motor.bot_Forward_withPWMm(FORWARD_MOTION_PWM);
   return true;
}

