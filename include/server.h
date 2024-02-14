#ifndef __SERVER_H__
#define __SERVER_H__

#include <epoll.h>
#include <string>
#include <map>
#include <utility>
#include <functional>
#include <server_connection.h>
#include <arpa/inet.h>

using namespace std;

class Server;
typedef Connection<Server> ServerConnection;

/*
 * TCP Server
 */
class Server{
        struct sockaddr_in socketAddr;
        const int listenQueueSize;
        map<int, ServerConnection*> connections;
        Epoll poll;
        void handleIncomingConnection();
        inline void handleIncomingMessage(const struct epoll_event & event);
        void handleEvent(const struct epoll_event & event);
        unsigned long nConnections;
        
    public:
        const int fd;
        const string address;
        const int port;
        Server(string aAddress = "0.0.0.0", const int aPort = 3000, const int aListenQueueSize = 10);
        void run();
        unsigned long getNConnections(){return nConnections;};
        function<void(ServerConnection &connection)> onConnect;
        function<void(ServerConnection &connection)> onMessage;
        void disconnect(const int clientFd);
};

#endif // __SERVER_H__