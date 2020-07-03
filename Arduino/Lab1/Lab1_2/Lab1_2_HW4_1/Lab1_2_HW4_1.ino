#define LED16 9

int LED[4] = {5, 6, 7, 8};

void setup() {
  // put your setup code here, to run once:
  int i;
  for(i = 0; i < 4; i++)
    pinMode(LED[i], OUTPUT);
  pinMode(LED16, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  for(i = 0; i < 4; i++){
    digitalWrite(LED[i], HIGH);
    delay(500);
    digitalWrite(LED[i], LOW);
    delay(500);
  }
  digitalWrite(LED16, HIGH);
  delay(1000);
  digitalWrite(LED16, LOW);
  delay(1000);
  
}
