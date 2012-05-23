#pragma config(Sensor, dgtl1,  pneu1,          sensorDigitalOut)
#pragma config(Sensor, dgtl2,  pneu2,          sensorDigitalOut)
#pragma config(Sensor, dgtl3,  pneu3,          sensorDigitalOut)
#pragma config(Sensor, dgtl4,  pneu4,          sensorDigitalOut)
#pragma config(Motor,  port1,           right3,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           right1,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           right2,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           left1,         tmotorNormal, openLoop)
#pragma config(Motor,  port5,           left2,         tmotorNormal, openLoop)
#pragma config(Motor,  port10,          left3,         tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int typeDrive = 1;
const int Drive = 1;
const int tracDrive = 2;
task main()
{
  while(true){
   switch (typeDrive)
  {
  case  Drive:
    {
      SensorValue[pneu1] =   SensorValue[pneu2] =   SensorValue[pneu3] =   SensorValue[pneu4] = 0;
      motor[right1] = motor[right2] = motor[right3] = vexRT[Ch2];
      motor[left1] = motor[left2] = motor[left3] = vexRT[Ch3];

      if(vexRT[Btn8D] == 1)
        typeDrive = tracDrive;
    }// case
    break;
  case tracDrive:
    {

 SensorValue[pneu1] =   SensorValue[pneu2] =   SensorValue[pneu3] =   SensorValue[pneu4] = 1;
      motor[right1] = motor[right2] = motor[right3] = vexRT[Ch2];
      motor[left1] = motor[left2] = motor[left3] = vexRT[Ch3];
      if(vexRT[Btn8U] == 1)
        typeDrive = Drive;
    }//case
    break;
  }//switch

}//while
}