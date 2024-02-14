#include "epoll.h"
#include <iostream>
#include <memory>


using namespace std;

Epoll::Epoll() : 
mFd(epoll_create1(0)){
    if (mFd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }
}

int Epoll::ctl(const int op, const int fd, const uint32_t events){
    struct epoll_event event;
    event.events = events;
    event.data.fd = fd;
    int ret = epoll_ctl(mFd, op, fd, &event);
    if (ret == -1) {
        perror("Epoll.ctl: epoll_ctl call error");
        exit(EXIT_FAILURE);
    }
    return ret;
}
int Epoll::add(const int fd, const uint32_t events){
    return ctl(EPOLL_CTL_ADD, fd, events);
}
int Epoll::mod(const int fd, const uint32_t events){
    return ctl(EPOLL_CTL_MOD, fd, events);
}
int Epoll::del(const int fd, const uint32_t events){
    return ctl(EPOLL_CTL_DEL, fd, events);
}

unique_ptr<vector<struct epoll_event>> Epoll::wait(const int maxevents, const int timeout){
    auto events = unique_ptr<vector<struct epoll_event>>(new vector<struct epoll_event>(maxevents));
    const int numEvents = epoll_wait(mFd, events.get()->data(), maxevents, timeout);
    if (numEvents == -1) {
        perror("epoll_wait");
        exit(EXIT_FAILURE);
    }
    return events;
}