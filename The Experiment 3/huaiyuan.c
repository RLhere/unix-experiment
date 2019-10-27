/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-10-27 17:59:23
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-27 18:18:17
 */
#include<fcntl.h>
#include"apue.h"

int main(int argc, char const *argv[])
{
    int fd;
    struct stat statbuf;

    lstat("./BackUp.txt",&statbuf);
    char buf[statbuf.st_size];

    if((fd = open("./BackUp.txt",FILE_MODE,0777))<0)
        err_sys("open error");

    if(chdir(argv[1])<0)
        err_sys("chdir error");

    if(read(fd,buf,statbuf.st_size) < 0)
        err_sys("read error");
    else
    {
        // printf("%s\n",buf);

    }
    
    return 0;
}
