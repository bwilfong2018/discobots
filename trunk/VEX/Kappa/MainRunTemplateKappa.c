#pragma config(Sensor, in1,    potArm,              sensorPotentiometer)
#pragma config(Sensor, dgtl1,  EncoderRight,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  EncoderLeft,         sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  AButton,             sensorTouch)
#pragma config(Motor,  port2,           RightDrive,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           LeftDrive,     tmotorNormal, openLoop)
#pragma config(Motor,  port4,           LeftArm1,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           RightArm,      tmotorNormal, openLoop)
#pragma config(Motor,  port6,           RightTread,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           LeftArm2,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           LeftTread,     tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "KappaLib.c"
#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "Encoder2.c"                    //Autonomous Encoder control
#include "PIDController.h"              //Autonomous PID Arm controller
/*#define MAX_ARM 110
#define MAX_TREAD 127

int KP = 1;
int KI = 0;
int KD = 0;

controller PID;

//set Values
int armGround = SensorValue[potArm];
int lowScore = armGround;// + value still to be tested;
int medScore = armGround;// + value still to be tested;
int highScore = armGround;// + value still to be tested;*/


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
    encoderConfigure(4,2,90,127,(14.375/12.0),(4.0/12.0));
    init(PID,potArm,port4);
    setSetpoint(PID, highScore);
    setPIDs(PID, KP, KI, KD);
    enable(PID);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////


bool driveComplete = false;
task autoDrive()
{
  driveComplete = false;
  encoderDriveStraight(44.0/12.0);
  driveComplete = true;

}

bool armUp = false;
task autoArm()
{
  armUp = false;
  setSetpoint(PID, highScore);
  enable(PID);
  while(calcPID(PID) != 0)
  {
    setArmSpeed(calcPID(PID));
  }
  armUp = true;
}

task autonomous()
{
  pre_auton();
  while(true)
  {
    if(vexRT[AButton] == 1)
    {
      StartTask(autoDrive);
      StartTask(autoArm);
      while(!(armUp && driveComplete));

      setCollectorSpeed(MAX_TREAD);
      wait10Msec(200);
      encoderDriveStraight(-44.0/12.0);
      motor[RightTread] = motor[LeftTread] = 0;
    }
  }
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
  while(true)
  {
    tankDrive();
    TreadDrive();
    PIDArmControl();
  }
}
