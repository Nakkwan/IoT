#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

//for select pin to use
const int FndSelectPin[6] = {4, 17, 18, 27, 22, 23};

//pin connect with led
const int FndPin[8] = {6, 12, 13, 16, 19, 20, 26, 21};

//number of display in fnd
const int FndFont[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
							0x7D, 0x27, 0x7F, 0x67};

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

	if(position == 2){		//for check sec point
		digitalWrite(FndPin[7], HIGH);
	}
	FndSelect(position);
}

int main(){
	int pos;
	int i, j;
	int data[6][2] = {{0,0},{1,0},{2,0},{3,0},{4,0},{5,0}};
	init();
	int time = millis();

	while(1)
	{
		for(pos = 0; pos < 6; pos++){
			FndDisplay(data[pos][0], data[pos][1]);
			delay(1);
			if(millis() - time > 10){
				data[0][1]++;
				for(i=0;i<5;i++){
					//increase next cipher
					if(data[i][1] > 9){
						data[i][1] = 0;	
						data[i+1][1]++;
					} 
				}


				if(data[5][1] > 9) data[5][1] = 0;
				time = millis();
			}
		}
	}
	return 0;
}
