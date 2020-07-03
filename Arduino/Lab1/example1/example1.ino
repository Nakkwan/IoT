unsigned char temp = 0x00;

void setup() {
  // put your setup code here, to run once:
  DDRA = 0x55;
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  PORTA = 0b00000001;
  for(i = 0; i < 4; i++){
    temp = PORTA << 2;
    delay(500);
    PORTA = 0x00;
    delay(500);
    PORTA = temp;
  }  
}
