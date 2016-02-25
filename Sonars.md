# Use #
We will be using sonar sensors to detect the distance the robot is away form the driver station wall and away from the feeding lane wall.

This should allow to easily align the robot up to a scoring position on each peg.

# How they Work #

Ultrasonic Sonar sensors allow the robot to tell the distance away it is from an object. To accomplish this the sensors must send out an ultrasonic sound way that is then reflected off of objects and returned to the sensor. The sensor times how long the sound took to echo back to itself and uses that to calculate the distance of the object.


# Details #

I think we will need to use the Maxbotix sonars to be able to not read the floor at distances of 9ft and only 5ins from the ground. Scott at Maxbotix is releasing a paper tomorrow about performance close to a ground but he has confirmed that the 1240's should be able to perform the task that we need.

  * [MaxSonar-1240](http://www.maxbotix.com/MB1240__XL-MaxSonar-EZ4.html)
  * [sparkfun page for sonar](http://www.sparkfun.com/products/9495)
  * [Detecting the MINIBOT pole](http://www.maxbotix.com/uploads/Direction_and_Distance_to_a_pole.pdf)
  * [chain maxbotix sensors together](http://www.maxbotix.com/uploads/Chaining_Application_Notes__AN_Output_Commanded_Loop_.pdf)

# Error and Noise Correction #
### Causes of Incorrect range readings (with a properly installed and properly powered sensor) ###
<sup><a href='Sonars#Reference.md'>Reference 1</a><sup>

<b>Multiple Sensor Applications (Cross Talk)</b>
Ultrasonic Sensors output and receive sound information when taking a range reading.  If multiple sensors are operational in the same environment this may cause one sensor to receive information sent by another sensor.  To eliminate interference, we recommend running sensors in sequence.  Refer to the examples of the three recommended ways to chain the sensors together.<br>
<a href='http://www.maxbotix.com/uploads/Chaining_Application_Notes__AN_Output_Commanded_'>http://www.maxbotix.com/uploads/Chaining_Application_Notes__AN_Output_Commanded_</a>...<br>
<a href='http://www.maxbotix.com/uploads/Chaining_Application_Notes__AN_Output_Constantly'>http://www.maxbotix.com/uploads/Chaining_Application_Notes__AN_Output_Constantly</a>...<br>
<a href='http://www.maxbotix.com/uploads/Chaining_Application_Notes__AN_Output_Simultaneo'>http://www.maxbotix.com/uploads/Chaining_Application_Notes__AN_Output_Simultaneo</a>...<br>
<br>
<b>External acoustic noise</b>
External acoustic noise sources may cause false range readings, that make phantom objects appear (i.e. readings are too close).<br>
<br>
<b>Soft or angled targets</b>
Also soft targets or angled targets can be missed occasionally.  That is, there must be a return of sufficient amplitude for detection and if enough energy is not returned then the target is missed.  This missed target issue can be exacerbated up close, where the returning energy must be detected in the presence of very high energy ring-down, so soft targets, or off axis targets, may not be detected easily.  (We will set the sensor to optimize for this... but the rules of physics will still apply.)<br>
<br>
<b>Filtering in General</b>
For filtering, do not average.  Do not average.  Do not average.  (Did I say, do not average?)  We have a lot of internal filtering in our products and if you receive readings that you feel must be filtered, do not use averaging.  Instead, throwing out the incorrect range values will produce the best results.  Averaging valid and invalid readings together will provide incorrect data.<br>
<br>
<b>Filtering</b>
The filtering that works best, is either a Mode filter or a Median filter.  (Did I forget to say, "Do not average the readings"?)<br>
<br>
<b>The Median Filter</b>
The median filter would take the last group of readings and first sort them and then pull out the center reading.  Here one might take three or more readings (up to say about 11 for people sensing) and after sorting the readings in order of range, pull out and use only the middle (median) reading.  Fairly good filtering.<br>
<br>
<b>The Mode Filter</b>
The mode filter would take the largest group of the same readings out of a set of even larger readings.  Very robust filtering.<br>
Filtering for most applications, the Very Simple Mode Filter<br>
<br>
The simplest mode filter, is simple as this question, "Do the last two readings agree?" (with in a certain distance, and the certain distance depends upon how much variation one expects in the actual use.  Even so most use the logic of "are these readings exactly the same")?  If so, use the readings, otherwise throw away to oldest reading, and compare the next reading with the most current reading and do this again.  Obviously with very noisy data, one might have to sample a larger group of readings, and pull out the most common reading, but for most applications, this simple two reading filter works very well.<br>
<br>
<br>
Even so, for specific cases, one has to try and find out what works best.<br>
<br>
Please let us know if you have any further questions. I request that you email me any questions at scott@maxbotix.com.<br>
<a href='http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1288290319'>source</a>

<h4>Reference</h4>
<ol><li><a href='http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1288290319'>http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1288290319</a>