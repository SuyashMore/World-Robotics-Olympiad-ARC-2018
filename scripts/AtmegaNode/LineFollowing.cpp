#pragma once

#include "containers.h"


void processPID(botData& newSensor,botData& oldSensor,Motor& motor)
{
 	bool preserveHistoryF =false;
  	bool preserveHistoryB = false;

  	int frontpwm=0;
  	int backpwm=0;
    float kd =1.5; 
  	
 	 double weightedSumFront = 0;
 	 double weightedSumBack = 0; 
 	 double sumfront = 0; 
  	double sumback = 0;

    int fronterror = -newSensor.errorFront;
    int backerror = newSensor.errorBack;
    int fronterrorprevious = -oldSensor.errorFront;
    int backerrorprevious = oldSensor.errorBack;

    int signedErrorF = fronterror;
    int signedErrorB = backerror;

    if (newSensor.isFrontAllWhite())
    {
      newSensor.preserveHistoryF = true;
      // Maximize Error with History-Direction
      if (oldSensor.lsaFront[0])
        signedErrorF = 3500; 
      else if (oldSensor.lsaFront[7])
        signedErrorF = -3500;  
    }

    if (newSensor.isBackAllWhite())
    {
        newSensor.preserveHistoryB=true;
        // Maximize Error with History-Direction
        if (oldSensor.lsaBack[0])
          signedErrorB = 3500;
        else if (oldSensor.lsaBack[7])
          signedErrorB = -3500;
    }

    if (signedErrorF >0 )
    {
    	//shifted right - > Move Left
      	frontpwm = abs(signedErrorF);
      	motor.direction[MOTOR_FRONT] = true;
    }
    else 
    {	
      	// shifted left - > Move Right
      	frontpwm = abs(signedErrorF);
      	motor.direction[MOTOR_FRONT] = false;
    }
    
    if (signedErrorB > 0)
    {	//Shifted Right -> Move Left
      backpwm = abs(signedErrorB);
      motor.direction[MOTOR_BACK] = false;
    }
    else {	
    	//Shifted Left - > Move Right
      backpwm = abs(signedErrorB);
      motor.direction[MOTOR_BACK] = true;
    }
    frontpwm -= (fronterrorprevious - fronterror)*kd;
    backpwm -= (backerrorprevious - backerror)*kd;
    
    motor.PWM[MOTOR_FRONT] = Vmap(frontpwm, F_MOTOR_MAP_INLOW, F_MOTOR_MAP_INHIGH, F_MOTOR_MAP_OUTLOW, F_MOTOR_MAP_OUTHIGH);
    motor.PWM[MOTOR_BACK] = Vmap(backpwm, B_MOTOR_MAP_INLOW, B_MOTOR_MAP_INHIGH, B_MOTOR_MAP_OUTLOW, B_MOTOR_MAP_OUTHIGH);

 //   if(frontpwm<250)
	// motor.PWM[MOTOR_FRONT]=0;
 //   if(backpwm<250)
	// motor.PWM[MOTOR_BACK]=0;
}

bool followLine(botData& newSensor,botData& oldSensor,Motor& motor)
{
   processPID(newSensor,oldSensor,motor);
   motor.bot_Forward_withPWMm(FORWARD_MOTION_PWM);
   return true;
}

bool followLineBackpwm(botData& newSensor,botData& oldSensor,Motor& motor,int pwm = 100)
{
  processPID(newSensor,oldSensor,motor);
   motor.bot_Backward_withPWMm(pwm);
   return true;
}
