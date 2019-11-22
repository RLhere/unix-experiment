/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-11-22 10:38:57
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-11-22 11:31:07
 */
#include "apue.h"
#define S_FIFO_NAME "servercreatedfifo"


int main(int argc, char const *argv[])
{
    int fd;
    char buf[BUFFSIZE];

    umask(0);
    if(mkfifo(S_FIFO_NAME,S_IFIFO|0666) == -1)
    {
        perror("mkfifo error!");
        exit(1);
    }

    while(1)
    {
    #listen:
        sleep(1);

        fd = open(S_FIFO_NAME, O_WRONLY);
        while(read(fd, buf, BUFFSIZE) == -1)
        {
        }
        close(fd);
        break;
    }

    //TODO::给各个client进程发消息通过各个client进程建立的命名管道
    

    goto listen;

    exit(0);
}
