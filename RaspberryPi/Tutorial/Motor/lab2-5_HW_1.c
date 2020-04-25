#include <wiringPi.h>
#include <softPwm.h>

#define MOTOR_MT_N_PIN 17
#define MOTOR_MT_P_PIN 4

#define LEFT_ROTATE 1
#define RIGHT_ROTATE 2

void MotorStop(){
	softPwmWrite(MOTOR_MT_N_PIN, 0);
	softPwmWrite(MOTOR_MT_P_PIN, 0);
}
//control direction and speed of Motor
void MotorControl(int rotate, int speed){
	if(rotate == LEFT_ROTATE){
		digitalWrite(MOTOR_MT_P_PIN, LOW);
		softPwmWrite(MOTOR_MT_N_PIN, speed);
	} else if(rotate == RIGHT_ROTATE){
		digitalWrite(MOTOR_MT_N_PIN, LOW);
		softPwmWrite(MOTOR_MT_P_PIN, speed);
	}
}

int main(void){
	int i;
	int speed = 0;
	if(wiringPiSetupGpio() == -1){
		return 1;
	}

	pinMode(MOTOR_MT_N_PIN, OUTPUT);
	pinMode(MOTOR_MT_P_PIN, OUTPUT);

	softPwmCreate(MOTOR_MT_N_PIN, 0, 128);
	softPwmCreate(MOTOR_MT_P_PIN, 0, 128);

	while(1){
		for(i=0;i<4;i++){
			speed += 32;
			MotorControl(LEFT_ROTATE, speed);
			delay(2000);
			MotorStop();
			delay(2000);
		}	
		for(i=0;i<4;i++){
			MotorControl(RIGHT_ROTATE, speed);
			delay(2000);
			MotorStop();
			delay(2000);
			speed -= 32;
		}
		speed = 0;
	}
	return 0;
}
