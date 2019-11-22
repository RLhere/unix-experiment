/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-11-22 10:38:57
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-11-22 18:32:45
 */
#include "apue.h"
#define S_FIFO_NAME "/tmp/servercreatedfifo"


int main(int argc, char const *argv[])
{
    int fd;
    void handler();
    char buf[BUFFSIZE];

    umask(0);
    if(mkfifo(S_FIFO_NAME,0777) == -1)
    {
        perror("mkfifo error!");
        exit(1);
    }

    int open_mode = 0;

    signal(SIGINT,handler);
    printf("Process %d is listenning!\n",getpid());
    while(1)
    {
    listen:
        sleep(1);
        open_mode = 0;
        open_mode |= O_RDONLY;

        int     n = 0;

        fd = open(S_FIFO_NAME, open_mode);
        while((n = read(fd, buf, BUFFSIZE)) == -1)
        {
            //等待管道消息
        }
        close(fd);
        break;
    }

    //TODO::给各个client进程发消息通过各个client进程建立的命名管道
    printf("%s",buf);
    goto listen;

    exit(0);
}

void handler()
{
    unlink(S_FIFO_NAME);
}
