int Led[4] = {5, 7, 6, 8};

void setup() {
  // put your setup code here, to run once:
  int i;
  for(i = 0; i < 4; i++)
    pinMode(Led[i], OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i, j;
  int del = 500;
  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      digitalWrite(Led[j], HIGH);
      delay(del);
      digitalWrite(Led[j], LOW);
      delay(del);
    }
    if(del == 2000)
      del = 500;
    else
      del += 500;
  }
}
