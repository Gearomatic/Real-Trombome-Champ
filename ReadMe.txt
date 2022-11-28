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
  See the "Serial.println((distance*2));" at the end, Modify that multiplier (default is 2) Try 1.3 for 1080 Height screens?

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
  