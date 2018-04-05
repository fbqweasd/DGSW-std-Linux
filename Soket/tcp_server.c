#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#define TCP_PORT 5100
int main(int argc, char** argv){

	int ssock,n,csock;
	struct sockaddr_in server_addr,client_addr;
	socklen_t clen;
	char buf[BUFSIZ]="Hello world";

	if((ssock = socket(PF_INET,SOCK_STREAM,0))<0){
				perror("socket()");
				return -1;
	}

	//소켓생성 성공
	
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
		printf("Client is connected :%s\n",inet_ntoa(client_addr.sin_addr));
		if((n=read(csock,buf,BUFSIZ))<=0)
			perror("read()");
		printf("data :%s",buf);
		if(write(csock,buf,n)<=0)
			perror("write()");
		close(csock);
	}
	close(ssock);
	return 0;
}
