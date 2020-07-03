#include <FreeRTOS_AVR.h>

uint8_t MT_P = 10;
uint8_t MT_N = 9;

const int LeftSpeedKey = 20;
const int RightSpeedKey = 19;

const int LeftKey = 2;
const int StopKey = 3;
const int RightKey = 21;

QueueHandle_t xQueue;
QueueHandle_t xQueueSpeed;    //스피드 제어 queue

void LeftKeyControl(){
  uint16_t sendValue = 1;
  xQueueSendFromISR(xQueue, &sendValue, 0);
}

void StopKeyControl(){
  uint16_t sendValue = 2;
  xQueueSendFromISR(xQueue, &sendValue, 0);
}

void RightKeyControl(){
  uint16_t sendValue = 3;
  xQueueSendFromISR(xQueue, &sendValue, 0);
}

void LeftSpeedControl(){
  uint16_t sendValue = 4;
  xQueueSendFromISR(xQueueSpeed, &sendValue, 0);
}

void RightSpeedControl(){
  uint16_t sendValue = 5;
  xQueueSendFromISR(xQueueSpeed, &sendValue, 0);
}

void MotorTask(void* arg){
  uint16_t receiveValue = 0;
  uint16_t speedValue = 0;
  int speedLeft = 141;
  int speedRight = 141;
  while(1){
    if(xQueueReceive(xQueue, &receiveValue, 0)){
      if(receiveValue == 1){
        speedRight = 141;
        Serial.write("1");
        analogWrite(MT_P, 0);
        analogWrite(MT_N, speedLeft);
      }
      else if(receiveValue == 2){
        Serial.write("2");
        speedLeft = 141;
        speedRight = 141;
        analogWrite(MT_P, 0);
        analogWrite(MT_N, 0);
      }
      else if(receiveValue == 3){
        speedLeft = 141;
        Serial.write("3");
        analogWrite(MT_P, speedRight);
        analogWrite(MT_N, 0);
      }
    }
    if(xQueueReceive(xQueueSpeed, &speedValue, 0)){//속도 제어 버튼 클릭시
      if(speedValue == 4){                  //왼쪽회전
        if(receiveValue == 1){              //왼쪽 회전 중 일때만 버튼 동작
          Serial.write("4");
          speedLeft += 38;
          if(speedLeft > 255){
            speedLeft = 179;
          }
          speedRight = 141;
          analogWrite(MT_N, speedLeft);
        }
      }else if (speedValue == 5){           //오른쪽 회전
        if(receiveValue == 3){              //오른쪽 회전 중 일때만 버튼 동작
          Serial.write("5");
          speedRight += 38;
          if(speedRight > 255){
            speedRight = 179;
          }
          speedLeft = 141;
          analogWrite(MT_P, speedRight);
        }
      }
    }   
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(MT_P, OUTPUT);
  pinMode(MT_N, OUTPUT);

  pinMode(LeftKey, INPUT);
  pinMode(StopKey, INPUT);
  pinMode(RightKey, INPUT);
  pinMode(LeftSpeedKey, INPUT);
  pinMode(RightSpeedKey, INPUT);

  Serial.begin(9600);

  attachInterrupt(0, LeftKeyControl, RISING);
  attachInterrupt(1, StopKeyControl, RISING);
  attachInterrupt(2, RightKeyControl, RISING);
  attachInterrupt(3, LeftSpeedControl, RISING);
  attachInterrupt(4, RightSpeedControl, RISING);
    
  xQueue = xQueueCreate(3, sizeof(uint16_t));
  xQueueSpeed = xQueueCreate(2, sizeof(int));
  if(xQueue != NULL){
    xTaskCreate(MotorTask, NULL, 200, NULL, 1, NULL);   
  } 
  vTaskStartScheduler();
}

void loop() {
}
