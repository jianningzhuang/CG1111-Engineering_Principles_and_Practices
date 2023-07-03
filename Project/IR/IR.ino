#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMCore.h>

MeDCMotor MotorL(M1);
MeDCMotor MotorR(M2);

//Port 4 of mCore
#define IR1 A0  // Left
#define IR2 A1  // Right

//Port 2 of mCore Digital
#define TRIGGER 9 // OUTPUT
#define ECHO 10 // INPUT
#define TIMEOUT 30000


void setup() {
  pinMode(TRIGGER, OUTPUT); 
  digitalWrite(TRIGGER, LOW); 
  pinMode(ECHO, INPUT); 

}

void loop() {
  //ULTRASONIC SENSOR FRONT
  digitalWrite(TRIGGER, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIGGER, LOW); 
  delayMicroseconds(10); 
  
  int duration = pulseIn(ECHO, HIGH, TIMEOUT);
  if (duration < 200){  // around 4-5 cm?
     Serial.println("Close");
  }
  delay(100);

  //IR SENSORS SIDE
  int left = analogRead(IR1);
  int right = analogRead(IR2);
  if (left < 500){ //around 3 cm away from wall?
    Serial.println("turn right");
  }
  if (right < 500){ //around 3 cm away from wall?
    Serial.println("turn left");
  }

}
