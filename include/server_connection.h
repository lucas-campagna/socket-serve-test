#ifndef __SERVER_CONNECTION_H__
#define __SERVER_CONNECTION_H__

#include <epoll.h>

template <class TServer>
class Connection{
        const int fd;
        TServer *serverPtr;
    public:
        const string addres;
        const int port;
        void send(string & msg);
        void disconnect(){serverPtr->disconnect(fd);};
        Connection(const TServer *aServerPtr, const int clientFd, struct sockaddr_in *clientSocketPtr);
};

#endif // __SERVER_CONNECTION_H__