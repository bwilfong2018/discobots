#pragma config(Sensor, dgtl1,  lift_max,            sensorTouch)
#pragma config(Motor,  port2,           LeftDrive,     tmotorNormal, openLoop)
#pragma config(Motor,  port3,           Rightdrive1,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           Rightdrive2,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           Lift,          tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           Arm,           tmotorNormal, openLoop)
#pragma config(Motor,  port7,           Claw,          tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
    SensorValue[dgtl1]=0;
    motor[port2]= 0;
	  motor[port3]= 0;
	  motor[port4]= 0;
	  motor[port5]= 0;
	  motor[port6]= 0;
	  motor[port7]= 0;
	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................

	AuonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
	  int arm_delta = vexRT[Btn7U]-vexRT[Btn7D];
	  int claw_delta = (vexRT[Btn5U]-vexRT[Btn5D]);
	  int lift_delta = (vexRT[Btn6U]-vexRT[Btn6D]);
	  // This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

	  // .....................................................................................
	  // Insert user code here. This is where you use the joystick values to update your motors, etc.
	  // .....................................................................................

	  motor[port2]= vexRT[Ch3];
	  motor[port3]= vexRT[Ch2];
	  motor[port4]= vexRT[Ch2];
	  /*if(SensorValue[dgtl1]==1&&vexRT[Btn6U]>0)
	    motor[port5]=0;
	 else */
	  if(lift_delta > 0){
	    motor[port5]=lift_delta*127;
	  }
	  else if (lift_delta <0)
	    motor[port5]=lift_delta*64;
	  else
	    motor[port5]=vexRT[Btn8R]*10;

	  if(arm_delta > 0)
	    motor[port6]=(arm_delta)*127  ;
	  else if (arm_delta < 0)
	    motor[port6]=(arm_delta)*20;
	    else motor[port6] = 0;

	  if(claw_delta > 0)
	    motor[port7]=(claw_delta)*40;
	  else if (claw_delta < 0) {
	    if (vexRT[Btn7D] > 0)
	     motor[port7]=(claw_delta)*90;
	    else
	    motor[port7]=(claw_delta)*25;
	  }
	  else motor[port7] = 0;


	}

}