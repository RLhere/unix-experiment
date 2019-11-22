/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-11-22 10:51:48
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-11-22 11:28:51
 */
#include "apue.h"
#define S_FIFO_NAME "servercreatedfifo"

int main(int argc, char const *argv[])
{
    int fd;
    char buf[BUFFSIZE];
    char C_FIFO_NAME[10];

    umask(0);
    sprintf(C_FIFO_NAME,"%d",getpid());
    printf("%s",C_FIFO_NAME);
    mkfifo(C_FIFO_NAME,S_IFIFO|0666);
    scanf(C_FIFO_NAME,&buf);
    
    //把自己这个进程的进程号写到well-known fifo
    fd = open(S_FIFO_NAME,O_WRONLY | O_NONBLOCK);
    printf("%d\n",fd);
    write(fd, buf, strlen(buf) + 1);

    close(fd);

    //立马开个自己的管道以自己的进程号为名
    fd = open(C_FIFO_NAME,O_RDONLY | O_NONBLOCK);
    printf("%d\n",fd);
    // while(1)
    // {
    //     // printf("%ld",read(fd, buf, BUFFSIZE));
    // }
    while(read(fd, buf, BUFFSIZE) == -1)
    {
        perror("read:");
        break;
    }
    close(fd);

    exit(0);
}
