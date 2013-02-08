`#pragma config(Sensor, in1,    pot,                 sensorPotentiometer)
#pragma config(Sensor, in2,    gyro,                sensorLineFollower)
#pragma config(Sensor, in3,    l2,                  sensorLineFollower)
#pragma config(Sensor, in4,    l3,                  sensorLineFollower)
#pragma config(Sensor, dgtl1,  sonar,               sensorSONAR_cm)
#pragma config(Sensor, dgtl4,  ncoderR,             sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  ,                    sensorSONAR_inch)
#pragma config(Motor,  port1,           ,              tmotorNormal, openLoop)
#pragma config(Motor,  port2,           left,          tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           right,         tmotorNormal, openLoop)
#pragma config(Motor,  port6,           port6,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           port7,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           port8,         tmotorNormal, openLoop)
#pragma config(Motor,  port9,           port9,         tmotorNormal, openLoop)
#pragma config(Motor,  port10,          Claw,          tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//variables:
int programselect = 1;
bool redteam = true;
bool programselecting = true;
const int totalprogramnumber = 5;

//function:
void turn_right()
{
  motor[right] = 127;
  motor[left] = -127;
}
void turn_left()
{
  motor[right] = -127;
  motor[left] =127;
}
void go_straight()
{
	motor[right] = 127;
  motor[left] = 127;
}

void cleargyro()
{
SensorValue[gyro] = 0;
}
void screenrefresh()
{
  clearLCDLine(1);
  displayLCDPos(1,0);
  if (redteam == true)
  {
    displayNextLCDString("RED ");
  }
  if (redteam == false)
  {
    displayNextLCDString("BlUE");
  }
  displayNextLCDString("    ");
  displayNextLCDNumber(programselect);
  displayNextLCDString("     OK");
}
void stopallmotors()
{
  motor[right] = 0;
  motor[left] = 0;
}
void red2()
{

      while(true)
      {
        cleargyro();
        if(SensorValue(sonar) <50)		// Loop while robot's Ultrasonic sensor is further than 20 inches away from an object
        {

          while(SensorValue[gyro] < 500){
              turn_left();
            }

          go_straight();

        }
        else
        {
          motor[right] = 127;
          motor[left] = 127;
        }


      }
}