/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-10-25 16:46:36
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-30 20:26:42
 */
#include "apue.h"

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
            printf("\tgid:%d\tmode:%d\tsize:%ld\tuid:%d\n",statbuf.st_gid,statbuf.st_mode,statbuf.st_size,statbuf.st_uid);
            printdir(entry->d_name, depth + 4);
        }
        else
        {
            printf("%*s%s", depth, "", entry->d_name);
            printf("\tgid:%d\tmode:%d\tsize:%ld\tuid:%d\t",statbuf.st_gid,statbuf.st_mode,statbuf.st_size,statbuf.st_uid);
            int fd;
            if((fd = open(entry->d_name,FILE_MODE,0777))<0)
                err_sys("open error");
            char buf[statbuf.st_size];
            if(read(fd,buf,statbuf.st_size) < 0)
            {
                err_sys("read error");
            }else
            {
                buf[statbuf.st_size] = '\0';
                printf("content:SU%s\n",buf);
            }
            
        }
    }
    chdir("..");
    closedir(dp);
}

int main(int argc, char *argv[])
{
    struct stat topdirbuf;
    char *topdir = ".";
    if (argc >= 2)
        topdir = argv[1];

    printf("Directory scan of %s\t", topdir);
    lstat(topdir,&topdirbuf);
    printf("\tgid:%d\tmode:%d\tsize:%ld\tuid:%d\n",topdirbuf.st_gid,topdirbuf.st_mode,topdirbuf.st_size,topdirbuf.st_uid);
    printdir(topdir, 4);
    printf("done.\n");
    exit(0);
}