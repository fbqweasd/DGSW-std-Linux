#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/types.h>
int csock;
int csocks[10];
int cnum=0;
struct sockaddr_in client_addr;
#define TCP_PORT 5100
void *client_connection(void *arg){
	int n,csock,i,j;
	char buf[BUFSIZ];
	csock=*((int*)arg);
	while(1){
	if((n=read(csock,buf,BUFSIZ))<=0){
		perror("read");
		pthread_exit(0);
		return (void*)NULL;	
	}
	if(!strncmp(buf,"q",1)){
		for(i=0;i<cnum;i++){
			if(csocks[i]==csock){
				close(csock);
				for(j=1;j<cnum;j++){
					csocks[j]=csocks[j+1];
				}
				cnum--;
			}
		}
		printf("csock closed and pthread exit\n");
		pthread_exit(0);
	}
	printf("Received Data : %s",buf);
	if(write(csock,buf,n)<=0){
		perror("write");
		pthread_exit(0);
		return (void*)NULL;
	}
	printf("now accepted csock :");
	for(i=0;i<cnum;i++)printf("%d ", csocks[i]);
	printf("\n");
	}
	
	pthread_exit(0);
	return (void*)NULL;

}

int main(int argc, char** argv){

	int ssock,n;
	struct sockaddr_in server_addr;
	socklen_t clen;
	char buf[BUFSIZ]="Hello world";
	pthread_t thread;
	
	if((ssock = socket(PF_INET,SOCK_STREAM,0))<0){
				perror("socket()");
				return -1;
	}

	//소켓생성공
	
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(TCP_PORT);
	
	if(bind(ssock,(struct sockaddr *)&server_addr,sizeof(server_addr))<0){
		perror("bind()");
		return -1;

	}
	//bind success
	
	if(listen(ssock,8)<0){
		perror("listen()");
		return -1;

	}
	clen=sizeof(client_addr);
	while(1){
		csock=accept(ssock,(struct sockaddr *)&client_addr,&clen);		
		csocks[cnum++]=csock;
		printf("Client is connected :%s\n",inet_ntoa(client_addr.sin_addr));
		pthread_create(&thread,NULL,client_connection,&csock);
		pthread_detach(thread);
		//close(csock);
	}
	close(ssock);
	return 0;
}
