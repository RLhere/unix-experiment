/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-10-25 16:46:36
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-27 14:12:35
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
    int fd;
    if((fd = open("Backup.txt", O_APPEND|O_RDWR|O_CREAT|O_TRUNC,0777)) < 0)
        err_sys("creat error");

    DIR *dp;  
    struct dirent *entry;  
    struct stat statbuf;  
  
    if ((dp = opendir(dir)) == NULL) {  
        fprintf(stderr, "Can`t open directory %s\n", dir);  
        return ;
    }  
      
    chdir(dir);  
    while ((entry = readdir(dp)) != NULL) {  

        lstat(entry->d_name, &statbuf);  
        if (S_ISDIR(statbuf.st_mode)) {  
            if (strcmp(entry->d_name, ".") == 0 ||   
                strcmp(entry->d_name, "..") == 0 )    
                continue;
    
            printf("%*s%s/\n", depth, "", entry->d_name);  
            printdir(entry->d_name, depth+4);  
        } else{
            printf("%*s%s\n", depth, "", entry->d_name);
        }  
              
    }  
    chdir("..");  
    closedir(dp);     
    close(fd);
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