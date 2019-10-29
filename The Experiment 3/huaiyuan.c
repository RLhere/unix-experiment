/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-10-27 17:59:23
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-29 22:48:23
 */
#include"apue.h"

int main(int argc, char const *argv[])
{
    int predepth = 0;
    int curdepth;
    int line = 0;
    int fd;
    int attr[4];
    int depth = 0;
    int curlineend = 0;
    int curlinebegin;
    int prelineend;
    struct stat * statbuf;
    statbuf = (struct stat *)malloc(sizeof(struct stat));
    
    char ** attribute = (char **)malloc(5*sizeof(char *));
    attribute[0] = (char *)malloc(4*sizeof(char));
    attribute[1] = (char *)malloc(5*sizeof(char));
    attribute[2] = (char *)malloc(5*sizeof(char));
    attribute[3] = (char *)malloc(4*sizeof(char));
    attribute[4] = (char *)malloc(8*sizeof(char));
    attribute[0] = "gid:";
    attribute[1] = "mode:";
    attribute[2] = "size:";
    attribute[3] = "uid:";
    attribute[4] = "content:";

    int checktype(char *curline,int begin,int end);
    void create(int type,char * curline,int begin,int end,int *attr);

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
            if(buf[i] == '\n')//检测到换行
            {
                line++;
                // printf("%d",line);
                if(curlineend != 0)
                {
                    prelineend = curlineend;
                }
                curlineend = i;
                if(line != 1)
                    curlinebegin = prelineend + 1;
                // printf("%c%c\n",buf[curlinebegin],buf[curlineend - 1]);定位每行开头结尾在整个文档中的位置正确
                char * curline = (char *)malloc((curlineend - curlinebegin + 1)*(sizeof(char)));
                int size = curlineend - curlinebegin;
                int otemp = 0;
                for(int temp = curlinebegin;temp < curlineend + 1;)
                {
                    curline[otemp++] = buf[temp++];
                }
                // printf("%s",curline);确认存储到了当前行内容
                // break;

                //第一行读取根文件夹名以及各属性并创建根文件夹
                if(line == 1)//控制为第一行
                {
                    otemp = 0;
                    int temp;
                    int times = 0;
                    int beginIndex,endIndex;
                    for(temp = i;temp > curlinebegin;temp--)
                    {
                        if(curline[temp]==':'&&curline[temp-1]=='e'&&curline[temp-2]=='d'&&curline[temp-3]=='o'&&curline[temp-4]=='m')
                        {
                            char* recmode = (char *)malloc(5*sizeof(char));
                            for(int rtemp = temp+1;rtemp < temp + 6;)
                            {
                                recmode[otemp++] = curline[rtemp++];
                            }
                            otemp = 0;
                            sscanf(recmode,"%d",&attr[1]);
                        }
                        if(curline[temp] == '/')
                        {
                            times++;
                            if(times == 1)
                            {
                                endIndex = temp;
                            }
                            if(times == 2)
                            {
                                beginIndex = temp;
                                break;
                            }
                        }
                    }

                    //得到目录参数
                    char * recdir = (char *)malloc((endIndex-beginIndex+1)*sizeof(char));
                    for(int temp = beginIndex + 1;temp < endIndex;)
                    {
                        recdir[otemp++] = curline[temp++];
                    }
                    otemp = 0;
                    //已得到目录参数
                    mkdir(recdir,attr[1]);
                    chdir(recdir);
                }
                else//判断该行是目录还是文件  是几级目录 然后再具体操作
                {
                    if(curline[0]==' ')
                        curdepth = 0;
                    if(curline[4]==' ')
                        curdepth = 1;
                    if(curline[8]==' ')
                        curdepth = 2;

                    // printf("%d\t%d",line,curdepth);测试时看的
                    int depthflag = curdepth - predepth;//表示与当前目录层次关系
                    // printf("\t%d\n",depthflag);
                    if(depthflag > 0)
                    {
                        // chdir()//进入先前创建的文件夹
                        // int type = checktype(curline,curlinebegin,curlineend);//检索文件类型
                        // printf("%d\n",type);
                        //取文件或目录名及对应属性然后创建void create(int type,char **attribute,int* attr)
                        //切换到目录
                        predepth = curdepth;
                    }else if(depthflag == 0){
                        // int type = checktype(curline,curlinebegin,curlineend);//检索文件类型
                        // printf("%d\n",type);//检索文件类型
                        //取文件或目录名及对应属性然后创建并修改权限用户
                    }else{
                        chdir("..");//切换到上级目录
                        // int type = checktype(curline,curlinebegin,curlineend);//检索文件类型
                        // printf("%d\n",type);//检索该行要创建的文件或文件夹信息
                        //创建
                        predepth = curdepth;
                    }
                }
            }
        }
    }
    return 0;
}

int checktype(char* curline,int begin,int end)
{
    printf("%s",curline);//for check
    // for(int i = 0;i < end - begin + 1;i++)
    // {
    //     // printf("%c",curline[i]);
    //     if(curline[i]=='/')
    //     {
    //         return 1;
    //     }
    // }
    return 0;
}

// void create(int type,char * curline,int begin,int end,int * attr)
// {
//     for(int i = 0;i < end - begin + 1;i++)
//     {
//         int otemp = 0;
//         //gid
//         if(curline[i]=='g'&&curline[i+1]=='i'&&curline[i+2]=='d'&&curline[i+3]==':')
//         {
//             char * recgid = (char *)malloc(4*sizeof(char));
//             for(int temp = i + 4;temp < (i + 8);temp++)
//             {
//                 recgid[otemp] = curline[temp];
//             }
//             otemp = 0;
//             sscanf(recgid,"%d",&attr[0]);
//         }
//         //mode
//         if(curline[i]=='m'&&curline[i+1]=='o'&&curline[i+2]=='d'&&curline[i+3]=='e'&&curline[i+4]==':')
//         {
//             char * recmode = (char *)malloc(5*sizeof(char));
//             for(int temp = i + 5;temp < (i + 10);temp++)
//             {
//                 recmode[otemp] = curline[temp];
//             }
//             otemp = 0;
//             sscanf(recmode,"%d",&attr[1]);
//         }
//         //size
//         if(curline[i]=='s'&&curline[i+1]=='i'&&curline[i+2]=='z'&&curline[i+3]=='e'&&curline[i+4]==':')
//         {
//             int length = 0;
//             for(int temp = i + 5;;temp++)
//             {
//                 if(curline[temp] != ' ')
//                     length++;
//                 else
//                 {
//                     break;
//                 }    
//             }
//             char * recsize = (char*)malloc(length*sizeof(char));
//             for(int temp = i + 5;temp < i + 5 + length;temp++)
//             {
//                 recsize[otemp++] = curline[temp];
//             }
//             otemp = 0;
//             sscanf(recsize,"%d",&attr[2]);
//         }
//         //uid
//         if(curline[i]=='u'&&curline[i+1]=='i'&&curline[i+2]=='d'&&curline[i+3]==':')
//         {
//             char * recuid = (char *)malloc(4*sizeof(char));
//             for(int temp = i + 4;temp < (i + 8);temp++)
//             {
//                 recuid[otemp] = curline[temp];
//             }
//             otemp = 0;
//             sscanf(recuid,"%d",&attr[3]);
//         }

//         if(type == 1)
//         {
//             int otemp = 0;
//             int namebegin,nameend;
//             for(int i = 0;;i++)
//             {
//                 if(curline[i]=='/')
//                 {
//                     nameend = i - 1;
//                     break;
//                 }
//                 if(curline[i-1]==' '&&curline[i]!=' ')
//                 {
//                     namebegin = i;
//                 }
//             }
//             char* recdirname = (char*)malloc((nameend - namebegin + 1)*sizeof(char));
//             for(int temp = namebegin;temp < nameend + 1;temp++)
//             {
//                 recdirname[otemp++] = curline[temp];
//             }
//             mkdir(recdirname,attr[1]);
//         }
//         if(type == 0)
//         {
//             int otemp = 0;
//             int namebegin,nameend;
//             for(int i = 0;;i++)
//             {
//                 if(curline[i-1]==' '&&curline[i]!=' ')
//                 {
//                     namebegin = i;
//                 }
//                 if(curline[i]!=' '&&curline[i+1]==' ')
//                 {
//                     nameend = i;
//                     break;
//                 }
//             }
//             char* recfilename = (char*)malloc((nameend - namebegin + 1)*sizeof(char));
//             for(int temp = namebegin;temp < nameend + 1;temp++)
//             {
//                 recfilename[otemp++] = curline[temp];
//             }
//             int fd = creat(recfilename,FILE_MODE);
//         }
//     }
// }