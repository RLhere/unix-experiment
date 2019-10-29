/*
 * @Description: the back part of the file backup
 * @Version: 2.0
 * @Author: Kevin Liu
 * @Date: 2019-10-29 22:52:21
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-30 03:28:29
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
        if( (chdir(argv[1]) < 0 ) )
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

    
    /**
     * @description: 本来我想用函数把文档内容分开成行的，但是我不知道如何解决声明了指
     * 针变量不立即初始化导致的SIGSEGV信号报错所以在主函数里写这段代码来代替
     * @param: ALLines 
     * @return: 将整个文档分成了每行，并将文档占用缓存释放，然后指针置空了
     * @author: Kevin Liu
     */
    char ** ALLines = (char**)malloc((*linenumber) * sizeof(char*));
    long int     index[*linenumber][2];
    int     herelineno = 0;
    index[0][0] = 0;
    for(int i = 0; i < statbuf.st_size; i++)
    {
        if(Document[i] == '\n')
        {
            if(herelineno!=0)
                index[herelineno][0] = index[herelineno-1][1] + 1;
            index[herelineno][1] = i;
            herelineno = herelineno + 1;
        }
    }
    index[(*linenumber)-1][0] = index[(*linenumber)-2][1] + 1;
    index[(*linenumber)-1][1] = index[(*linenumber)-1][0];
    int length[*linenumber];
    for(int i = 0; i < *linenumber;i++)
    {
        length[i] = index[i][1] - index[i][0] + 1;
        ALLines[i] = (char *)malloc(length[i] * sizeof(char));
        int temp = index[i][0];
        for(int otemp = 0;otemp < length[i];otemp++)
        {
            ALLines[i][otemp] = Document[temp++];
        }
    }
    free(Document);
    Document = NULL;

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