#include <wiringPi.h>
const int LedRed[8] = {4, 17, 18, 27, 22, 23, 24, 25};
const int Keypad[3] = {6, 12, 13};
int lastkeypad = -1;

int KeypadRead(){
	int i, keypadnum = - 1;
	for(i = 0; i < 3; i++){
		if(!digitalRead(Keypad[i])){
			keypadnum = i; break;
		}
	}
	return keypadnum;
}

int main(){
	unsigned int deltime;
	int i, keypadnum = -1;
	if(wiringPiSetupGpio() == -1)
		return 1;
	for(i = 0; i < 8; i++){
		pinMode(LedRed[i], OUTPUT);
		digitalWrite(LedRed[i], LOW);
	}

	for(i = 0; i < 2; i++){
		pinMode(Keypad[i], INPUT);
	}
	i = 0;
	while(1){
		keypadnum = KeypadRead();
		if (keypadnum == 0 && lastkeypad != 0){
			lastkeypad = 0;
			i = 0;
			deltime = millis();
		} else if (keypadnum == -1 && lastkeypad == 0){
			for(int j = 0; j < 8; j++){
				if(j == i){
					digitalWrite(LedRed[j], HIGH);
				} else {
					digitalWrite(LedRed[j], LOW);
				}
			}
			if(millis() - deltime > 500){
				i = (i + 1) % 8;
				deltime = millis();
			}
		} else if (keypadnum == 1 && lastkeypad != 1){
			lastkeypad = 1;
			i = 7;
			deltime = millis();
		} else if (keypadnum == -1 && lastkeypad == 1){
			for(int j = 0; j < 8; j++){
				if(j == i){
					digitalWrite(LedRed[j], HIGH);
				} else {
					digitalWrite(LedRed[j], LOW);
				}
			}
			if(millis() - deltime > 500){
				i = i - 1;
				if(i < 0) i = 7;
				deltime = millis();
			}
		} else if (keypadnum == 2 && lastkeypad != 2){
			lastkeypad = 2;
		} else if (keypadnum == -1 && lastkeypad == 2){
			for(i = 0; i < 8; i++){
				digitalWrite(LedRed[i], LOW);
			}
		}
	}
	return 0;
}
