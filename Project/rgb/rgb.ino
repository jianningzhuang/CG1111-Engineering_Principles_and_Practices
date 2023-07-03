#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMCore.h>
#define RGBWAIT 100
#define LDRWAIT 10
MeLightSensor lightsensor(6);
MeRGBLed led1(7,2);
//MeRGBLed led2();
//float colourArray[] = {0,0,0};
float whiteArray[] = {0,0,0};
float blackArray[] = {0,0,0};
float greyDiff[] = {0,0,0};
float rgbArr[3][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}};
                      
void setup() {
  char colourStr[3][6] = {"Red", "Green", "Blue"};
  int currval;
  Serial.begin(9600);
  set_balance();
  for(int c = 0; c < 3; c++){
    Serial.println(colourStr[c]);
    led1.setColor(rgbArr[c][0],rgbArr[c][1],rgbArr[c][2]);
    led1.show();
    for(int i=0; i < 50; i++){
      currval = (lightsensor.read()-blackArray[c])/(greyDiff[c])*255;
      printColor(currval);
    }
    led1.setColor(0,0,0);
    led1.show();
  }
   Serial.println("Experiment Completed.");
}

void loop() {
  // put your main code here, to run repeatedly:

}

int getAvgReading(int times){      
//find the average reading for the requested number of times of scanning LDR
  int reading;
  int total =0;
//take the reading as many times as requested and add them up
  for(int i = 0;i < times;i++){
     reading = lightsensor.read();
     total = reading + total;
     delay(LDRWAIT);
  }
  return total/times;
}

void set_balance(){
  led1.setColor(0, 0, 0);//  
  Serial.println("Put White Sample For Calibration ...");
  delay(5000);    //delay for five seconds for getting sample ready
  // scan white
  for(int i = 0; i < 3; i++){
    led1.setColor(rgbArr[i][0],rgbArr[i][1],rgbArr[i][2]);
    led1.show();
    delay(RGBWAIT);
    whiteArray[i] = getAvgReading(5);
    led1.setColor(0,0,0);
    led1.show();
    delay(RGBWAIT);
  }
  // scan black
  Serial.println("Put Black Sample For Calibration ...");
  delay(5000); 
  for(int i = 0; i < 3; i++){
    led1.setColor(rgbArr[i][0],rgbArr[i][1],rgbArr[i][2]);
    led1.show();
    delay(RGBWAIT);
    blackArray[i] = getAvgReading(5);
    led1.setColor(0,0,0);
    led1.show();
    delay(RGBWAIT);
    greyDiff[i] = whiteArray[i] - blackArray[i];
  }
  Serial.println("Put Colour Sample");
  //Pause 5 seconds to get the colorful paper
  delay(5000);
}

void printColor(int reading){
  Serial.print(millis());
  Serial.print(",");
  Serial.println(reading);
}
