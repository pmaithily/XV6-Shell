#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void readinput(char *input);

int main(void)
{
  /* Insert your code here */
	int status;
	char *argv[] = {"grep", "main", NULL};
	char *ls[] = {"ls", NULL};
	char *wc[] = {"wc", NULL};
	int p1[2], p2[2];
	if(pipe(p1) == -1) {
		perror("pipe1");
		exit(-1);
	}
	int pid = fork();
	if(pid == -1) {
		perror("Fork");
		exit(-1);
	}
	if(pid == 0) {
		dup2(p1[1], 1);
		//perror("dup21");
		close(p1[0]);
		close(p1[1]);
		//perror("close1");
		int res = execvp(ls[0], ls);
		//perror("execvp1");
		exit(-1);
	}
	
	if(pipe(p2) == -1) {
		perror("Pipe2");
		exit(-1);
	}
	pid = fork();
	if(pid == -1) {
		perror("fork");
		exit(1);
	}
	if(pid == 0) {
		dup2(p1[0], 0);
		//perror("dup22");
		dup2(p2[1], 1);
		close(p1[0]);
		close(p1[1]);
		close(p2[0]);
		close(p2[1]);
		//perror("close2");
		execvp(argv[0], argv);
		//perror("execvp2");
		exit(-1);
	}
	//close(pipe1[0]);
	//close(pipe1[1]);	
	pid = fork();
	if(pid == -1) {
		perror("Fork");
		exit(-1);
	}
	if(pid == 0) {
		dup2(p2[0], 0);
		//perror("dup23");
		close(p2[0]);
		close(p1[0]);
		close(p1[1]);	
		close(p2[1]);
		//perror("close3");
		execvp(wc[0], wc);
		//perror("execvp3");	
		exit(-1);
	}
	
	else if(pid > 0) {
		int i = 0;
		close(p1[0]);
		close(p1[1]);
		close(p2[0]);
		close(p2[1]);
		while(i < 3) {
			wait(&status);
			i++;
		}
	}

	exit(0);
}

