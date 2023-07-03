#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMCore.h>

MeLightSensor LightSensor(PORT_6);
MeRGBLed LED(PORT_7);

//Colour Arrays
float colourArray[] = {0,0,0};
float whiteArray[] = {0,0,0};
float blackArray[] = {0,0,0};
float greyDiff[] = {0,0,0}; 
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
  if (colourArray[0] > 200 && colourArray[1] < 100 && colourArray[2] < 100){
    Serial.println("RED DETECTED!");
    return 0;
  }
  else if (colourArray[0] < 100 && colourArray[1] >200 && colourArray[2] < 100){
    Serial.println("GREEN DETECTED!");
    return 1;
  }
  else if (colourArray[0] < 100 && colourArray[1] < 100 && colourArray[2] > 200){
    Serial.println("BLUE DETECTED!");
    return 2;
  }
  else if (colourArray[0] > 200 && colourArray[1] > 200 && colourArray[2] < 100){
    Serial.println("YELLOW DETECTED!");
    return 3;
  }
  else if (colourArray[0] > 150 && colourArray[1] < 120 && colourArray[2] > 200){
    Serial.println("PURPLE DETECTED!");
    return 4;
  }
  else if (colourArray[0] < 50 && colourArray[1] < 50 && colourArray[2] < 50){
    Serial.println("BLACK DETECTED!");
    return 5;
  }
}

void setup() {
  Serial.begin(9600);
  set_balance();
  delay(5000); 
  detect_colour();
}

void loop() {

}
