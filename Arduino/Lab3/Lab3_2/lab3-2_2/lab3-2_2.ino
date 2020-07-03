 #include <FreeRTOS_AVR.h>

#define MS2TICKS(ms)(ms/portTICK_PERIOD_MS)

#define LED1 5
#define LED2 6
#define LED3 7
#define LED4 8

int SendValue = -1;

SemaphoreHandle_t Sem;

void Task1(){
  xSemaphoreTake(Sem, portMAX_DELAY);
  SendValue = 1;
  delay(random(1000, 2000));
  xSemaphoreGive(Sem);
  vTaskDelay(MS2TICKS(random(1000, 2000)));
}

void Task2(){
  xSemaphoreTake(Sem, portMAX_DELAY);
  SendValue = 2;
  delay(random(1000, 2000));
  xSemaphoreGive(Sem);
  vTaskDelay(MS2TICKS(random(1000, 2000)));
}

void Task3(){
  xSemaphoreTake(Sem, portMAX_DELAY);
  SendValue = 3;
  delay(random(1000, 2000));
  xSemaphoreGive(Sem);
  vTaskDelay(MS2TICKS(random(1000, 2000)));
}

void Task4(){
  xSemaphoreTake(Sem, portMAX_DELAY);
  SendValue = 4;
  delay(random(1000, 2000));
  xSemaphoreGive(Sem);
  vTaskDelay(MS2TICKS(random(1000, 2000)));
}

void LedTask(int* pParam){
  int led, turn, param = *pParam;
  if(param == 1){
    led = LED1;
    turn = HIGH;  
  }else{
    led = LED2;
    turn = LOW;  
  }
  while(1){
    digitalWrite(led, turn);
    vTaskDelay(MS2TICKS(500));
    turn = (turn == HIGH)?LOW:HIGH;
  }  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  Sem = xSemaphoreCreateBinary();
  xSemaphoreGive(Sem);

  xTaskCreate(LedTask, NULL, 200, &SendValue, 1, NULL);
  

  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:

}
