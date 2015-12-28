/*
 RC Drive to Light
 Reads two LDR's at the front of the vehicle. Once a threshold light
 level is exceeded, it steers towards the light source and drives
 forward. Below the threshold, the car stops and steers straight.
 
 Circuit:
 Team Associated XPS Micro ESC #29136
 - Battery Connector to Battery
 - Batt + Terminal to Arduino Vin
 
 Servo1 5V to Servo2 5V
 Servo1 GND to Servo2 GND
 Servo1 GND to Arduino GND
 Servo1 Signal to Arduino Pin 9
 Servo2 Signal to Arduino Pin 10
 
 5V through 100uF Cap to GND
 5V through 0.1uF Cap to GND
 
 LDR1: 5V through LDR to Pin A0 and through 10K resistor to ground.
 LDR2: 5V through LDR to Pin A1 and through 10K resistor to ground.
 */

#include <Servo.h>

Servo driveServo;  // create servo object to control a servo 
Servo steerServo;  // create servo object to control a servo 

int drivePos = 90;    // variable to store the servo position 
int steerPos = 90;    // variable to store the servo position 

int rtEyeValue = 0;
int lfEyeValue = 0;
int difference = 0;

int threshold = 650;  // todo: write a setup function that reads the LDR's for a while to determine a good threshold value before entering the main loop.

void setup() {
  Serial.begin(9600);
  steerServo.attach(9);  // attaches the servo on pin 9 to the servo object 
  driveServo.attach(10);  // attaches the servo on pin 10 to the servo object 
}

void loop() {
  rtEyeValue = analogRead(0);
  lfEyeValue = analogRead(1);
  Serial.print("rt = " );  
  Serial.print(rtEyeValue, DEC);
  Serial.print(", lf = ");
  Serial.print(lfEyeValue, DEC);

  if( rtEyeValue > threshold || lfEyeValue > threshold) //look for some light
  {
    difference = rtEyeValue - lfEyeValue;
    steerPos = map(difference, -300, 300, 45, 135);     // scale it to use it with the servo (value between 0 and 180) 
    steerServo.write(steerPos);
    driveServo.write(103);                              // you may need to tweak this value to get the speed you want
    Serial.print(", diff = ");
    Serial.print(difference, DEC);
    Serial.print(", steer = ");
    Serial.print(steerPos, DEC);

  }
  else{
    Serial.print(", just ambient");
    steerServo.write(90);
    driveServo.write(90);
  }
  Serial.println(" ");
}








