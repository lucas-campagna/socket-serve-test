#include "configs.h"
#include "utils.h"

extern void str_echo(int sockfd);

int main(int argc, char **argv){
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htonl(SERV_PORT);

    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(listenfd, LISTEN_QUEUE_SIZE);

    while(true){
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

        if( (childpid = fork()) == 0){ // child process
            close(listenfd); // close listening socket
            str_echo(connfd); // process the request
            exit(0);
        }
        close(connfd); // parent closes conected socket
    }
}