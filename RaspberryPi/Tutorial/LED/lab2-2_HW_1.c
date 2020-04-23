#include <wiringPi.h>

#define LED_OFF 0
#define LED_ON 1
#define LED_ODD 2
#define LED_EVEN 3

const int LedOdd[8] = {4, 18, 22, 24, 6, 13, 19, 26};
const int LedEven[8] = {17, 27, 23, 25, 12, 16, 20, 21};

void LEDControl(int numtype){
	int i;
	if(numtype == LED_ODD){
		for(i = 0; i < 8; i++){
			digitalWrite(LedOdd[i], LED_ON);
			digitalWrite(LedEven[i], LED_OFF);
		}
		delay(500);
		for(i = 0; i < 8; i++){
			digitalWrite(LedOdd[i], LED_OFF);
		}
	}
	else if (numtype == LED_EVEN){
		for(i=0;i<8;i++){
			digitalWrite(LedOdd[i], LED_OFF);
			digitalWrite(LedEven[i], LED_ON);
		}
		delay(500);
		for(i = 0; i < 8; i++){
			digitalWrite(LedEven[i], LED_OFF);
		}
	}
}

int main(void){
	int i;
	if(wiringPiSetupGpio()==-1)
		return 1;
	for(i=0;i<8;i++){
		pinMode(LedOdd[i], OUTPUT);
		pinMode(LedEven[i], OUTPUT);

		digitalWrite(LedOdd[i], LED_OFF);
		digitalWrite(LedEven[i], LED_OFF);
	}

	while(1){
		LEDControl(LED_ODD);
		delay(500);
		LEDControl(LED_EVEN);
		delay(500);
	}

	return 0;
}
