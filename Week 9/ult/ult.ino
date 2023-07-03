#define TIMEOUT 30000
#define WAITING_TIME 1000

/* The ultrasonic sensor (HC- SR04) has 4 pins,Vcc,  Trigger, Echo and GND
 *  Vcc(Sensor)---> 5V (Arduino)
 *  Trigger ------> Arduino Pin 12
 *  Echo ---------> Arduino Pin 11
 *  GND (Sensor)--> GND (Arduino)
*/
#define TRIGGER 12
#define ECHO 11

long duration; 

//The following code is run once at the start of execution to setup the different peripherals

void setup() 
{ 
  pinMode(TRIGGER, OUTPUT); 
  digitalWrite(TRIGGER, LOW); 
  pinMode(ECHO, INPUT); 
  
  // Set up the serial Communication
  Serial.begin(9600); 
}
void loop() 
{ 
  //The following code is run repeatedly 
  digitalWrite(TRIGGER, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIGGER, LOW); 
  delayMicroseconds(10); 
  
  duration = pulseIn(ECHO, HIGH, TIMEOUT); 
  Serial.print("Duration: ");
  Serial.print(duration*340/20000); 
  Serial.println(" microseconds"); 
  
  delay(WAITING_TIME); 
}
