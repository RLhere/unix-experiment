/*
 * @Description: the back part of the file backup
 * @Version: 2.0
 * @Author: Kevin Liu
 * @Date: 2019-10-29 22:52:21
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-30 01:16:15
 */
#include "apue.h"

int main(int argc, char const *argv[])
{
    /**
     * @description: change the topdir where backup the file
     * @param { the number of parameters, the dir where backup the file } 
     * @return: not a function, a statement of operations
     * @author: Kevin Liu
     */
    if( argc == 2 )
    {
        if( (chdir(argv[1]) < 0 )
            err_sys("change dir error");
    }

    /**
     * @description: read the entile backup document
     * @param {the stat of the document, a buf which receives the all content in document} 
     * @return: not a function, is a statement of operation
     * @author: Kevin Liu
     */
    struct stat statbuf;
    lstat("./BackUp.txt",&statbuf);
    char * Document = (char *)malloc((statbuf.st_size * sizeof(char)));
    int fd;
    if((fd = open("./BackUp.txt",FILE_MODE,0777)) < 0)
        err_sys("open Backup.txt error");
    if(read( fd, Document,statbuf.st_size) < 0)
        err_sys("read error");

    /**
     * @description: count lines of the document
     * @param {the document , nbytes of the document, linenumber of the document} 
     * @return: no return  change the value through the pointer
     * @author: Kevin Liu
     */
    void countlines(char * form_Documnet,long int doc_size,int * linenumber);
    int * linenumber = (int *)malloc(sizeof(int));
    *linenumber = 1;
    countlines( Document, statbuf.st_size, linenumber);

    return 0;
}

void countlines(char * form_Documnet,long int doc_size,int * linenumber)
{
    for(int i = 0;i < doc_size;i++)
    {
        if(form_Documnet[i] == '\n')
            (*linenumber)++;
    }
}