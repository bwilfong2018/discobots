#pragma config(Motor,  port2,           FrontLeft1,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           FrontLeft2,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           BackLeft,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           BackRight,     tmotorNormal, openLoop)
#pragma config(Motor,  port8,           FrontRight1,   tmotorNormal, openLoop)
#pragma config(Motor,  port9,           FrontRight2,   tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Vex_Competition_Includes.c"
#include "Zetta_Mecanum.c"
#include "Zetta_Tank.c"
#include "Zetta_Simple_Mechanum.c"

void pre_auton(){
}

task autonomous(){
}

task usercontrol(){
  while(true){
    simpleMechanumDrive();
  }
}
