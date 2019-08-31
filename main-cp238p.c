#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  /* Insert your code here */
	char buf[1024];
	int src, dst;
	if(argc < 3 || argc > 3)
		return -1;
	else {
		src = open(argv[1], O_RDONLY);
		dst = open(argv[2], O_WRONLY | O_CREAT | S_IWUSR, 0644);
		if(src == -1 || dst == -1){
			printf("couln't open either of the two files\n");
			return -1;
		}	
		ssize_t count;
		while((count = read(src, buf, sizeof(buf))) != '\0') {
			write(dst, buf, count);
		}
		if(close(src) == -1 || close(dst) == -1) {
			printf("couldn't close either of the two files\n");
			return -1;
		}
	}
	exit(0);
}

