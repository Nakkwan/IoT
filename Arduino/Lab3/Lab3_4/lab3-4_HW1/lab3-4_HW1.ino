#include <FreeRTOS_AVR.h>

const int MT_P = 10;
const int MT_N = 9;

const int LeftKey = 2;
const int StopKey = 3;
const int RightKey = 21;

const int Key[3] = {2, 3, 21};

SemaphoreHandle_t Sem;

int SendValue = -1;

void Keypad1(){
  delay(50);
  SendValue = 0;
  xSemaphoreGive(Sem);
}
void Keypad2(){
  delay(50);
  SendValue = 1;
  xSemaphoreGive(Sem);
}
void Keypad3(){
  delay(50);
  SendValue = 2;
  xSemaphoreGive(Sem);
}

void MotorExecute(int mode){
  if(mode == 0){
    digitalWrite(MT_P, LOW);
    digitalWrite(MT_N, HIGH);
  }
  else if(mode == 1){
    digitalWrite(MT_P, LOW);
    digitalWrite(MT_N, LOW);
  }
  else if(mode == 2){
    digitalWrite(MT_P, HIGH);
    digitalWrite(MT_N, LOW);
  }
}

void MotorTask(void* arg){
  int i;
  int keypad;

  while(1){
    if(xSemaphoreTake(Sem, portMAX_DELAY)){
      keypad = SendValue;
      MotorExecute(keypad);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  int i;

  for(i = 0; i < 3; i++){
    pinMode(Key[i], INPUT);
  }
  pinMode(MT_P, OUTPUT);
  pinMode(MT_N, OUTPUT);
  attachInterrupt(0, Keypad1, RISING);
  attachInterrupt(1, Keypad2, RISING);
  attachInterrupt(2, Keypad3, RISING);

  Sem = xSemaphoreCreateBinary();

  xTaskCreate(MotorTask, NULL, 200, NULL, 1, NULL);
  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:

}
