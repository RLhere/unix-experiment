/*
 * @Description: Create a newuser newuser on Unix/Linux and program to create sources/ folder under the user's system directory file /home/newuser/;Then, in sources folder, create 5 folders (name: 5 random lowercase English letter strings), create 5 more folders in each folder (name: 5 random lowercase English letter strings);Create 20 files in each of the 1+5+5*5=31 folders, each with 100 random lowercase letters and a filename of 8 random uppercase strings.
 * @Version: 2.0
 * @Author: Kevin Liu
 * @Date: 2019-10-20 14:50:31
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-25 21:23:54
 */
#include "apue.h"
#include <fcntl.h>
#include <stdlib.h>
#define BUFFSIZE 4096

int main(int argc, char const *argv[])
{
    char name[BUFFSIZE];
    char buf[BUFFSIZE];
    int fd;

    if ((mkdir("sources", 0777)) < 0)
        err_sys("mkdir error");

    if ((chdir("sources")) < 0)
        err_sys("chdir error");

    for (int i = 0; i < 5; i++)
    {
        for (int ji = 0; ji < 5; ji++)
        {
            name[ji] = 'a' + rand() % 26;
        }
        mkdir(name, 0777);
        chdir(name);
        for (int j = 0; j < 5; j++)
        {
            for (int jii = 0; jii < 5; jii++)
            {
                name[jii] = 'a' + rand() % 26;
            }
            mkdir(name, 0777);
            chdir(name);
            for (int k = 0; k < 20; k++)
            {
                for (int jiii = 0; jiii < 8; jiii++)
                {
                    name[jiii] = 'A' + rand() % 26;
                }
                if ((fd = creat(name, FILE_MODE)) < 0)
                    err_sys("creat error");
                //在文件中写东西
                for (int n = 0; n < 100; n++)
                {
                    buf[n] = 'a' + rand() % 26;
                }
                if (write(fd, buf, 100) < 0)
                    err_sys("write error");
                close(fd);
            }
            chdir("..");
            name[5] = '\0';
        }
        chdir("..");
    }
    return 0;
}