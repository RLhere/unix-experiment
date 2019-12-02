/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-11-22 10:51:48
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-11-22 18:49:28
 */
#include "apue.h"
#define S_FIFO_NAME "/tmp/servercreatedfifo"

int main(int argc, char const *argv[])
{
    int fd;
    int open_mode = 0;
    void handler(char arg[10]);
    char buf[BUFFSIZE];
    char C_FIFO_NAME[10];

    umask(0);
    sprintf(C_FIFO_NAME,"%d",getpid());
    mkfifo(C_FIFO_NAME,0777);
    sscanf(C_FIFO_NAME,"%s",&buf);
    
    //把自己这个进程的进程号写到well-known fifo
    open_mode |= O_WRONLY;
    fd = open(S_FIFO_NAME,open_mode);
    write(fd, buf, strlen(buf) + 1);

    close(fd);

    //立马开个自己的管道以自己的进程号为名
    open_mode = 0;
    open_mode |= O_RDONLY;
    fd = open(C_FIFO_NAME,open_mode);
    while(read(fd, buf, BUFFSIZE) == -1)
    {
        sleep(1);//等消息
    }
    printf("%s\n",buf);
    close(fd);

    signal(SIGINT,handler);

    exit(0);
}

void handler(char arg[10])
{
    unlink(S_FIFO_NAME);
    unlink(arg);
}