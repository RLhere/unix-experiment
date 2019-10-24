/*
 * @Description: creating a file in the given folder and print the owner and type of the file
 * @Version: 2.0
 * @Author: Kevin Liu
 * @Date: 2019-10-19 15:18:53
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-19 16:03:45
 */
#include "apue.h"
#include "my_err.h"
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int i;
    int fd;
    struct stat buf;
    char        *ptr;

    if (chdir("./newdir") < 0)
        err_sys("chdir failed");
    printf("chdir to ./newdir succeeded\n");

    if((fd = creat("file.txt", FILE_MODE)) < 0)
        err_sys("creat error");

    for(i = 1; i < 3; i++)
    {
        switch(i)
        {
            case 1:
            {
                printf("file.txt: ");
                if (lstat("file.txt", &buf) < 0){
                    err_ret("lstat error");
                    continue;
                }
                if(S_ISREG(buf.st_mode))
                    ptr = "regular";
                else if(S_ISDIR(buf.st_mode))
                    ptr = "directory";
                else if(S_ISCHR(buf.st_mode))
                    ptr = "character special";
                else if(S_ISBLK(buf.st_mode))
                    ptr = "block special";
                else if(S_ISFIFO(buf.st_mode))
                    ptr = "fifo";
                else if(S_ISLNK(buf.st_mode))
                    ptr = "symbolic link";
                else if(S_ISSOCK(buf.st_mode))
                    ptr = "socket";
                else
                {
                    ptr = "** unknown mode **";
                }
                printf("%s  %d\n", ptr, buf.st_uid);
                break;
            }
            case 2:
            {
                printf("newdir: ");
                if (lstat("../newdir", &buf) < 0){
                    err_ret("lstat error");
                    continue;
                }
                if(S_ISREG(buf.st_mode))
                    ptr = "regular";
                else if(S_ISDIR(buf.st_mode))
                    ptr = "directory";
                else if(S_ISCHR(buf.st_mode))
                    ptr = "character special";
                else if(S_ISBLK(buf.st_mode))
                    ptr = "block special";
                else if(S_ISFIFO(buf.st_mode))
                    ptr = "fifo";
                else if(S_ISLNK(buf.st_mode))
                    ptr = "symbolic link";
                else if(S_ISSOCK(buf.st_mode))
                    ptr = "socket";
                else
                {
                    ptr = "** unknown mode **";
                }
                printf("%s  %d\n", ptr, buf.st_uid);
                break;
            }
        }
    }

    exit(0);
}