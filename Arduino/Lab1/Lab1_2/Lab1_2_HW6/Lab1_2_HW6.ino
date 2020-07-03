unsigned char temp = 0x00;

void setup() {
  DDRA = 0x55;
}

void loop() {
  int i;
  PORTA = 0x01;
  for(i = 0; i < 4; i++){
    temp = PORTA << 2;
    delay(500);
    PORTA = 0x00;
    delay(500);
    PORTA = temp;
  }  
}
