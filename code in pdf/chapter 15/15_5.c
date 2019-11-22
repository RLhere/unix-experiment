/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-11-22 13:18:23
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-11-22 13:30:15
 */
#include "apue.h"

int main(int argc, char const *argv[])
{
    int     n;
    int     fd[2];
    pid_t   pid;
    char    line[MAXLINE];

    if(pipe(fd) < 0)
        err_sys("pipe error");
    if((pid = fork()) < 0){
        err_sys("fork error");
    }else if(pid < 0){
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
    }else{
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }
    exit(0);
}
