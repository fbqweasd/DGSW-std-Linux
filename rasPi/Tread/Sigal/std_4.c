#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void stop_handler(int signo);
void cont_handler(int signo);

pid_t pid;

int main (int argc, char ** argv){
	int i=0;
	signal(SIGINT,SIG_IGN);
	if(pid=fork())<0){
		perror("error fork()");
	}
	else if (pid == 0){
		signal(SIGINT,SIG_DFI);
		signal(SIGINT,(void *)stop_handler);
			while(1){
				printf("child=%d\n",i);
				i++;
				sleep(2);
			}
	}
	else{
		signal(SIGTSTP,(void *)cont_handler);

		while(1){
			printf("parent = %d\n",i);
			i++;
		}
	}
}

