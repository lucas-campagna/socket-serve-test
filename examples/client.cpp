#include "configs.h"
#include "utils.h"

void str_cli(FILE *fp, int sockfd);

int main(int argc, char **argv){
    int sockfd;
    struct sockaddr_in servaddr;

    if(argc != 2)
        err_quit("usage: tcpcli <IPaddress>");

    sockdf = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htonl(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    connect(sockfd, (struct socket *) &servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);

    exit(0);
}

void str_cli(FILE *fp, int sockfd){
    char sendline[MSG_LINE_SIZE], recvline[MSG_LINE_SIZE];
    while(fgets(sendline, MSG_LINE_SIZE, fp) != NULL){
        writen(sockfd, sendline, MSG_LINE_SIZE);

        if(readline(sockfd, recvline, MSG_LINE_SIZE) == 0){
            err_quit("str_cli: server terminated prematurely");
        }
        fputs(recvline, stdout);
    }
}