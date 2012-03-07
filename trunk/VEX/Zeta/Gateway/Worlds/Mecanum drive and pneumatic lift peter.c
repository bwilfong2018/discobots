#pragma config(Sensor, dgtl9,  solenoidL,           sensorDigitalOut)
#pragma config(Sensor, dgtl10, solenoidR,           sensorDigitalOut)
#pragma config(Motor,  port2,           frontRight,    tmotorNormal, openLoop)
#pragma config(Motor,  port3,           frontRight2,   tmotorNormal, openLoop)
#pragma config(Motor,  port4,           backRight,     tmotorNormal, openLoop)
#pragma config(Motor,  port5,           frontLeft,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           frontLeft2,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           backLeft,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           collectorR,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           collectorL,    tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

 void setSuckSpeed(int speed) {
motor[collectorL] = motor[collectorR] = speed;
}//end void


/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++
Mecanum Drive with Deadzone Thresholds
- This program allows you to remotely control a robot with mecanum wheels.
- The left joystick Y-axis controls the robot's forward and backward movement.
- The left joystick X-axis controls the robot's left and right movement.
- The right joystick X-axis controls the robot's rotation.
- This program incorportes a threshold/deadzone that allows very low Joystick values to be ignored.
This allows the robot to ignore values from the Joysticks when they fail to center at 0,
and provides a margin of error for the driver when they only want the robot to move in one axis.

[I/O Port]          [Name]              [Type]                [Description]
Motor Port 2        frontRight          VEX Motor             Front Right motor
Motor Port 3        backRight           VEX Motor             Back Right motor
Motor Port 4        frontLeft           VEX Motor             Front Left motor
Motor Port 5        backLeft            VEX Motor             Back Left motor
--------------------------------------------------------------------------------------------------*/

task main()
{
//Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone
int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;

//Loop Forever
while(1 == 1)
{
//Create "deadzone" for Y1/Ch3
if(abs(vexRT[Ch3]) > threshold)
Y1 = vexRT[Ch3];
else
Y1 = 0;
//Create "deadzone" for X1/Ch4
if(abs(vexRT[Ch4]) > threshold)
X1 = vexRT[Ch4];
else
X1 = 0;
//Create "deadzone" for X2/Ch1
if(abs(vexRT[Ch1]) > threshold)
X2 = vexRT[Ch1];
else
X2 = 0;

//Remote Control Commands
motor[frontRight]  = Y1 - X2 - X1;
motor[frontRight2] = Y1 - X2 - X1;
motor[backRight]   = Y1 - X2 + X1;
motor[frontLeft]   = Y1 + X2 + X1;
motor[frontLeft2]  = Y1 + X2 + X1;
motor[backLeft]    = Y1 + X2 - X1;



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

}//end while loop

}//end task main
