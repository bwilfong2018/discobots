#pragma config(Sensor, in1,    PotArm,              sensorPotentiometer)
#pragma config(Sensor, in2,    DetectTube,          sensorLineFollower)
#pragma config(Sensor, dgtl1,  EncoderR,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  EncoderL,            sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  BaseSonar,           sensorSONAR_cm)
#pragma config(Sensor, dgtl7,  Pneu1,            sensorDigitalOut)
#pragma config(Sensor, dgtl11, ArmUp,               sensorTouch)
#pragma config(Sensor, dgtl12, ArmDown,             sensorTouch)
#pragma config(Motor,  port1,           DriveRB,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           DriveRF,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           DriveLF,       tmotorNormal, openLoop)
#pragma config(Motor,  port4,           ArmRL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           ArmLL,         tmotorNormal, openLoop)
#pragma config(Motor,  port6,           ArmRU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           ArmLU,         tmotorNormal, openLoop)
#pragma config(Motor,  port8,           SuckR,         tmotorNormal, openLoop)
#pragma config(Motor,  port9,           SuckL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          DriveLB,       tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


//---------------------------------/ Functions Prototypes /--------------------------------------//
//--------------------------------/                        /-------------------------------------//
//-------------------------------/                          /------------------------------------//
/*void drive(int driveSpeed, float r);
void drive_suck(int driveSpeed, int suckSpeed, float r);
void turn_left(int, driveSpeed, float r);
void turn_right(int, driveSpeed, float r);
void raise_arm(int armSpeed, int finalPos);
void lower_arm(int armSpeed, int finalPos);
void suck(int suckSpeed, int msec);
*/
//--/ PID /-------------------------------------------------------/

int startpoint = 0;
int goal_value = startpoint;
int change = -1000;
int k_P = 10;
int k_I = 0;
int k_D = 0;

//--/ Arm Position /----------------------------------------------/
int low_descore;
int low_lock;
int high_descore;
int high_lock;

//--Declare Global Variables--------------------------------------/
/* 'rotations' will be a counter for every 360 encoder clicks */
/* which is one full rotation of the wheel (ie. 2 'rotations' */
/* will equal 720.0 clicks, 2 full rotations of the wheel).   */
const float rotations = 360.0;
//---------------------------------/ Library /-------------------------------------------------//
//--------------------------------/           /------------------------------------------------//
//-------------------------------/             /-----------------------------------------------//

//-------------------------------------------| MOTOR SHORTCUTS |---------------------------------------
/*Set Arm Speed*/
void setArmSpeed(int speed) {
  motor[ArmLL] = motor[ArmLU] = motor[ArmRL] = motor[ArmRU] = speed;
}

/*Set Suck Speed*/
void setSuckSpeed(int speed) {
  motor[SuckR] = motor[SuckL] = speed;
}

/*Set Drive Speed: Left & Right*/
void setDriveSpeed(int speed) {
  motor[DriveRF] = motor[DriveRB] = motor[DriveLF] = motor[DriveLB] = speed;
}

/*Set Drive Right Speed*/
void setDriveRSpeed(int speed) {
  motor[DriveRF] = motor[DriveRB] = speed;
}

/*Set Drive Left Speed*/
void setDriveLSpeed(int speed) {
  motor[DriveLF] = motor[DriveLB] = speed;
}

/*Kill Drive Train Motors*/
void killdrive() {
  setDriveSpeed(0);
}
/*Kill Arm Motors*/
void killarm() {
  setArmSpeed(0);
}
/*Kill Suck Motors*/
void killsuck() {
  setSuckSpeed(0);
}


//----------------------------------------------| FORWARD |---------------------------------------------
void drive(int driveSpeed, float r)
{
  SensorValue[EncoderR] = 0;    /* Clear the encoders for    */
  SensorValue[EncoderL] = 0;    /* consistancy and accuracy. */

  // While the encoders have not yet met their goal: (r * rotations) ie (3.0 * 360.0) or "three rotations"
  while(SensorValue[EncoderR] < (r * rotations) && SensorValue[EncoderL] < (r * rotations))
  {
    setDriveSpeed(driveSpeed); /* Run all motors */ /* at driveSpeed. */
  }
  killdrive();
}
//--------------------------------------------| FORWARD + SUCK |---------------------------------------------
void drive_suck(int driveSpeed, int suckSpeed, float r)
{
  SensorValue[EncoderR] = 0;    /* Clear the encoders for     */
  SensorValue[EncoderL] = 0;    /* consistancy and accuracy. */
  // While the encoders have not yet met their goal: (r * rotations) ie (3.0 * 360.0) or "three rotations"
  while(SensorValue[EncoderR] < (r * rotations) && SensorValue[EncoderL] < (r * rotations))
  {
    setDriveSpeed(driveSpeed);
    setSuckSpeed(suckspeed);
  }
  killdrive();
  killsuck();
}
//--------------------------------------------| Arc |---------------------------------------------
void drive_arc(int rightSpeed, int leftSpeed, float r)
{
  SensorValue[EncoderR] = 0;    /* Clear the encoders for    */
  SensorValue[EncoderL] = 0;    /* consistancy and accuracy. */

  // While the encoders have not yet met their goal: (r * rotations) ie (3.0 * 360.0) or "three rotations"
  while(SensorValue[EncoderR] < (r * rotations) && SensorValue[EncoderL] < (r * rotations))
  {
    setDriveRSpeed(rightSpeed);
    setDriveLSpeed(leftSpeed);
  }
  killdrive();
}
//-------------------------------------------| TURN LEFT |--------------------------------------------
void turn_left(int driveSpeed, float r)
{
  SensorValue[EncoderR] = 0;    /* Clear the encoders for    */
  SensorValue[EncoderL]  = 0;    /* consistancy and accuracy. */

  // While the encoders have not yet met their goal: (left is compared negativly since it will in reverse)
  while(SensorValue[EncoderR] < (r * rotations) && SensorValue[EncoderL] > (-1 * r * rotations))
  {
    setDriveRSpeed(driveSpeed);
    setDriveLSpeed(-driveSpeed);
  }
  killdrive();
}
//-------------------------------------------| TURN RIGHT |-------------------------------------------
void turn_right(int driveSpeed, float r)
{
  SensorValue[EncoderR] = 0;    /* Clear the encoders for    */
  SensorValue[EncoderL]  = 0;    /* consistancy and accuracy. */

  // While the encoders have not yet met their goal: (left is compared negativly since it will in reverse)
  while(SensorValue[EncoderL] < (r * rotations) && SensorValue[EncoderR] > (-1 * r * rotations))
  {
    setDriveRSpeed(-driveSpeed);
    setDriveLSpeed(driveSpeed);


  }
  killdrive()
}
//-------------------------------------------| MOVE ARM |---------------------------------------------
void move_arm(int armSpeed, int target)
{
  //Upper limit is 610, lower limit is 990
  //While the pot value is greater than +5 of the target, or less than -5 of the target...

  while(SensorValue(PotArm) > target + 5 || SensorValue(PotArm) < target - 5)
  {
    //If the pot value is greater than the target...move the arm up
    if (SensorValue(PotArm) > target)
    {
      setArmSpeed(-armSpeed);
      //motor[port5] = (speed) + 35;
      //motor[port6] = (speed * -1) + 35;
    }
    //If the pot value is less than the target...move the arm down
    if (SensorValue(PotArm) < target)
    {
      setArmSpeed(armSpeed);
      //motor[port5] = (speed * -1) + 35;
      //motor[port6] = (speed) + 35;
    }
  }
  setArmSpeed(0);
  //motor[port5] = 15;
  //motor[port6] = -15;
}
//-------------------------------------------| RAISE ARM |---------------------------------------------
void raise_arm(int armSpeed, int finalPos)
{
  if (SensorValue[PotArm] < finalPos){
    motor[ArmRU] = armSpeed;
    motor[ArmRL] = armSpeed;
    motor[ArmLU] = armSpeed;
    motor[ArmLL] = armSpeed;
  }
  else {/*Zero Arm Motors*/
      motor[ArmRU] = 0;
    motor[ArmRL] = 0;
    motor[ArmLU] = 0;
    motor[ArmLL] = 0;
  }
}
//-------------------------------------------| LOWER ARM |---------------------------------------------
void lower_arm(int armSpeed, int finalPos)
{
  if (SensorValue[PotArm] > finalPos) {
    motor[ArmRU] = -armSpeed;
    motor[ArmRL] = -armSpeed;
    motor[ArmLU] = -armSpeed;
    motor[ArmLL] = -armSpeed;
  }
  else {/*Zero Arm Motors*/
      killarm();
  }
}
//-------------------------------------------| SUCK |--------------------------------------------------
void Suck(int suckSpeed, int msec) {
  setSuckSpeed(suckSpeed);
  wait1Msec(msec);
  killsuck();
}
