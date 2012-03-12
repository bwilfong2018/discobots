#pragma config(Sensor, in7,    ,                    sensorGyro)
#pragma config(Sensor, in8,    ,                    sensorAccelerometer)
#pragma config(Sensor, in9,    ,                    sensorAccelerometer)
#pragma config(Sensor, in10,   ,                    sensorAccelerometer)
#pragma config(Motor,  port1,           Audio,         tmotorAudio, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

///////////////////////////////////////////////////////////////////////////////////////////////
//
//                          Program Chooser Application
//
// This program is designed for the VEX robots equipped with a optional LCD and with the
// file system enabled.
//
// The file system enables multiple user programs to be stored on one Vex. Upon startup and
// termination of a program, the default "primary" user program is started. This application
// is an implementation of the primary program and provides a chooser function to select any
// of the other user programs on the VEX for execution.
//
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma defaultFile   // Program will be "default" file started when VEX powers up

int nCurrentFileIndex;

//const int kNumbOfFiles = 16;


bool bSelectNextProgram(int nDirection)
{
  //
  // Increment (or decrement) to the next valid file slot. Skip over empty file slots.
  //
  int nAttempts = 0;

  for (nAttempts = 0; nAttempts < kNumbOfFiles; ++nAttempts)
  {
    nCurrentFileIndex += nDirection;
    if (nCurrentFileIndex < 1)
      nCurrentFileIndex = kNumbOfFiles - 1;
    if (nCurrentFileIndex >= kNumbOfFiles)
      nCurrentFileIndex = 1;
    if (bValidFile(nCurrentFileIndex))
      return true;
  }
  return false;
}


task main()
{
  nCurrentFileIndex = 0;
  bLCDBacklight = true;
	PlaySound(soundFastUpwardTones);
  if (!bSelectNextProgram(+1))
	{
		// File system is empty

	  displayLCDCenteredString(1, "No programs");
		while (true)
		{
		  PlaySound(soundBlip);
		  wait1Msec(500);
	  }
	}
	displayLCDCenteredString(1, "Select A Pgm");
	wait1Msec(1000);

	while (true)
  {
    if (nLCDButtons & kLeftButton)
    {
      bSelectNextProgram(-1);
      while (nLCDButtons != kNoButtons)
      {}
    }

    else if (nLCDButtons & kRightButton)
    {
      bSelectNextProgram(+1);
      while (nLCDButtons != kNoButtons)
      {}
    }

    else if (nLCDButtons & kRightButton)
    {
      bSelectNextProgram(+1);
    }


    else if (nLCDButtons & kCenterButton)
    {
      // Start execution of current selection

      while (nLCDButtons != kNoButtons)
      {}
      setProgramNumber(nCurrentFileIndex);
    }

    // Display current selection on LCD

    displayFileName(0, nCurrentFileIndex);
    displayLCDPos(1, 0);
    displayNextLCDString("\F7     Run      \F6");// F6 and F7 are left, right arrows

  }
  return;
}
