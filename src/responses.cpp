#include "configs.h"

void str_echo(int sockfd){
    ssize_t n;
    char line[MSG_LINE_SIZE];

    while(true){
        // if((n = readline(sockfd, line, MSG_LINE_SIZE)) == 0){
        //     return;
        // }
        write(sockfd, line, n);
    }
}