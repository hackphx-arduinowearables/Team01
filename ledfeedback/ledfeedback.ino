/*
 Input Pullup Serial
 
 This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a 
 digital input on pin 2 and prints the results to the serial monitor.
 
 The circuit: 
 * Momentary switch attached from pin 2 to ground 
 * Built-in LED on pin 13
 
 Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal 
 20K-ohm resistor is pulled to 5V. This configuration causes the input to 
 read HIGH when the switch is open, and LOW when it is closed. 
 
 created 14 March 2012
 by Scott Fitzgerald
 
 http://www.arduino.cc/en/Tutorial/InputPullupSerial
 
 This example code is in the public domain
 
 */

#define FINGER_RED A5
#define FINGER_YELLOW 15
#define FINGER_WHITE 14
#define FINGER_BLUE 16

#include <Wire.h>

#define PIN 16

int inputs[4] = {FINGER_RED, FINGER_WHITE, FINGER_BLUE, FINGER_YELLOW};
unsigned long last[4] = {0, 0, 0, 0};

#define OP 11

void setup(){
  //start serial connection
  Serial.begin(9600);
  
  pinMode(OP, OUTPUT);
  digitalWrite(OP, HIGH);
  delay(500);
  digitalWrite(OP, LOW);
  delay(500);
  digitalWrite(OP, HIGH);
  delay(500);
  digitalWrite(OP, LOW);
  delay(500);
  digitalWrite(OP, HIGH);
  delay(500);
  digitalWrite(OP, LOW);
  delay(500);
  
  //Serial.println("Ready?");
  //Serial.println(A5);
  
  Wire.begin();
  delay(200);
  
  Wire.beginTransmission(0x04);
  Wire.write(0x01);
  Wire.write(0x01);
  Wire.endTransmission();
  
  Wire.beginTransmission(0x04);
  Wire.write(0x06);
  Wire.write(2);
  Wire.write(1);
  Wire.write(1);
  Wire.endTransmission();
  
  //configure pin2 as an input and enable the internal pull-up resistor
  for (int i=0; i<4; i++) {
    //Serial.println("Setup");
    //Serial.println(i);
    //Serial.println(inputs[i]);
    pinMode(inputs[i], INPUT_PULLUP);
  }
  //delay(100000);

}

void loop(){
  //Serial.println("#loopin");
  digitalWrite(OP, HIGH);
  int i;
  
  //read the pushbutton value into a variable
  for (i=0; i<4; i++) {
    int sensorVal = digitalRead(inputs[i]);
    if (sensorVal == LOW) {
      //Serial.println("HIGH");
      //Serial.println(inputs[i]);
      //Serial.println(sensorVal);
      last[i] = millis();
    }
  }
  
  int data[5] = {0, 0, 0, 0, 0};
  long dur = 800;
  long per = dur/7;
  
  for (i=0; i<4; i++) {
    if (last[i] > millis() - dur) {
      int dist = floor((millis() - last[i])/per);
      
      //Serial.println("ON");
      //Serial.println(i);
      //Serial.println(dist);
      data[i] = 1 << dist;
    }
  }
  
  Wire.beginTransmission(0x04);
  
  Wire.write(0x03);
  
  for (i=0; i<5; i++) {
    Wire.write(data[i]);
  }
  
  Wire.endTransmission();
  
  delay(80);
}



