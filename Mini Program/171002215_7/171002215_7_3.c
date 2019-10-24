/*
 * @Description: creating a txt file ,then creat a symbolink for it then read and readlink
 * @Version: 2.0
 * @Author: Kevin Liu
 * @Date: 2019-10-19 15:19:17
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-19 17:12:16
 */
#include "apue.h"
#include "my_err.h"
#include <fcntl.h>
#define BUFFSIZE 4096

int main(int argc, char const *argv[])
{
    int n;
    int fd, fd2;
    struct stat buf;
    char    buf1[] = "abcdefghij";
    char    buf2[BUFFSIZE];
    char    bufl[BUFFSIZE];

    if (chdir("./newdir") < 0)
        err_sys("chdir failed");
    printf("chdir to ./newdir succeeded\n");

    if ((fd = creat("file.txt", FILE_MODE)) < 0)
        err_sys("creat error");

    if(write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");

    if(symlink("/mnt/c/Users/Matebook/Desktop/Unix环境高级编程/mini program/171002215_7/newdir/file.txt","/mnt/c/Users/Matebook/Desktop/Unix环境高级编程/mini program/171002215_7/filefuben.txt") < 0)
        err_sys("symlink creat error");

    if((fd2 = open("../filefuben.txt", O_RDWR)) < 0)
        err_sys("open filefuben.txt error");


    while((n = read(fd2, buf2, BUFFSIZE)) > 0)
        printf("%s",buf2);
    
    printf("\n");

    if(n < 0)
        err_sys("read error");

    if(readlink("/mnt/c/Users/Matebook/Desktop/Unix环境高级编程/mini program/171002215_7/filefuben.txt", bufl, BUFFSIZE) < 0)
        err_sys("readsymlink error");
    else
    {
        printf("%s",bufl);
    }

    printf("\n");

    exit(0);
}