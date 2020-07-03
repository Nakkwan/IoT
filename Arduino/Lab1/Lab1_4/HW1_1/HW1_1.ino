enum{REST=0, DO=262, RE= 294, MI=330, FA=349, SOL=392, LA=440, SHI=494, DO2=523};

#define BUZZER 5

int Num1 = 7;
int Num2 = 5;
int Frequency[] = {DO, RE, MI, FA ,SOL, LA, SHI, DO2};
int Delay1[] = {500, 500, 500, 500, 500, 500, 1000};
int Delay2[] = {500, 500, 500, 500, 1000};
int music1[] = {4, 4, 5, 5, 4, 4, 2};
int music2[] = {4, 4, 2, 2, 1};
int music3[] = {4, 2, 1, 2, 0};

void musicplay(int* mus, int* del, int num){
  int i;
  for(i = 0; i < num; i++){
    tone(BUZZER, Frequency[mus[i]], del[i]);
    delay(del[i]);
    delay(20);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  musicplay(music1, Delay1, Num1);
  musicplay(music2, Delay2, Num2);
  delay(500);
  musicplay(music1, Delay1, Num1);
  musicplay(music3, Delay2, Num2);
  delay(500);
}
