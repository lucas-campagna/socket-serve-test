#ifndef __UTILS_H__
#define __UTILS_H__

#include <unistd.h>

ssize_t readn(int fd, void *vptr, size_t n);
ssize_t writen(int fd, const void *vptr, size_t n);

#endif // __UTILS_H__