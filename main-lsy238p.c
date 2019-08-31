#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int
main(void)
{
  /* Insert your code here */
	int pid = fork();
	if(pid == -1)
		perror("fork");
	if(pid == 0) {
		close(1);
		int dst = open("y", O_WRONLY| O_CREAT, S_IRWXU| S_IRWXG| S_IRWXO);
		if(dst == -1){
			printf("file could not be opened\n");
		}	
		execlp("ls", "ls", (char *)NULL);
		perror("execlp");
	}
	else if(pid > 0) {
		wait(0);
	}
	exit(0);
}

