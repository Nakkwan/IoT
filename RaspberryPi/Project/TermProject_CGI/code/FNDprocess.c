#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
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

	int buf = -1;					//FIFO로 받을 BUFFER
	int fd;							//file descriptor
	
	int value = 0;					//BUFFER로 받은 값

	if(mkfifo("/tmp/FNDfifo", 0666) == -1){			//FIFO 생성
		perror("Create FiFo Error\n");
		exit(1);
	}
	
	if((fd = open("/tmp/FNDfifo", O_RDONLY))<0){	//FIFO Open
		printf("FiFo Open Error\n");
		exit(1);
	}
	

	while(1)
	{
		if(read(fd, &buf, sizeof(buf)) > 0){	//FNDfifo에서 값을 받고
			value = buf;						//해당값을 할당
		}

		if(value == 0){							//start일때
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
		}else if (value == 1){					//stop일때
			for(pos = 0; pos < 6; pos++){
				FndDisplay(data[pos][0], data[pos][1]);
				delay(1);
			}
		}else if (value == 2){					//clear일때
			for(pos = 0; pos < 6; pos++){
				data[pos][1] = 0;
				FndDisplay(data[pos][0], data[pos][1]);
				delay(1);
			}
		}
	}
	return 0;
}
