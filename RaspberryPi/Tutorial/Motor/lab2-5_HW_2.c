#include <wiringPi.h>
#include <softPwm.h>

#define LED_PIN 4
#define LED_UP 1
#define LED_DOWN 2

void LedControl(int mode){
	int i,j;
	if(mode == LED_UP){
		for(i = 0; i < 129; i++){
			softPwmWrite(LED_PIN, i);
			delay(20);
		}
	} else if(mode == LED_DOWN){
		for(j = 128; j >= 0; j--){
			softPwmWrite(LED_PIN, j);
			delay(20);
		}
	}
}

int main(void){
	int i;
	if(wiringPiSetupGpio() == -1){
		return 1;
	}
	
	pinMode(LED_PIN, OUTPUT);

	softPwmCreate(LED_PIN, 0, 128);

	while(1){
		LedControl(LED_UP);
		delay(250);
		LedControl(LED_DOWN);
		delay(250);
	}
	return 0;
}
