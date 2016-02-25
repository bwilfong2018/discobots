# Goals #

## Week 1: ##
  1. ~~Reimage Classmate~~
  1. ~~Reimage cRIO and redownload code to 2010 robot~~
  1. Sensor setup and output:
    * ~~Gyro~~
    * Accelerometer
    * Quadrature Encoder
    * Light Sensor
    * [Sonar Rangefinder](Sonars.md) (may move to week 2)
  1. Research Sensor algorithms and uses
  1. ~~Design Electronic Layout for Robot~~
    * ~~Paper layout design~~
    * ~~CAD layout of electronics~~
    * ~~Battery mount designed~~


## Week 2: ##
  1. control loop for gyro to drive strait ~~and hold orientation.~~
    * When driving the robot stays strait, when not moving, if twisted the robot will try to reorient back to it's original position)
    * Test on 2010 Robot
  1. ~~control loop for gyro turning to set degrees (90 degrees, 180 degrees, etc.)~~
    * Test on 2010 Robot
  1. ~~control loop for encoder-based velocity control~~
    * When velocity set to zero the robot would try to stay still by pushing back in any direction that it is pushed
    * All wheels should spin at the same rate
  1. Holonomic Drive
    * ~~Class structure for holonomic drive control~~
    * Able to tell the method an x vector, y vector, and a twist and have it calculate each wheels velocity
    * Able to tell the method a magnitude, a direction and a twist and have it calculate each wheels velocity
  1. Protobot
    * ~~Code written for VEX Cortex~~
    * Basic Line Following for 6 wheeled robot
    * Line Tracking Mount designed and built
    * Can drive and control lift
  1. Electronic Board created with parts mounted
    * ~~Battery mount created~~
    * Sensor Mounts created
      * Sonars Mounted
      * ~~Encoders Mounted on drive motors~~
      * ~~Gyro and Accelerometer Mounted~~
  1. Power Wires are routed and labeled on the board

## Week 3: ##
  1. Drive control
    * Have drive modes that limit top speed and increase sensitivity for fine drive movements
    * Test on 2010 Robot
  1. Lift control programmed
    * encoder mounted on lift motor
    * uses encoder to tell lift position
    * two limit switches for full up and full down
  1. Claw control programmed
  1. ~~Sonar Ranger Positioning~~
    * Able to tell the distance from each of the three sides of the robot
  1. Protobot
    * Able to track line and stop when line ends
    * Able to detect branch in the line and follow one of the branches
    * Programmed for the VEX microcontroller

## Week 4: ##
  1. ~~Mount cRIO on the new robot~~
  1. Driver Control
    * Testing the ability of the drive train to drive strait and be controlled easily
    * Tweak PID parameters and get everything working really tight
  1. Sonar Orienting
    * Robot is able to use two sonars on the front of the robot to make sure it is oriented strait to the wall

## Week 5: ##
  1. Automatically position itself in front of any peg and hang the tube
  1. Autonomously hang tube on top rung (Strait ahead)

## Week 6: ##
  1. Autonomously hang tube on top run from middle position
  1. Lots of Driver Practice