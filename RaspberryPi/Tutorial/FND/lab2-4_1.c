#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

//for select pin to use
const int FndSelectPin[6] = {4, 17, 18, 27, 22, 23};

//pin connect with led
const int FndPin[8] = {6, 12, 13, 16, 19, 20, 26, 21};

//number of display in fnd
const int FndFont[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 
				0x6D, 0x7D, 0x27, 0x7F, 0x67};

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

void FndDisplay(int position, int num){
	int i, j;
	int flag = 0;
	int shift = 0x01;

	for(i=0;i<8;i++){
		//decide corresponding fnd led is high, low about num
		flag = (FndFont[num] & shift);
		digitalWrite(FndPin[i], flag);
		shift <<= 1;
	}

	//appear num at fnd module of position
	digitalWrite(FndSelectPin[position], LOW);
}

int main(int argc, char** argv){
	if(argc != 3){
		printf("Usage: %s [position] [number]", argv[0]);
		exit(-1);
	}

	init();

	FndDisplay(atoi(argv[1]), atoi(argv[2]));

	return 0;
}
