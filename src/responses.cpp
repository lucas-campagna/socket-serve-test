#include "configs.h"
#include "utils.h"

void str_echo(int sockfd){
    ssize_t n;
    char line[MSG_LINE_SIZE];

    while(true){
        if((n = readn(sockfd, line, MSG_LINE_SIZE)) == 0){
            return;
        }
        writen(sockfd, line, n);
    }
}