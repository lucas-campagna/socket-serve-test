#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

int main() {
    int serverSocket, epollfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    // Create a socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // Initialize sockaddr structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345);

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 12345\n");

    // Create epoll instance
    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    // Add the server socket to the epoll instance
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = serverSocket;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, serverSocket, &event) == -1) {
        perror("epoll_ctl: serverSocket");
        exit(EXIT_FAILURE);
    }

    // Array to store events
    struct epoll_event events[MAX_EVENTS];

    while (1) {
        int numEvents = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (numEvents == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < numEvents; ++i) {
            int fd = events[i].data.fd;

            if (fd == serverSocket) {
                // Accept a new connection
                int newSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
                if (newSocket == -1) {
                    perror("accept");
                    continue;
                }

                printf("New connection from %s on port %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

                // Add the new socket to the epoll instance
                event.events = EPOLLIN | EPOLLET; // Edge-triggered mode
                event.data.fd = newSocket;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, newSocket, &event) == -1) {
                    perror("epoll_ctl: newSocket");
                    exit(EXIT_FAILURE);
                }
            } else {
                // Handle data from clients
                ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE);
                if (bytesRead == 0) {
                    // Connection closed by client
                    printf("Client disconnected\n");
                    close(fd);
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
                } else if (bytesRead == -1) {
                    perror("read");
                } else {
                    // Echo back the data to the client
                    send(fd, buffer, bytesRead, 0);
                }
            }
        }
    }

    // Clean up
    close(serverSocket);
    close(epollfd);

    return 0;
}
