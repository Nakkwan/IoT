#define BUZZER 5

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  tone(BUZZER, 262);  //도
  delay(500);
  
  tone(BUZZER, 294);  //레
  tone(BUZZER, 330);  //미
  delay(500);
  noTone(BUZZER);
  delay(500);

  tone(BUZZER, 349);  //파
  delay(500);
  
  tone(BUZZER, 392, 500); //솔
  delay(500);

  tone(BUZZER, 440, 500); //라
  delay(1000);
  
  tone(BUZZER, 494, 500); //시
  delay(500);
  
  tone(BUZZER, 523, 500); //도
  delay(500);
}
