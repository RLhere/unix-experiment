/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-10-29 22:52:21
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-30 00:05:58
 */
#include "apue.h"

int main(int argc, char const *argv[])
{
    //读取整个文档
    struct stat statbuf;
    lstat("./BackUp.txt",&statbuf);
    char * Document = (char *)malloc((statbuf.st_size * sizeof(char)));
    int fd;
    if((fd = open("./BackUp.txt",FILE_MODE,0777)) < 0)
        err_sys("open Backup.txt error");
    if(read( fd, Document,statbuf.st_size) < 0)
        err_sys("read error");

    void Curline(char * form_Document,long int doc_Size,char * cur_line,int * inDent,int * fileType,int * attribute,int * curline);
    /**
     * @description: 根据传入参数将每行分开存储  获取每行缩进  获取每行记录文件类型  属性  简而言之提取信息
     * @param {char*,long int,char*,int*,int*,int*,int*} 
     * @return: void
     * @author: Kevin Liu
     */    
    // Curline( Document, statbuf.st_size,)

    return 0;
}

void Curline(char * form_Document,long int doc_Size,char * cur_line,int * inDent,int * fileType,int * attribute,int * curline)
{

}
