#pragma config(UART_Usage, UART2, VEX_2x16_LCD, baudRate19200, IOPins, None, None)
#pragma config(Sensor, dgtl6,  startAuton,          sensorTouch)
#pragma config(Sensor, dgtl7,  encoderL,            sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  solenoidL,           sensorDigitalOut)
#pragma config(Sensor, dgtl10, solenoidR,           sensorDigitalOut)
#pragma config(Sensor, dgtl11, encoderR,            sensorQuadEncoder)
#pragma config(Motor,  port1,           collectorL,    tmotorNormal, openLoop)
#pragma config(Motor,  port2,           frontL,        tmotorNormal, openLoop)
#pragma config(Motor,  port3,           frontL2,       tmotorNormal, openLoop)
#pragma config(Motor,  port4,           backL,         tmotorNormal, openLoop)
#pragma config(Motor,  port5,           backL2,        tmotorNormal, openLoop)
#pragma config(Motor,  port6,           frontR,        tmotorNormal, openLoop)
#pragma config(Motor,  port7,           frontR2,       tmotorNormal, openLoop)
#pragma config(Motor,  port8,           backR,         tmotorNormal, openLoop)
#pragma config(Motor,  port9,           backR2,        tmotorNormal, openLoop)
#pragma config(Motor,  port10,          collectorR,    tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/*To example of use:
setSuckSpeed(127);
type desired speed, between -127 and 127, between ()*/
void setSuckSpeed(int speed)
{
  motor[collectorL] = motor[collectorR] = speed;
}// void //


void killDrive(){
  motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = 0;
}//END void //

void pre_auton()
{
	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}//END void //


task autonomous()
{
  while(SensorValue[startAuton] == 0) {

    SensorValue[solenoidL] = SensorValue[solenoidR] = 1;     //raises lift...
    wait1Msec(2000000);

}//end while statement


  motor[frontL] = motor[frontL2] = motor[backL] = -127;  //drives backwards to the big goal...
  motor[frontR] = motor[frontR2] = motor[backR] = -127;
  wait1Msec(900);
  killDrive();                                           // kils drivetrain...

  motor[frontL] = motor[frontL2] = motor[backL] = -127;  //switches sides of the goal...
  wait1Msec(500);
  killDrive();                                           // kill drivetrain...

  setSuckSpeed(127);                                     //scores tubes in high goal...
  wait1Msec(4000);
  setSuckSpeed(0);                                       //stop collector from spinning...

  motor[frontR] = motor[frontR2] = motor[backR] = -127;  //comes back to original side of goal...
  wait1Msec(500);
  killDrive();                                           //kill drivetrain...

  motor[frontL] = motor[frontL2] = motor[backL] = 127;   //drives back to blue sqaure...
  motor[frontR] = motor[frontR2] = motor[backR] = 127;
  wait1Msec(900);
  killDrive();                                           //kill drive train...

  SensorValue[solenoidL] = SensorValue[solenoidR] = 0;   //lowers lift...
  wait1Msec(3000);                                       //waits for three secs as we put 2 more preloads in...

  motor[frontL] = motor[frontL2] = motor[backL] = -127;  //drives backwards to low goal...
  motor[frontR] = motor[frontR2] = motor[backR] = -127;
  wait1Msec(300);
  killDrive();                                           //kil drive train...

  setSuckSpeed(127);                                     //scores tubes in low goal...
  wait1Msec(2000);
  setSuckSpeed(0);                                       //stop collector from spinning...

  motor[frontL] = motor[frontL2] = motor[backL] = 127;   //comes back to blue tile...
  motor[frontR] = motor[frontR2] = motor[backR] = 127;
  wait1Msec(300);

  killDrive();                                           //kill drive train.




}// task autonomous //

//////////////////////////////////////////////////////////////RED INTERACTION AUTON

/*
while(SensorValue[startAuton] == 0) {

SensorValue[liftPneu1] = SensorValue[liftPneu2] = 1;     //raises lift...
wait1Msec(2000000);

}//end while statement


motor[frontL] = motor[frontL2] = motor[backL] = -127;  //drives backwards to the big goal...
motor[frontR] = motor[frontR2] = motor[backR] = -127;
wait1Msec(900);
killDrive();                                           // kils drivetrain...

motor[frontR] = motor[frontR2] = motor[backR] = -127;  //switches sides of the goal...
wait1Msec(500);
killDrive();                                           // kill drivetrain...

setSuckSpeed(127);                                     //scores tubes in high goal...
wait1Msec(4000);
setSuckSpeed(0);                                       //stop collector from spinning...

motor[frontL] = motor[frontL2] = motor[backL] = -127;  //comes back to original side of goal...
wait1Msec(500);
killDrive();                                           //kill drivetrain...

motor[frontL] = motor[frontL2] = motor[backL] = 127;   //drives back to blue sqaure...
motor[frontR] = motor[frontR2] = motor[backR] = 127;
wait1Msec(900);
killDrive();                                           //kill drive train...

SensorValue[liftPneu1] = SensorValue[liftPneu2] = 0;   //lowers lift...
wait1Msec(3000);                                       //waits for three secs as we put 2 more preloads in...

motor[frontL] = motor[frontL2] = motor[backL] = -127;  //drives backwards to low goal...
motor[frontR] = motor[frontR2] = motor[backR] = -127;
wait1Msec(300);
killDrive();                                           //kil drive train...

setSuckSpeed(127);                                     //scores tubes in low goal...
wait1Msec(2000);
setSuckSpeed(0);                                       //stop collector from spinning...

motor[frontL] = motor[frontL2] = motor[backL] = 127;   //comes back to blue tile...
motor[frontR] = motor[frontR2] = motor[backR] = 127;
wait1Msec(300);
\
killDrive();                                           //kill drive train.




}// task autonomous //

*/




task usercontrol()
{
	while (true)
	{

////////PNEUMATICS/////////////////////////////////////////////////////////////////////////////

 if(vexRT[Btn5U] == 1)   {      // If button 5U is pressed:
SensorValue[solenoidL] = SensorValue[solenoidR] = 1;  // ...both pneumatics shoot out.
}//end if

 else if(vexRT[Btn5D] == 1)  {   // If button 5D is pressed:
SensorValue[solenoidL] = SensorValue[solenoidR] = 0;  // ...both pneumatics shoot in.
}//end else if

//////////////////COLLECTOR///////////////////////////////////////////////////////////////////

 if(vexRT[Btn6U] == 1) {
motor[collectorL] = motor[collectorR] = 127;//if btn 6u is pressed turn both collector motors at full suck in
}//end if
 else if(vexRT[Btn6D] == 1) {
motor[collectorL] = motor[collectorR] = -127;//if btn 6d is pressed turn both collector motors at full spitout
}//end else if
 else {
motor[collectorL] = motor[collectorR] = 0;//if no btn is pressed turn neither motors
}//end else

/////////////////DRIVETRAIN/////////////////////////////////////////////////////////////////////

motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = vexRT[Ch3];//L drivetrain speed = y axis of L joystick values
motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = vexRT[Ch2];//R drivetrain speed = y axis of R joystick values


	}//end while loop
}//end task usercontrol