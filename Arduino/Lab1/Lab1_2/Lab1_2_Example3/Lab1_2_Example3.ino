#include <MsTimer2.h>

int Led[4] = {5, 6, 7, 8};

void LedControl(){
  static int counter = 0;
  static byte output = HIGH;

  digitalWrite(Led[counter++], output);
  if(counter > 3){
    counter = 0;
    output = !output;
    }
  }

void setup() {
  // put your setup code here, to run once:
  int i;
  for(i = 0; i < 4; i++)
    pinMode(Led[i], OUTPUT);
  pinMode(2, OUTPUT);
  MsTimer2::set(500, LedControl);
  MsTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);
}
