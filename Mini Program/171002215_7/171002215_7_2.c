/*
 * @Description: plus one to the uid of the file and the folder,then change the mode of both to 777
 * @Version: 2.0
 * @Author: Kevin Liu
 * @Date: 2019-10-19 15:18:53
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-19 16:23:52
 */
#include "apue.h"
#include "my_err.h"
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int i;
    int fd;
    struct stat buf;

    if (chdir("./newdir") < 0)
        err_sys("chdir failed");
    printf("chdir to ./newdir succeeded\n");

    if ((fd = creat("file.txt", FILE_MODE)) < 0)
        err_sys("creat error");

    for (i = 1; i < 3; i++)
    {
        switch (i)
        {
        case 1:
        {
            printf("file.txt: ");
            if (lstat("file.txt", &buf) < 0)
            {
                err_ret("lstat error");
                continue;
            }

            if(chmod("file.txt",S_IRWXU | S_IRWXG | S_IRWXO) < 0)
                err_sys("chmod error for file.txt");

            printf("the implused uid: %d\t", buf.st_uid);
            buf.st_uid = buf.st_uid + 1;
            printf("the plused uid: %d\t", buf.st_uid);
            printf("the changed mode of file.txt:%d\n",buf.st_mode);
            break;
        }
        case 2:
        {
            printf("newdir: ");
            if (lstat("../newdir", &buf) < 0)
            {
                err_ret("lstat error");
                continue;
            }

            if(chmod(".",S_IRWXU | S_IRWXG | S_IRWXO) < 0)
                err_sys("chmod error for ./newdir");
            
            printf("the implused uid: %d\t", buf.st_uid);
            buf.st_uid = buf.st_uid + 1;
            printf("the plused uid: %d\n", buf.st_uid);
            printf("the changed mode of newdir:%d\n",buf.st_mode);
            break;
        }
        }
    }

    exit(0);
}