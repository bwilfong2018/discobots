#pragma config(Sensor, dgtl1,  solenoid,            sensorDigitalOut)
#pragma config(Motor,  port1,           liftL,         tmotorNormal, openLoop)
#pragma config(Motor,  port2,           rFront,        tmotorNormal, openLoop)
#pragma config(Motor,  port3,           rFront2,       tmotorNormal, openLoop)
#pragma config(Motor,  port4,           rBack,         tmotorNormal, openLoop)
#pragma config(Motor,  port5,           lFront,        tmotorNormal, openLoop)
#pragma config(Motor,  port6,           lFront2,       tmotorNormal, openLoop)
#pragma config(Motor,  port7,           lBack,         tmotorNormal, openLoop)
#pragma config(Motor,  port8,           collectorR,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           collectorL,    tmotorNormal, openLoop)
#pragma config(Motor,  port10,          liftR,         tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


//left drive
void setDriveLSpeed(int speed) {
  motor[lFront] = motor[lFront2] = motor[lBack] = speed;
}

//right drive
void setDriveRSpeed(int speed) {
  motor[rFront] = motor[rFront2] = motor[rBack] = speed;
}

//drive
void setDriveSpeed(int speed) {
setDriveLSpeed(speed);
setDriveRSpeed(speed);
}



task main ()
{

  while(1 == 1)
  {
 //left drive
setDriveLSpeed(vexRT[Ch3]);
    //right drive
setDriveRSpeed(vexRT[Ch2]);

    //Lift code

    motor[liftL] = motor[liftR] = ((vexRT[Btn5U]- vexRT[Btn5D])*127);

    //collector code

    motor[collectorL] = motor[collectorR] = ((vexRT[Btn6U]- vexRT[Btn6D])*127);

    //pneumatics collector flip code

    if(vexRT[Btn8U]==1)
    {
      SensorValue[solenoid]=1;
      }

    else if(vexRT[Btn8D]==1)
    {
      SensorValue[solenoid]=0;
      }


  }

}
