#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void sig_hander(int signo);
int main(int argc, char **atgv){
	int i=0;
	signal(SIGINT,SIG_IGN);
	while(1){
		printf("%d\n", i);
		i++;
		Sleep(2);
	}
	
	return 0;
}

void sig_handler(int signo){
	printf("SIGINT %d\n",SIGINT);
	kill(getpid(),SIGQUIT);
}
