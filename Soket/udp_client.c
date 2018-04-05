
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define UDP_PORT 5100

int main(int argc, char **argv) {

        int sockfd, n;
        struct sockaddr_in servaddr, cliaddr;
        socklen_t clisize;
        char sendline[BUFSIZ];
        char recvline[BUFSIZ];

        if (argc != 2) {
                printf("usage : %s <IP address> \n", argv[0]);
                return -1;
        }

        sockfd = socket(PF_INET, SOCK_DGRAM, 0);
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr(argv[1]);
        servaddr.sin_port = htons(UDP_PORT);

        while(fgets(sendline, BUFSIZ, stdin) != NULL) {

                if (!strncmp(sendline, "q", 1)) break;
                sendto(sockfd, sendline, strlen(sendline), 0,
                (struct sockaddr*)&servaddr, sizeof(servaddr));
                clisize = sizeof(cliaddr);
                n = recvfrom(sockfd, recvline, BUFSIZ, 0,
                (struct sockaddr*)&cliaddr, &clisize);
                recvline[n] = '\0';

        };

        close(sockfd);
        return 0;

}

