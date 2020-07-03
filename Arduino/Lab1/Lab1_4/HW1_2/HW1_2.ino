enum{REST=0, DO=262, RE= 294, MI=330, FA=349, SOL=392, LA=440, SHI=494, DO2=523};

#define BUZZER 5

int Frequency[] = {DO, RE, MI, FA ,SOL, LA, SHI, DO2};
int Delay1[] = {500, 250, 250, 500, 500, 500, 250, 250, 500, 500};
int Delay2[] = {250, 250, 500, 250, 250, 500, 500, 500, 1000};
int Delay3[] = {500, 500, 500, 500, 500, 500, 1000};
int Delay4[] = {500, 500, 500, 500, 250, 250, 250, 250, 1000};
int music1[] = {0, 0, 0, 0, 0, 2, 4, 4, 2, 0};
int music2[] = {4, 4, 2, 4, 4, 2, 0, 0, 0};
int music3[] = {4, 4, 2, 0, 4, 4, 4};
int music4[] = {4, 4, 2, 0, 4, 4, 4, 5, 4};
int music5[] = {7, 4, 7, 4, 2, 1, 0};

/*
@pre: Set array for frequency and delay
@post: Sounds corresponding to the array
@param: array for frequency, delay, size of array
*/
void musicplay(int* mus, int* del, int num){
  int i;
  for(i = 0; i < num; i++){
    tone(BUZZER, Frequency[mus[i]], del[i]);
    delay(del[i]);
    delay(20);
  }
}

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  musicplay(music1, Delay1, 10);
  musicplay(music2, Delay2, 9);
  musicplay(music3, Delay3, 7);
  musicplay(music3, Delay3, 7);
  musicplay(music4, Delay4, 9);
  musicplay(music5, Delay3, 7);
}
