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
MeBuzzer Buzzer(8);

//PORT_4 of mCore
#define IR1 A0  // Left
#define IR2 A1  // Right

//Movement variables
int moveSpeed = 200;
int minSpeed = 48;

//Movement Functions
void Forward(){
  MotorL.run(-moveSpeed*1.09);
  MotorR.run(moveSpeed);
}

void Backward(){
  MotorL.run(moveSpeed); 
  MotorR.run(-moveSpeed);
}

void TurnLeft(){
  MotorL.run(moveSpeed);
  MotorR.run(moveSpeed);
}

void TurnRight(){
  MotorL.run(-moveSpeed);
  MotorR.run(-moveSpeed);
}

void Stop(){
  MotorL.run(0);
  MotorR.run(0);
}

//Colour Arrays
float colourArray[] = {0,0,0};
float whiteArray[] = {420,325,400};
float blackArray[] = {30,30,30};
float greyDiff[] = {390,295,370}; 
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
  if (colourArray[0] > 140 && colourArray[1] < 70 && colourArray[2] < 70){
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
  else{
    return 6;
  }
}

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

void celebrate(){
  int tempo = 250;
  int melody[] = {
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  };
  int notes = sizeof(melody)/sizeof(melody[0]) / 2;
  int wholenote = (60000*4)/tempo;
  int divider = 0;
  int noteDuration = 0;
  for (int thisNote = 0; thisNote < notes*2; thisNote = thisNote + 2){
    divider = melody[thisNote + 1];
    if (divider > 0){
      noteDuration = (wholenote)/ divider;
    }
    else if (divider < 0){
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }
    Buzzer.tone(8, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    Buzzer.noTone();
  }
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensor_state = LineSensor.readSensors();
  int front_distance = UltrasonicSensor.distanceCm();
  int left_distance = analogRead(IR1);
  int right_distance = analogRead(IR2);
  Serial.println("right reading");
  Serial.println(analogRead(IR2));
  Serial.println("left reading");
  Serial.println(analogRead(IR1));
  if (sensor_state < 3 || front_distance <= 7){
    Stop();
    int cmd = detect_colour();
    if (cmd == 0){
      TurnLeft();
      delay(300);
      Stop();
      delay(500);
    }
    else if (cmd == 1){
      TurnRight();
      delay(300);
      Stop();
      delay(500);
    }
    else if (cmd == 2){ // light blue
      TurnRight();
      delay(300);
      Stop();
      delay(500);
      if(UltrasonicSensor.distanceCm() <= 35) {
        while(1) {
          if (UltrasonicSensor.distanceCm() < 9) {
            Stop();
            break;
          } else {
            Forward();
          }
         }
        } else {
        Forward();
        delay(700);
      }
      Stop();
      delay(500);
      TurnRight();
      delay(300);
      Stop();
      delay(500);
    }
    else if (cmd == 3){ // yellow
      Stop();
      delay(300);
      Serial.println(analogRead(IR2));
      if (analogRead(IR2) > 750){
        TurnRight();
        delay(300);
        Stop();
        delay(500);
        TurnRight();
        delay(300);
        Stop();
        delay(500);
      }
      else if (analogRead(IR1) > 610){
        TurnLeft();
        delay(300);
        Stop();
        delay(500);
        TurnLeft();
        delay(300);
        Stop();
        delay(500);
      }
      else{
        TurnRight();
        delay(300);
        Stop();
        delay(500);
        TurnRight();
        delay(300);
        Stop();
        delay(500);
      }
    }
    else if (cmd == 4){ // 
      TurnLeft();
      delay(300);
      Stop();
      delay(500);
      if(UltrasonicSensor.distanceCm() <= 35) {
        while(1) {
          if (UltrasonicSensor.distanceCm() < 9) {
            Stop();
            break;
          } else {
            Forward();
          }
         }
        } else {
        Forward();
        delay(700);
      }
      Stop();
      delay(500);
      TurnLeft();
      delay(300);
      Stop();
      delay(500);
    }
    else if (cmd == 5){
      Stop();
      celebrate();
      delay(5000);
    }
    else if (cmd == 6){
      Stop();
      delay(500);
    }
  }
  else{
    Forward();
    if (left_distance < 590){ //around 3 cm away from wall?
      Serial.println(left_distance);
      Serial.println("Turn right");
      TurnRight();
      delay(15);
      //Stop();
    }
    if (right_distance < 600){ //around 3 cm away from wall?
      Serial.println(right_distance);
      Serial.println("Turn left");
      TurnLeft();
      delay(15);
      //Stop();
    }
  }
}
