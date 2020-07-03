#include <FreeRTOS_AVR.h>

const int MT_P = 10;        //모터핀
const int MT_N = 9;         //모터핀

const int LeftKey = 2;      //왼쪽 회전 핀 (명시적 선언)
const int StopKey = 3;      //멈춤 핀 (명시적 선언)
const int RightKey = 21;    //오른쪽 회전 핀 (명시적 선언)

unsigned int in = 0;        //buffer에 in 할 data의 위치
unsigned int out = 0;       //buffer에 out 할 data의 위치
const int Buffer_Size = 8;
unsigned int qbuffer[Buffer_Size];

SemaphoreHandle_t mutex, empty, full, Sem;

int SendValue = -1;        //KeypadTask과 Keycontrol 사이

void Keypad1(){            //왼쪽 회전
  delay(50);
  SendValue = 0;
  xSemaphoreGive(Sem);
}

void Keypad2(){            //멈춤
  delay(50);
  SendValue = 1;
  xSemaphoreGive(Sem);
}

void Keypad3(){            //오른쪽 회전
  delay(50);
  SendValue = 2;
  xSemaphoreGive(Sem);
}

void KeypadTask(){        //buffer의 producer
  while(1){
    if(xSemaphoreTake(Sem, portMAX_DELAY)){
      xSemaphoreTake(empty, portMAX_DELAY);   //넣을 자리가 있을 때
      xSemaphoreTake(mutex, portMAX_DELAY);   //공유 자원에 접근
      qbuffer[in] = SendValue;
      in = (in + 1) % Buffer_Size;
      xSemaphoreGive(mutex);                  //공유 자원 접근 해제
      xSemaphoreGive(full);                   //full signal
    }
  }
}

void MotorExecute(int mode){      //모터 실행
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

void MotorTask(void* arg){        //Buffer에서 out (consummer)
  int mode;

  while(1){
    xSemaphoreTake(full, portMAX_DELAY);  //받아올 데이터가 있을 때 
    xSemaphoreTake(mutex, portMAX_DELAY); //공유 자원에 접근
    mode = qbuffer[out];
    out = (out + 1) % Buffer_Size;
    xSemaphoreGive(mutex);                //공유 자원 접근 해제
    xSemaphoreGive(empty);                //empty signal
    
    MotorExecute(mode);                   //모터 실행
  }
}

void setup() {
  // put your setup code here, to run once:
  int i;
  
  for(i = 0; i < 8; i++){
    qbuffer[i] = -1;
  }

  pinMode(MT_P, OUTPUT);
  pinMode(MT_N, OUTPUT);

  attachInterrupt(0, Keypad1, RISING);
  attachInterrupt(1, Keypad2, RISING);
  attachInterrupt(2, Keypad3, RISING);

  Sem = xSemaphoreCreateBinary();
  mutex = xSemaphoreCreateBinary();
  xSemaphoreGive(mutex);      //기본값이 0이기 때문에 1로 만들어줌
  empty = xSemaphoreCreateCounting(Buffer_Size, Buffer_Size);
  full = xSemaphoreCreateCounting(Buffer_Size, 0);

  xTaskCreate(MotorTask, NULL, 200, NULL, 1, NULL);
  xTaskCreate(KeypadTask, NULL, 200, NULL, 2, NULL);
  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
}
