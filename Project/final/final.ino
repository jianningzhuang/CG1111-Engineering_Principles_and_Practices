#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMCore.h>

//Motors, LED, LineSensor, LightSensor, UltrasonicSensor
MeDCMotor MotorL(M1);
MeDCMotor MotorR(M2);
MeLineFollower LineSensor(PORT_2);
MeUltrasonicSensor UltrasonicSensor(PORT_3);
MeLightSensor LightSensor(PORT_6);
MeRGBLed LED(PORT_7);

//PORT_4 of mCore
#define IR1 A0  // Left
#define IR2 A1  // Right

//Movement variables
int moveSpeed = 100;
int minSpeed = 48;

//Movement Functions
void Forward(){
  MotorL.run(-moveSpeed);
  MotorR.run(moveSpeed);
}

void Backward(){
  MotorL.run(moveSpeed); 
  MotorR.run(-moveSpeed);
}

void TurnLeft(){
  MotorL.run(moveSpeed*0.8);
  MotorR.run(moveSpeed*0.8);
}

void TurnRight(){
  MotorL.run(-moveSpeed*0.8);
  MotorR.run(-moveSpeed*0.8);
}

void TurnLeft2(){
  MotorL.run(-moveSpeed/5);
  MotorR.run(moveSpeed);
}

void TurnRight2(){
  MotorL.run(-moveSpeed);
  MotorR.run(moveSpeed/5);
}

void BackwardAndTurnLeft(){
  MotorL.run(moveSpeed/3 ); 
  MotorR.run(-moveSpeed);
}

void BackwardAndTurnRight(){
  MotorL.run(moveSpeed); 
  MotorR.run(-moveSpeed/3);
}

void Stop(){
  MotorL.run(0);
  MotorR.run(0);
}

//Colour Arrays
float colourArray[] = {0,0,0};
float whiteArray[] = {500,375,440};
float blackArray[] = {30,30,30};
float greyDiff[] = {470,345,410}; 
float rgbArr[3][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}};

//DELAYS
#define RGBWAIT 100
#define LDRWAIT 10

int getAvgReading(int times){      
//find the average reading for the requested number of times of scanning LDR
  int reading;
  int total =0;
//take the reading as many times as requested and add them up
  for(int i = 0;i < times;i++){
     reading = LightSensor.read();
     total = reading + total;
     delay(LDRWAIT);
  }
  return total/times;
}

void set_balance(){
  LED.setColor(0, 0, 0);//  
  Serial.println("Put White Sample For Calibration ...");
  delay(5000);    //delay for five seconds for getting sample ready
  // scan white
  for(int i = 0; i < 3; i++){
    LED.setColor(rgbArr[i][0],rgbArr[i][1],rgbArr[i][2]);
    LED.show();
    delay(RGBWAIT);
    whiteArray[i] = getAvgReading(5);
    Serial.print("white :");
    Serial.println(whiteArray[i]);
    LED.setColor(0,0,0);
    LED.show();
    delay(RGBWAIT);
  }
  // scan black
  Serial.println("Put Black Sample For Calibration ...");
  delay(5000); 
  for(int i = 0; i < 3; i++){
    LED.setColor(rgbArr[i][0],rgbArr[i][1],rgbArr[i][2]);
    LED.show();
    delay(RGBWAIT);
    blackArray[i] = getAvgReading(5);
    Serial.print("black :");
    Serial.println(blackArray[i]);
    LED.setColor(0,0,0);
    LED.show();
    delay(RGBWAIT);
    greyDiff[i] = whiteArray[i] - blackArray[i];
  }
}

int detect_colour(){
  for(int i = 0; i < 3; i++){
    LED.setColor(rgbArr[i][0],rgbArr[i][1],rgbArr[i][2]);
    LED.show();
    for(int j=0; j < 20; j++){
      colourArray[i] = (LightSensor.read()-blackArray[i])/(greyDiff[i])*255;
      delay(10);
    }
    LED.setColor(0,0,0);
    LED.show();
    Serial.println(colourArray[i]);
  }
  if (colourArray[0] > 140 && colourArray[1] < 50 && colourArray[2] < 50){
    Serial.println("RED DETECTED!");
    return 0;
  }
  else if (colourArray[0] < 70 && colourArray[1] >100 && colourArray[2] < 70){
    Serial.println("GREEN DETECTED!");
    return 1;
  }
  else if (colourArray[0] > 200 && colourArray[1] > 200 && colourArray[2] > 200){
    return 6;
  }
  else if (colourArray[0] > 100 && colourArray[1] >150 && colourArray[2] > 150){
    Serial.println("BLUE DETECTED!");
    return 2;
  }
  else if (colourArray[0] > 200 && colourArray[1] > 130 && colourArray[2] < 100){
    Serial.println("YELLOW DETECTED!");
    return 3;
  }
  else if (colourArray[0] > 100 && colourArray[1] > 100 && colourArray[2] > 150){
    Serial.println("PURPLE DETECTED!");
    return 4;
  }
  else if (colourArray[0] < 50 && colourArray[1] < 50 && colourArray[2] < 50){
    Serial.println("BLACK DETECTED!");
    return 5;
  }
  
}



int gogogo = 0;

void setup() {
  Serial.begin(9600);
  set_balance();
  gogogo = 1;
}

void loop() {
  if (gogogo == 0){
    Stop();
  }
  int sensor_state = LineSensor.readSensors();
  int front_distance = UltrasonicSensor.distanceCm();
  int left_distance = analogRead(IR1);
  int right_distance = analogRead(IR2);
  if (sensor_state < 3 || front_distance <= 7){
    Stop();
    int cmd = detect_colour();
    if (cmd == 0){
      TurnLeft();
      delay(790);
      Stop();
    }
    else if (cmd == 1){
      TurnRight();
      delay(810);
      Stop();
    }
    else if (cmd == 2){
      TurnRight();
      delay(810);
      Stop();
      Forward();
      delay(1500);
      Stop();
      TurnRight();
      delay(810);
      Stop();
    }
    else if (cmd == 3){
      TurnRight();
      delay(1630);
      Stop();
    }
    else if (cmd == 4){
      TurnLeft();
      delay(790);
      Stop();
      Forward();
      delay(1500);
      Stop();
      TurnLeft();
      delay(790);
      Stop();
    }
    else if (cmd == 5){
      Stop();
      delay(5000);
    }
    else if (cmd == 6){
      Stop();
      delay(500);
    }
  }
  else{
    Forward();
    if (left_distance < 500){ //around 3 cm away from wall?
      Serial.println(left_distance);
      Serial.println("Turn right");
      TurnRight();
      delay(70);
      Stop();
    }
    if (right_distance < 500){ //around 3 cm away from wall?
      Serial.println(right_distance);
      Serial.println("Turn left");
      TurnLeft();
      delay(70);
      Stop();
    }
  }
}
