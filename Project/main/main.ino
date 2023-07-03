#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMCore.h>
#include <stdbool.h>

//Instantiate the LED, Buzzer and Motors
MeRGBLed led1(7,2);
MeDCMotor MotorL(M1);
MeDCMotor MotorR(M2);
MeLineFollower LineSensor(2);
MeLightSensor lightsensor(6);
MeUltrasonicSensor ultrasensor(3);
float colourArray[] = {0,0,0};
float whiteArray[] = {0,0,0};
float blackArray[] = {0,0,0};
float greyDiff[] = {0,0,0};
uint8_t rgbArr[3][3]={255,0,0,
                      0,255,0,
                      0,0,255};

                      
//Instantiate the line sensor, light sensor, IR sensor
MeLineFollower lineFinder(PORT_2);
MePort IRinput(PORT_3);
MeLightSensor lightSensor(PORT_6);

//Port 4 of mCore
#define IR1 A0  // Left
#define IR2 A1  // Right

//Port 2 of mCore Digital
#define TRIGGER 9 // OUTPUT
#define ECHO 10 // INPUT
#define TIMEOUT 30000
#define response 100
int moveSpeed = 100;
int minSpeed = 48;

int colorsensor(){
  led1.setColor(0,0,0);
  led1.show();
  int val[3];
  for(int c = 0; c < 3; c++){
    led1.setColor(rgbArr[c][0],rgbArr[c][1],rgbArr[c][2]);
    led1.show();
    delay(response);
    for(int i = 0; i < 5; i++){
      val[c] += lightsensor.read();
    }
    val[c] = val[c]/5;
    
  }
}

bool linedetect(){
  int sensorstate1 = LineSensor.readSensor1();
  int sensorstate2 = LineSensor.readSensor2();
  if(sensorstate1){
    return true;
  }
  return false;
}

void Forward() 
{
    MotorL.run(-moveSpeed);
    MotorR.run(moveSpeed);
}

void Backward()
{
  MotorL.run(moveSpeed); 
  MotorR.run(-moveSpeed);
}

void TurnLeft()
{
  MotorL.run(moveSpeed*0.8);
  MotorR.run(moveSpeed*0.8);
}

void TurnRight()
{
  MotorL.run(-moveSpeed*0.8);
  MotorR.run(-moveSpeed*0.8);
}

void TurnLeft2()
{
  MotorL.run(-moveSpeed/5);
  MotorR.run(moveSpeed);
}

void TurnRight2()
{
  MotorL.run(-moveSpeed);
  MotorR.run(moveSpeed/5);
}

void BackwardAndTurnLeft()
{
  MotorL.run(moveSpeed/3 ); 
  MotorR.run(-moveSpeed);
}

void BackwardAndTurnRight()
{
  MotorL.run(moveSpeed); 
  MotorR.run(-moveSpeed/3);
}

void Stop()
{
  MotorL.run(0);
  MotorR.run(0);
}
void setup() {
  pinMode(TRIGGER, OUTPUT); 
  digitalWrite(TRIGGER, LOW); 
  pinMode(ECHO, INPUT); 
  LineSensor.readSensors();
  Serial.begin(9600);
}

void loop() {
  //ULTRASONIC SENSOR FRONT
  digitalWrite(TRIGGER, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIGGER, LOW); 
  delayMicroseconds(10); 
  int sensorstate = LineSensor.readSensors();
  int distance = ultrasensor.distanceCm();
  int duration = pulseIn(ECHO, HIGH, TIMEOUT);
  //Serial.println(distance);
  
  
  //IR SENSORS SIDE
  int left = analogRead(IR1);
  int right = analogRead(IR2);
  
  
  if (sensorstate < 3 || distance <= 7){
    Stop();
    Serial.println("BLack");
  }
  else{
    Forward();
    if (left < 800){ //around 3 cm away from wall?
      Serial.println(left);
      Serial.println("Turn right");
      TurnRight();
      delay(70);
      Stop();
    }

    if (right < 800){ //around 3 cm away from wall?
      Serial.println(right);
      Serial.println("Turn left");
      TurnLeft();
      delay(70);
      Stop();
    }
  }
}
