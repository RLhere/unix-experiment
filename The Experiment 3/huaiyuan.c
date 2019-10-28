/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-10-27 17:59:23
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-28 14:53:04
 */
#include<fcntl.h>
#include"apue.h"
#include<malloc.h>

int main(int argc, char const *argv[])
{
    int fd;
    // int flag = 1;
    int curlineend = 0;
    int prelineend;
    struct stat (*statbuf);
    char * curline = NULL;
    // int test[1000] = {0};//目前这段代码编译执行都是成功的，但一旦把这行注释去掉编译执行就会出现分段错误

    // long long int line[1000];

    lstat("./BackUp.txt",statbuf);
    char buf[(*statbuf).st_size];

    if((fd = open("./BackUp.txt",FILE_MODE,0777))<0)
        err_sys("open error");

    if(chdir(argv[1])<0)
        err_sys("chdir error");

    if(read(fd,buf,(*statbuf).st_size) < 0)
        err_sys("read error");
    else
    {
        for(int i = 0;i < (*statbuf).st_size; i++)
        {
            if(buf[i] == '\n')
            {
                if(curlineend != 0)
                {
                    prelineend = curlineend;
                }
                curlineend = i;
                int curlinebegin = prelineend + 1;
                curline = (char *)malloc((curlineend - curlinebegin + 1) * sizeof(char));
                curline = buf + curlinebegin;
                for(int j = 0;j < (curlineend - curlinebegin + 1);j++)
                {
                    printf("%c",curline[curlineend - curlinebegin]);
                }
                // char linebuf[curlineend - prelineend];
            }
        }
        // system("pause");
        // for(int i = 0;i < (*statbuf).st_size;i++)
        // {
        //     // if(buf[i] == '\n')
        //     // {
        //     //     // line[linecount] = i;
        //     //     linecount = linecount + 1;
        //     // }
        // }

        // for(int j=0;j<linecount;j++)
        // {
        //     printf("\t%d",line[j]);
        // }
        // printf("%s\n",buf);
        // int linecount = 1;
        // for(int i = 0;i < (*statbuf).st_size;i++)
        // {
        //     if(buf[i] == '\n')
        //         linecount += 1;
        // }
        // printf("%d\n",linecount);
        // (*statbuf).st_uid = 1001;
        // printf("%ld",*(&((*statbuf).st_size)));想通过修改结构体里的值来修改文件属性果然最终修改无效
    }
    
    return 0;
}
