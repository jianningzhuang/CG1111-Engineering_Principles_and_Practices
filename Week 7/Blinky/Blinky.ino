//Blinky
//Turns LED on for one second, then off for one second, repeatedly in a loop.


//setup function runs once when you press reset 
void setup() {
  pinMode(11, OUTPUT); //initialize digital pin 13 as output
  pinMode(2, INPUT);

}

void loop() {
  int buttonState = digitalRead(2);
  if (buttonState == HIGH){
    digitalWrite(11, HIGH); //LED turns on when HIGH (voltage level is HIGH)
    delay(1000); //wait for 1 second
    digitalWrite(11, LOW); //LED turns off by making voltage level LOW 
    delay(1000); //wait for 1 second
  }
}
