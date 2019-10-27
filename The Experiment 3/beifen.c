/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-10-25 16:46:36
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-27 23:10:50
 */
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "apue.h"
#include <fcntl.h>
#define BUFFSIZE 4096

void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if ((dp = opendir(dir)) == NULL)
    {
        fprintf(stderr, "Can`t open directory %s\n", dir);
        return;
    }

    chdir(dir);
    while ((entry = readdir(dp)) != NULL)
    {

        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode))
        {
            if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0)
                continue;

            printf("%*s%s/", depth, "", entry->d_name);
            printf("\tatime:%ld\tctime:%ld\tdev:%ld\tgid:%d\tino:%ld\tmode:%d\tmtime:%ld\tnlink:%ld\trdev:%ld\tsize:%ld\tuid:%d\n", statbuf.st_atime, statbuf.st_ctime,statbuf.st_dev,statbuf.st_gid,statbuf.st_ino,statbuf.st_mode,statbuf.st_mtime,statbuf.st_nlink,statbuf.st_rdev,statbuf.st_size,statbuf.st_uid);
            printdir(entry->d_name, depth + 4);
        }
        else
        {
            printf("%*s%s", depth, "", entry->d_name);
            printf("\tatime:%ld\tctime:%ld\tdev:%ld\tgid:%d\tino:%ld\tmode:%d\tmtime:%ld\tnlink:%ld\trdev:%ld\tsize:%ld\tuid:%d\t", statbuf.st_atime, statbuf.st_ctime,statbuf.st_dev,statbuf.st_gid,statbuf.st_ino,statbuf.st_mode,statbuf.st_mtime,statbuf.st_nlink,statbuf.st_rdev,statbuf.st_size,statbuf.st_uid);
            int fd;
            if((fd = open(entry->d_name,FILE_MODE,0777))<0)
                err_sys("open error");
            char buf[statbuf.st_size];
            if(read(fd,buf,statbuf.st_size) < 0)
            {
                err_sys("read error");
            }else
            {
                printf("content:\t%s\n",buf);
            }
            
        }
    }
    chdir("..");
    closedir(dp);
}

int main(int argc, char *argv[])
{
    char *topdir = ".";
    if (argc >= 2)
        topdir = argv[1];

    printf("Directory scan of %s\n", topdir);
    printdir(topdir, 0);
    printf("done.\n");
    exit(0);
}