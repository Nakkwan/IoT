#include <MsTimer2.h>

int ButtonOff = 9;
int ButtonOn = 8;
int Led16 = 7;
int Led[2] = {5,6};

int ledState = HIGH;
int ButtonState;
int lastButtonState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;


void LedControl(){
  static int counter =0;
  static byte output = HIGH;
  
  digitalWrite(Led[counter++], output); 
  if (counter > 1){ 
    counter = 0; 
    output = ! output; 
  }
}

void trig(int inButton, int state, int out){
  if(inButton != lastButtonState){
    lastDebounceTime = millis();
  }
  if(millis() - lastDebounceTime > debounceDelay){
    if(inButton != ButtonState){
      ButtonState = inButton;
      if(ButtonState == state){
        ButtonState = !state;
        ledState = out;
        digitalWrite(Led16, out);
      }
    }
  }
  lastButtonState = inButton;
}

void setup() {
  int i;
  pinMode(ButtonOn, INPUT);
  pinMode(ButtonOff, INPUT);
  pinMode(Led16, OUTPUT);
  for(i=0; i<2; i++)
    pinMode(Led[i],OUTPUT);

  MsTimer2::set(500, LedControl);
  MsTimer2::start();
}

void loop() {
  int readingOn = digitalRead(ButtonOn);
  int readingOff = digitalRead(ButtonOff);

  if(ledState == LOW){
    trig(readingOn, LOW, HIGH);
  }
  else {
    trig(readingOff, HIGH, LOW);
  }

}
