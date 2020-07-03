#include <MsTimer2.h>

int ButtonOff = 2;
int ButtonOn = 3;
int Led = 7;
int led[2] = {5,6};

void LedControl(){
  static int counter =0;
  static byte output = HIGH;
  
  digitalWrite(led[counter++], output); 
  if (counter > 1){ 
    counter = 0; 
    output = ! output; 
  }
}


void ButtonLedControlOn(){
  byte output = HIGH;

  digitalWrite(Led, output);
}

void ButtonLedControlOff(){
  byte output = LOW;

  digitalWrite(Led, output);
}

void setup() {
  int i;
  pinMode(ButtonOn, INPUT);
  pinMode(ButtonOff, INPUT);
  pinMode(Led, OUTPUT);
  
  for(i=0; i<2; i++)
    pinMode(led[i],OUTPUT);

  MsTimer2::set(500, LedControl);
  MsTimer2::start();

  attachInterrupt(1, ButtonLedControlOn, FALLING);
  attachInterrupt(0, ButtonLedControlOff, RISING);
}

void loop() {

}
