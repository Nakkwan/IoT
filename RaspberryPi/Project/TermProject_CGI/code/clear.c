#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(){
	printf("Content-type:text/html\n\n");
	printf("<html>\n<head>\n<title>CLEAR</title>\n<head>\n");
	printf("<body>\n<p>CLEAR TIME</p>\n");
	
	int fd;

	int buf = 2;

	if((fd = open("/tmp/FNDfifo", O_WRONLY))<0){
		printf("Stop:FIFO open Error\n");
		exit(1);
	}

	write(fd, &buf, sizeof(int));
	close(fd);

	printf("</body>\n</html>");

	return 0;
}
