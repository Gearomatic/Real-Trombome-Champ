/*
  
  Trombone Champ Controler V04.0

  For Pro Micro + Python

  Controls the mouse based on the results from a VL53L1X sensor mounted on a trombone.

  Hardware:
  - Arduino Pro Micro
  - VL53L1X TOF Sensor
  - MPXV7007 Pressure Sensor
  - Momentary Push Button
  - Toggle Switch
  

  The mouse movement is calibrated for a 1440X2560 monitor. You will need to modify the code to fit other screen sizes.
  See the "Serial.println((distance*4));" at the end, Modify that multiplier (default is 4) Try 2 for 1080 Height screens?

  WARNING: When you use the Mouse.move() command (in python in this case), the Arduino/python takes over your
  mouse! Make sure you have control before you use the mouse commands. Flipping the switch on pin 5 to ground should stop the flow of data to python and give you mouse control back
  this can be used to select levels or quit the python code.
  If all else fails, unplugging the usb cable should return mouse control to you as well.

  Created 2022 - 10 - 10
  Modified on 2022 - 10 - 24
  By Gearomatic
  
  
  Used code from:
  Reading distance from the laser based VL53L1X
  By: Nathan Seidle
  SparkFun Electronics
  
*/

#include <Mouse.h>
#include <Wire.h>
#include "SparkFun_VL53L1X.h" //library: http://librarymanager/All#SparkFun_VL53L1X
// grab librarys for use in this code. 
// Mouse.h is used to click the mouse (but not move it via the arduino, It is used on the python side to move the mouse)
// Wire.h is used for communiccation
// SparkFun_VL53L1X.h is used for communication to the sensor

SFEVL53L1X distanceSensor;
//define the distance sensor

// set pin for push button and switch:
const int pushButton = 4;
// set an input for the push button, Used to click the mouse to "play"
const int switchButton = 5;
// Set an input for the toggle switch. We pull this high internaly later so we dont need suport resistors. This is used to toggle the code on or off so we can regain mouse control
int switchState = LOW;
// assuming the switch is starting low. i dont think we need to do this but the code is working so why mess with it :)
int sensorPin = A3;    
// Set an input for the pressure sensor
int sensorValue = 0;  
// assume the sensor Value is 0 to start
int sensorPwr = 8;
// being lazy and powering the sensor from a pin
int sensorGnd = 9;
// being lazy and grounding the sensor from a pin


void setup(void)
{
{
pinMode(sensorPwr, OUTPUT);
pinMode(sensorGnd, OUTPUT);
digitalWrite(sensorPwr, HIGH);
digitalWrite(sensorGnd, LOW);
}
{
  
  Wire.begin();
// Start I2C(i think) comunications
  Serial.begin(9600);
// Start Serial comunications

if (distanceSensor.begin() != 0) 
// Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    // Stops the code if you cant read from the sensor    
    while (1)
      ;
  }
  Serial.println("Sensor online!");
  // Sends message to python code if the sensor is working. No real reason to other than to be able to confirm on the python side. Youll see a ton of numbers if the switch is in the right spot too.
}

  pinMode(pushButton, INPUT_PULLUP);
  pinMode(switchButton, INPUT_PULLUP);
  // initialize the buttons' inputs, both with pullups to avoid external resistors
    
  Mouse.begin();
  // initialize mouse control for clicking

  
  distanceSensor.setDistanceModeShort();
  // Set the Distance Mode to short range on the sensor. allows for faster reporting of times, and your arm isnt long enough for it to need the full sensor range
  // Originaly used a VL53L0X which has the right range and speed, but the reported values were very jumpy. Had consitered averaging them but this sensor is working better for me
  distanceSensor.setROI(4, 4, 199);
  // ROI setting lets us "beam steer" a little bit. Imagine theres a cone about 20 degrees coming out of the sensor, this lets us choose how much of that cone and which direction in the cone to use
  // In this case, we are saying to use the smallest area we can "4x4" centerd in the middle or just slightly don and tho the left of the middle of the range. See https://learn.sparkfun.com/tutorials/qwiic-distance-sensor-vl53l1x-hookup-guide/arduino-library-overview for more info.
  
  }

void loop(void)
{

  

  
  int pushState = digitalRead(pushButton);
  // Read/Store the state of the pushbutton
  int switchState = digitalRead(switchButton);
  // Read/Store the state of the Switch
  int sensorValue = analogRead(sensorPin);
  // Read/Store the value from the pressure sensor

if (switchState == LOW) {
    


  if (pushState == LOW or sensorValue >= 590) {
    // if the mouse is not pressed, press it:  )
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
      
    }
  }
  else {
       // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
     
    }
  }

  
  distanceSensor.startRanging(); 
  // Write configuration bytes to initiate measurement
  while (!distanceSensor.checkForDataReady())
  {
    delay(1);
   // not %100 sure what this one does, lol
  }
  
  int distance = distanceSensor.getDistance(); 
  // Get the result of the measurement from the sensor
  distanceSensor.clearInterrupt();
  distanceSensor.stopRanging();

  Serial.println(((distance*4)-300));
  //Print the distance in milimeters*2 to serial so the python code can grab it

 
}
}
