//Difference in value between sensors
//If on line line, 0 = center, negative value = robot to far left of line, positive value = to far right
int brightest = 1024;
int i = 0;
int lineaverage;
int lasttask;
bool junction = false;
const int left = 0;
const int right = 1;
const int centre = 2;
const bool front = true;
const bool back = false;

//Drive forward or backward until it sees the line
void findline(int sensor, int speed, int timeout)
{
  motor[DriveLeft] = speed;
  motor[DriveRight] = speed;
  ClearTimer(T1);
  switch (sensor)
  {
  case back:
    while (SensorValue(GreyCentre) > SensorValue(CentreRightLine) - 200 && time1[T1] < timeout)
    {
    }
    break;
  case front:
    while (SensorValue(CentreRightLine) > SensorValue(GreyCentre) - 200 && time1[T1] < timeout)
    {
    }
    break;
  }
}

//Spin until the robot finds the line
void findlineturn(int direction, int speed, int timeout)
{
  switch(direction)
  {
  case left:
    motor[DriveLeft] = -speed;
    motor[DriveRight] = speed;
    ClearTimer(T1);
    while (SensorValue(CentreRightLine) > SensorValue(Right2Line) - 200 && time1[T1] < timeout)
    {
    }
    break;
  case right:
    motor[DriveLeft] = speed;
    motor[DriveRight] = -speed;
    ClearTimer(T1);
    while (SensorValue(CentreRightLine) > SensorValue(LeftLine) - 100 && time1[T1] < timeout)
    {
    }
    break;
  }
}

//Wait until it detects a junction
void waitforjunction(int timeout)
{
  ClearTimer(T1);
  junction = false;
  while (junction == false && time1[T1] < timeout)
  {
  }
}

//Follow the line
task followline()
{

  while(true)
  {

    //Detect junction
    if (SensorValue(LeftLine) < SensorValue(Grey) - 100 && SensorValue(Right2Line) < SensorValue(Grey) - 100)
    {
      junction = true;
    }

    //Find which sensor line is under
    if (SensorValue(LeftLine) < brightest)
    {
      brightest = SensorValue(LeftLine);
      i = 1;
    }
    if (SensorValue(CentreLeftLine) < brightest)
    {
      brightest = SensorValue(CentreLeftLine);
      i = 2;
    }
    if (SensorValue(CentreRightLine) < brightest)
    {
      brightest = SensorValue(CentreRightLine);
      i = 3;
    }
    if (SensorValue(RightLine) < brightest)
    {
      brightest = SensorValue(RightLine);
      i = 4;
    }
    if (SensorValue(Right2Line) < brightest)
    {
      brightest = SensorValue(Right2Line);
      i = 5;
    }
    brightest = 1024;


    //Check that at least one line sensor is on line
    lineaverage = (SensorValue(LeftLine) + SensorValue(CentreLeftLine) + SensorValue(CentreRightLine) + SensorValue(RightLine) + SensorValue(Right2Line))/5;
    //If one sensor senses a brighter value than all the other sensors, then assume the robot is over the line
    if (

    (
    (SensorValue(LeftLine) < lineaverage + 40)
    &&
    (SensorValue(LeftLine) > lineaverage - 40)
    )

    &&
    (
    (SensorValue(CentreLeftLine) < lineaverage + 40)
    &&
    (SensorValue(CentreLeftLine) > lineaverage - 40)
    )

    &&
    (
    (SensorValue(CentreRightLine) < lineaverage + 40)
    &&
    (SensorValue(CentreRightLine) > lineaverage - 40)
    )

    &&
    (
    (SensorValue(RightLine) < lineaverage + 40)
    &&
    (SensorValue(RightLine) > lineaverage - 40)
    )

    &&
    (
    (SensorValue(Right2Line) < lineaverage + 40)
    &&
    (SensorValue(Right2Line) > lineaverage - 40)
    )

    )

    {
      switch(lasttask)
      {
        //Spin Left
      case true:
        motor[DriveLeft] = -80;
        motor[DriveRight] = 0;
        break;

        //Spin Right
      case false:
        motor[DriveLeft] = 0;
        motor[DriveRight] = -80;
        break;
      }

    }
    else
    {

      //Turn proportional to the error
      switch (i)
      {
      case 1:
        motor[DriveLeft] = 70;
        motor[DriveRight] = 100;
        lasttask = true;
        break;
      case 2:
        motor[DriveLeft] = 85;
        motor[DriveRight] = 120;
        break;
      case 3:
        motor[DriveLeft] = 127;
        motor[DriveRight] = 127;
        break;
      case 4:
        motor[DriveLeft] = 120;
        motor[DriveRight] = 85;
        break;
      case 5:
        motor[DriveLeft] = 100;
        motor[DriveRight] = 70;
        lasttask = false;
        break;
      }
    }


  }
}
