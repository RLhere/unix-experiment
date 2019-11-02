/*
 * @Description: Print file flags for specified descriptor
 * @Version: 1.0
 * @Author: Kevin Liu
 * @Date: 2019-11-02 14:01:08
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-11-02 14:15:10
 */
#include"apue.h"
#include<fcntl.h>

int main(int argc, char const *argv[])
{
    int     val;
    if(argc != 2)
        err_quit("usage: a.out <descriptor#>");
    switch(val & O_ACCMODE) {
        case O_RDONLY:
            printf("read only");
            break;
        
        case O_WRONLY:
            printf("write only");
            break;

        case O_RDWR:
            printf("read write");
            break;

        default:
            err_dump("unknown access mode");
    }
    if(val & O_APPEND)
        printf(", append");
    if(val & O_NONBLOCK)
        printf(", nonblocking");
    if(val & O_SYNC)
        printf(", synchronous writes");

#if !defined(_POSIX_X_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if(val & O_FSYNC)
        printf(", synchronous writes");
#endif

    putchar('\n');
    exit(0);
}
