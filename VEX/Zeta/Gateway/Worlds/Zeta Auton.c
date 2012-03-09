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

void drive_forward_msec(int speed, int duration) {
  motor[frontR]  = speed;
  motor[frontR2] = speed;
  motor[backR]   = speed;
  motor[backR2]  = speed;
  motor[frontL]  = speed;
  motor[frontL2] = speed;
  motor[backL]   = speed;
  motor[backL2]  = speed;

  wait1Msec(duration);

  motor[frontR]  = 0;
  motor[frontR2] = 0;
  motor[backR]   = 0;
  motor[backR2]  = 0;
  motor[frontL]  = 0;
  motor[frontL2] = 0;
  motor[backL]   = 0;
  motor[backL2]  = 0;

}//END void

void killDrive(){
  motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = 0;
}//END void //


/*To example of use:
setSuckSpeed(127);
type desired speed, between -127 and 127, between ()*/
void setSuckSpeed(int speed, int duration)   {
  motor[collectorL] = speed;
  motor[collectorR] = speed;
  wait1Msec(duration);
}// void //

task autonomous()
{

SensorValue[solenoidL] = SensorValue[solenoidR] = 1;
wait1Msec(2000);

drive_forward_msec(-127,800);
killDrive();

setSuckSpeed(127,4000);


}