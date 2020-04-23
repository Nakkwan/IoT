#include <wiringPi.h>
const int LedRed[8] = {4, 17, 18, 27, 22, 23, 24, 25};
const int Keypad[8] = {16, 13, 12, 6, 21, 26, 20, 19};
int buttonState[8];
int ledState[8] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int lastButtonState[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
unsigned int lastDebounceTime[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int debounceDelay = 50;

void debounce(int key, int j){
	if(key != lastButtonState[j]){
		lastDebounceTime[j] = millis();
	}
	if(millis() - lastDebounceTime[j] > debounceDelay){
		if(key != buttonState[j]){
			buttonState[j] = key;
			if(buttonState[j] == HIGH){
				ledState[j] = !ledState[j];
			}
		}
	}
	digitalWrite(LedRed[j], ledState[j]);
}


int main(){
	int i;
	int reading[8];
	if(wiringPiSetupGpio() == -1)
		return 1;
	for(i = 0; i < 8; i++){
		pinMode(LedRed[i], OUTPUT);
		digitalWrite(LedRed[i], ledState[i]);
	}

	for(i = 0; i < 8; i++){
		pinMode(Keypad[i], INPUT);
	}

	while(1){
		for(i = 0; i < 8; i++){
		reading[i] = digitalRead(Keypad[i]);
		debounce(reading[i], i);
		lastButtonState[i] = reading[i];
		}
	}

	return 0;
}
