/*
 * @Description: 
 * @Version: 2.0
 * @Author: Kevin Liu
 * @Date: 2019-10-21 17:10:42
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-21 17:24:31
 */
#include "apue.h"
#include "my_err.h"

int main(int argc, char const *argv[])
{
    int fd;
    char buf[4096];
    char buf1[4096];

    if((fd = open("./filefuben.txt",O_RDWR)) < 0)
        err_sys("open error");
    
    while((read(fd,buf,4096)) > 0)
        printf("%s",buf);
    
    // while((readlink("./filefuben.txt",buf1,4096)) > 0)
    // {
    //     printf("%s",buf1);
    //     break;
    // }

    return 0;
}
