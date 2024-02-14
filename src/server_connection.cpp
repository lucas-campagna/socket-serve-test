#include <arpa/inet.h>
#include <netinet/in.h>
#include <server_connection.h>

template<class TServer>
Connection<TServer>::Connection(const TServer *aServerPtr, const int clientFd, struct sockaddr_in *clientSocketPtr):
addres(string(inet_ntoa(clientSocketPtr->sin_addr))),
port(ntohs(clientSocketPtr->sin_port)),
serverPtr(aServerPtr),
fd(clientFd) {};