#include "configs.h"
#include "utils.h"
#include <server.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
#include <server_connection.h>

Server::Server(string aAddress, const int aPort, const int aListenQueueSize) :
address(aAddress),
port(aPort),
listenQueueSize(aListenQueueSize),
nConnections(0),
fd(socket(AF_INET, SOCK_STREAM, 0)) {
    if(fd == 0){
        perror("Server: socket creation fail");
        exit(EXIT_FAILURE);
    }
    bzero(&socketAddr, sizeof(socketAddr));
    socketAddr.sin_family = AF_INET;
    socketAddr.sin_addr.s_addr = inet_addr(address.c_str());
    socketAddr.sin_port = htonl(port);
    bind(fd, (struct sockaddr *) &socketAddr, sizeof(socketAddr));
    listen(fd, aListenQueueSize);
};


void Server::run(){
    poll.add(fd, EPOLLIN);
    cout << "Starting server at " << address << ":" << port << endl;
    while(true){
        auto eventsUniquePtr = poll.wait();
        const int numEvents = eventsUniquePtr.get()->size();
        for(const auto & event : *eventsUniquePtr.get()){
            // TODO: Add paralellism here
            handleEvent(event);
        }
    }
}

void Server::handleEvent(const struct epoll_event & event){
    if(event.data.fd == fd){
        handleIncomingConnection();
    } else {
        handleIncomingMessage(event);
    }
}

inline void Server::handleIncomingMessage(const struct epoll_event & event){
    if(onMessage){
        onMessage(*connections.at(event.data.fd));
    }
}

void Server::handleIncomingConnection(){
    // struct sockaddr_in *clientSocketPtr = new sockaddr_in;
    // socklen_t clientBufferSize = sizeof(struct sockaddr_in);
    // const int clientFd = accept(fd, (struct sockaddr*) clientSocketPtr, &clientBufferSize);
    // if (clientFd == -1) {
    //     perror("Server.handleIncomingConnection: error while accepting client");
    //     exit(EXIT_FAILURE);
    // }
    // connections[clientFd] = ServerConnection(this, clientFd, clientSocketPtr);
    // poll.add(clientFd, EPOLLIN | EPOLLET);
    // if(onConnect){
    //     onConnect(*connections.at(clientFd));
    // }
}

void Server::disconnect(const int clientFd){
    poll.del(clientFd, EPOLLIN | EPOLLET);
    close(clientFd);
    delete connections.at(clientFd);
    connections.erase(clientFd);
}