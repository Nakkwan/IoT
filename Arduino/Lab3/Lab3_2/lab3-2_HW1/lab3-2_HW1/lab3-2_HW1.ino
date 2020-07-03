#define LED 5
#define BUZZER 6
int i = 0;
enum {REST=0, DO=262, RE=294, MI=330, FA=349, SOL=392, LA=440, SHI=494, DO2=523};
int buttonState = HIGH;
int Frequency[] = {DO, RE, MI, REST, FA, SOL, LA, SHI, DO2};

unsigned long lastLedDebounceTime = 0;
unsigned long lastBuzzerDebounceTime = 0;
unsigned long ledDelay = 500;
unsigned long Delay[] = {500, 0, 500, 500, 500, 500, 1000, 0, 500};

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  tone(BUZZER, Frequency[0]);
}

void loop() {
  if(millis() - lastLedDebounceTime > ledDelay){
    lastLedDebounceTime = millis();
    buttonState = !buttonState;
  }
  if(millis() - lastBuzzerDebounceTime > Delay[i]){
    i++;
    lastBuzzerDebounceTime = millis();
    if(i == 9) i = 0;
    tone(BUZZER, Frequency[i]);
  }
  digitalWrite(LED, buttonState);
}
