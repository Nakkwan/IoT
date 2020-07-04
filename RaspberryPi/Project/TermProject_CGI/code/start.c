#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(){
	printf("Content-type:text/html\n\n");
	printf("<html>\n<head>\n<title>Start Stop Watch</title>\n</head>\n");
	printf("<body>\n<p>Start</p>\n");

	int fd1, fd2;

	int buf = 0;

	int pid;

	pid = fork();
	if(pid > 0){
		if((fd1 = open("/tmp/FNDfifo", O_WRONLY)) == -1){
			perror("Start: FIFO open Error\n");
			exit(1);
		}
		write(fd1, &buf, sizeof(int));
		close(fd1);
	}else{
		//if((fd2 = open("/home/pi/FNDprocess", O_EXEC)) <  0){
		//	printf("Start: Execute Error\n");
		//	exit(1);
		//}
		execl("/home/pi/FNDprocess", NULL);
	}

	printf("</body>\n</html>");
	return 0;
}
