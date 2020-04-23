#include <wiringPi.h>

#define LED_ON 1
#define LED_OFF 0

const int Led[16] = {
	4, 17, 18, 27, 22, 23, 24, 25,
	6, 12, 13, 16, 19, 20, 26, 21
};

void LEDControl(int pinnum){
	int i;
	for(i=0;i <16;i++){
		digitalWrite(Led[i], LED_OFF);
	}
	digitalWrite(Led[pinnum], LED_ON);
	digitalWrite(Led[pinnum + 1], LED_ON);
}

int main(void){
	int i;
	int j = 0;
	if(wiringPiSetupGpio() == -1)
		return 1;

	for(i = 0; i < 16; i++){
		pinMode(Led[i], OUTPUT);
		digitalWrite(Led[i], LED_OFF);
	}

	while(1){
		LEDControl(j);
		j+=2;
		if(j > 15){
			j = j % 16;
		}
		delay(500);
	}
	return 0;
}
