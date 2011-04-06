#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(200)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "Delta_Worlds_Function_Library_v1.0.c"
#include "Delta_Auton_Cheater_Blue_1.0.c"
/*
* Pot values NOT CODE
* arm_grounded = 1250
* descore_lock_point = 1680 - 1250 = 430
* low_lock_point = 2300 - arm grounded = 1050
* high_lock_point = 2587 - arm_grounded = 1337
*/

int arm_grounded;
int low_descore_point;
int low_lock_point;
int descore_high_point;
int high_lock_point;

/////PRE-AUTON///////////////////////////////////////////////////////////////////////////////////////////////////
void pre_auton()
{

//Encoders:
  SensorValue[EncoderL] = 0;
  SensorValue[EncoderR] = 0;

//Arm:
  arm_grounded = SensorValue[PotArm];    // sets ground point
  low_descore_point = arm_grounded + 500; // sets low descore arm pooint
  low_lock_point = arm_grounded + 800;   //...lowgoal
  high_lock_point = arm_grounded + 1100; // ...high goal
  arm_grounded += 250;
}
/////AUTON///////////////////////////////////////////////////////////////////////////////////////////////////////
task autonomous()
{
   pre_auton();

 //raise arm
  int arm_in_position = 0;  //arm is down; 0 for false and 1 for true
  while(arm_in_position != 1)
   {
	  arm_in_position = lock(low_lock_point);
	 }
 //drive forward to stack
  drive_straight(50, 2);//speed,


  {
   SensorValue[EncoderL] = 0;
   SensorValue[EncoderR] = 0;
   lock(low_lock_point);
  }
 }


/////TELE-OP/////////////////////////////////////////////////////////////////////////////////////////////////////
task usercontrol()
{
 pre_auton();

 int goal_lock = 0;
  //0 for unlocked, -1 for low gal, 1 for high goal
  //calibration for potentiometer setting the arm
  /*int low_lock_point = SensorValue[in1] + 703;
  //low goal potentiometer reading
  //sets the low lock point based on the starting potentiometer point int high_lock_point = SensorValue[in1] + 1000;
  //high goal potentiometer reading
  //end calibrarion*/
 while(true)
 {

  //Auto_Arm/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*
 	if(vexRT[Btn7L] == 1)//auto button close loop
  	{
   	goal_lock = -1;   //sets to low lock
  	}
 	else if(vexRT[Btn7U] == 1) {
   	goal_lock = 1;	//sets to high lock
  	}
 	else if(vexRT[Btn7D] == 1) {// descore/ score on low goal...
   	goal_lock = 2;
  	}

  	if(goal_lock == -1)
    	lock(low_lock_point); //brings to low lock point
  	else if(goal_lock == 1)
    	lock(high_lock_point);//moves arm to high lock point

  	///////////////////////////////////////////////////////////////NEW STUFF TAKE THIS OUT IF IT DOESNT WORK
  	else if (goal_lock == 2)
    	lock(low_descore_point);//moves arm to descore lock point
  	else if(goal_lock == 3)
    	lock(descore_high_point);
  	//////////////////////////////////////////////////////////////


    //Manual_Arm/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*

    if(vexRT[Ch3] < 15 && vexRT[Ch3] > -15){//Trim, if stick is between 15 & negative 15 motors equal 0.
      motor[ArmRL] = 0;
      motor[ArmRU] = 0;
      motor[ArmLL] = 0;
      motor[ArmLU] = 0;
      }
    else{//motors = stick angle
      motor[ArmRL] = vexRT[Ch3];
      motor[ArmRU] = vexRT[Ch3];
      motor[ArmLL] = vexRT[Ch3];
      motor[ArmLU] = vexRT[Ch3];
      }

    //Claw/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*
  	switch(vexRT[Btn5U] - vexRT[Btn5D])
    {
      case  1:motor[SuckR] = 127;
              motor[SuckL] = 127;
              break;
      case -1:motor[SuckR] = -127;
              motor[SuckL] = -127;
              break;
      case  0:motor[SuckR] = 0;
              motor[SuckL] = 0;
              break;
    }//: switch


    //Drive_Train/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*
    motor[DriveRB]  = (vexRT[Ch2] - vexRT[Ch1]);  // (y + x)
    motor[DriveRF]  = (vexRT[Ch2] - vexRT[Ch1]);  // (y + x)
    motor[DriveLB] = (vexRT[Ch2] + vexRT[Ch1]);  // (y - x)
    motor[DriveLF] = (vexRT[Ch2] + vexRT[Ch1]);  // (y - x)


 }//while
}//taskusercontrol
