#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

//for select pin to use
const int FndSelectPin[6] = {4, 17, 18, 27, 22, 23};

//pin connect with led
const int FndPin[8] = {6, 12, 13, 16, 19, 20, 26, 21};

//number of display in fnd
const int FndFont[6] = {0x3F, 0x38, 0x38, 0x79, 0x76, 0x00};

void init(){
	int i;

	if(wiringPiSetupGpio() == -1){
		printf("wiringPiSetupGpio() error\n");
		exit(-1);
	}

	//set select pin output, and set off (default on is Low)
	for(i = 0; i < 6; i++){
		pinMode(FndSelectPin[i], OUTPUT);
		digitalWrite(FndSelectPin[i], HIGH);
	}

	//set Led pin Output, and set off initially
	for(i = 0; i < 8; i++){
		pinMode(FndPin[i], OUTPUT);
		digitalWrite(FndPin[i], LOW);
	}
}

void FndSelect(int position){
	int i;

	for(i = 0; i<6; i++){
		if(i == position){
			digitalWrite(FndSelectPin[i], LOW);
		} else {
			digitalWrite(FndSelectPin[i], HIGH);
		}
	}
}

void SetClear(){
	int i;
	for(i=0;i<6;i++){
		digitalWrite(FndSelectPin[i], HIGH);
	}
}

void FndDisplay(int position, int num){
	int i;
	int flag = 0;
	int shift = 0x01;
	for(i=0;i<8;i++){
		//decide corresponding fnd led is high, low about num
		flag = (FndFont[num] & shift);
		digitalWrite(FndPin[i], flag);
		shift <<= 1;
	}
	FndSelect(position);
}

int main(){
	int pos;
	int i = 0,j = 0;
	int data[6] = {0, 1, 2, 3, 4, 5};
	init();
	int time = millis();

	while(1)
	{
		for(pos = 0; pos < 6; pos++){
			j = pos - i;
			if(j<0) j += 6;
			FndDisplay(pos, data[j]);
			delay(1);
			if(millis() - time > 500){
				i++;
				if(i > 5){
					i = i % 6;
				}
				time = millis();
			}
		}
	}
	return 0;
}
