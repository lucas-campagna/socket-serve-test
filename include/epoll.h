#ifndef __EPOLL_H__
#define __EPOLL_H__

#include <sys/epoll.h>
#include <memory>
#include <vector>

using namespace std;

class Epoll{
        const int mFd;
        int ctl(const int op, const int fd, const uint32_t events);
    public:
        Epoll();
        int add(const int fd, const uint32_t events);
        int mod(const int fd, const uint32_t events);
        int del(const int fd, const uint32_t events);
        /*
         * wait
         * calls epoll_wait
         * @params asd
        */
        unique_ptr<vector<struct epoll_event>> wait(const int maxevents = 10, const int timeout = -1);
};

#endif // __EPOLL_H__