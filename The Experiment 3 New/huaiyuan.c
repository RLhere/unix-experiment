/*
 * @Description: the back part of the file backup
 * @Version: 2.0
 * @Author: Kevin Liu
 * @Date: 2019-10-29 22:52:21
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-30 23:45:54
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

    /**
     * @description: get attr from every singlelines
     * @param {pointers to all single lines, Ftypes 1 mean dir and 0 mean regular file, indent which links to the change of dir, linenumber } 
     * @return: change value through pointer
     * @author: Kevin Liu
     */
    void setattr(char ** ALLines, unsigned short * Ftype,short ** indent, int * linenumber,int * Len);
    unsigned short * Ftype = (unsigned short *)malloc((*linenumber)*sizeof(unsigned short));
    int * Len = (int *)malloc((*linenumber)*sizeof(int));
    short ** indent = (short **)malloc((*linenumber)*sizeof(short*));
    for(int i = 0;i < (*linenumber);i++)
    {
        indent[i] = (short*)malloc(3*sizeof(short));
        Len[i] = length[i];
    }
    setattr(ALLines,Ftype,indent,linenumber,Len);
    Ftype[0] = 1;
    // for(int i = 0;i < (*linenumber);i++)
    // {
    //     printf("%d\n",Ftype[i]);
    // }

    //以上getattr获取了两样东西一个该行代表文件的类型，另一个是该行对于上一行
    //的层次关系标识符

    /**
     * @description: get gid uid  where the filename begin and how long it is and the size of the content and where the content begin
     * @param {lines,file type which lines represent,file gid, filenamelenth, filename where begin, file uid, filesize, where file content begin} 
     * @return: change values through pointers
     * @author: Kevin Liu
     */
    void getattr(char ** ALLines, unsigned short * Ftype,char ** Gid,int * FnameLen,int * Fnamebegin,char ** Uid,unsigned short * Fsize,unsigned short * ContentBegin,int * linenumber,int * Len,char ** Mode);
    char ** Gid = (char **)malloc((*linenumber)*sizeof(char *));
    char ** Uid = (char **)malloc((*linenumber)*sizeof(char *));
    int * FnameLen = (int *)malloc((*linenumber)*sizeof(int));
    int * Fnamebegin = (int *)malloc((*linenumber)*sizeof(int));
    char ** Mode = (char **)malloc((*linenumber)*sizeof(char *));
    unsigned short * Fsize = (unsigned short *)malloc((*linenumber)*sizeof(unsigned short));
    unsigned short * ContentBegin = (unsigned short *)malloc((*linenumber)*sizeof(unsigned short));
    for(int i = 0;i < (*linenumber);i++)
    {
        Mode[i] = (char *)malloc(5*sizeof(char));
        Gid[i] = (char *)malloc(4*sizeof(char));
        Uid[i] = (char *)malloc(4*sizeof(char));
    }
    getattr(ALLines, Ftype, Gid, FnameLen,Fnamebegin,Uid,Fsize,ContentBegin,linenumber,Len,Mode);
    Fsize[(*linenumber) - 1] = 0;
    Fsize[(*linenumber) - 2] = 0;

    void getattri(char ** ALLines, unsigned short * Ftype,char ** Gid,int * FnameLen,int * Fnamebegin,char ** Uid,unsigned short * Fsize,unsigned short * ContentBegin,int * linenumber,int * Len,char ** Mode);
    getattri(ALLines, Ftype, Gid, FnameLen,Fnamebegin,Uid,Fsize,ContentBegin,linenumber,Len,Mode);
    // debug
    for(int i = 0;i < (*linenumber);i++)
    {
        Uid[i][4] = '\0';
        Gid[i][4] = '\0';
        // printf("%d\t%d\t%d\n",i+1,Fnamebegin[i],FnameLen[i]);
        printf("%d\t%hd\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",i+1,Fsize[i],Gid[i],Uid[i],Mode[i],Ftype[i],Fnamebegin[i],FnameLen[i],indent[i][2],ContentBegin[i]);
    }

    char** name    = (char**)malloc((*linenumber)*sizeof(char*));
    char** content = (char**)malloc((*linenumber)*sizeof(char*));
    for(int i = 0;i < (*linenumber);i++)
    {
        content[i] = (char*)malloc(Fsize[i]*sizeof(char));
        name[i]    = (char*)malloc(FnameLen[i]*sizeof(char));
    }
    

    for(int i = 1; i < (*linenumber) - 2;i++)
    {
        if(indent[i][2] == 1)
        {
            if(Ftype[i]==1)
            {
                
            }
            else
            {
                /* code */
            }
            
        }
        else if(indent[i][2] == 0)
        {
            if(Ftype[i]==1)
            {

            }
            else
            {
                /* code */
            }
        }
        else
        {
            if(Ftype[i]==1)
            {

            }
            else
            {
                /* code */
            }
            
        }
        
    }

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

void setattr(char ** ALLines, unsigned short * Ftype,short ** indent,int * linenumber,int * Len)
{
    for(int i = 0;i < (*linenumber);i++)
    {
        indent[i][0] = 0;
        indent[i][1] = 0;
        indent[i][2] = 0;
        for(int j = 0;j < Len[i]; j++)
        {
            if(ALLines[i][0]==' ')
            {
                if(i != 0 && i != 1)
                {
                    indent[i][1] = 0;
                    indent[i][0] = indent[i-1][1];
                }else if(i == 1){
                    indent[i][1] = 0;
                    indent[i][0] = 0;
                }else{
                    indent[i][0] = 0;
                    indent[i][1] = 0;
                }
            }
            if(ALLines[i][4]==' ')
            {
                if(i != 0 && i != 1)
                {
                    indent[i][1] = 1;
                    indent[i][0] = indent[i-1][1];
                }else if(i == 1){
                    indent[i][1] = 0;
                    indent[i][0] = 0;
                }else{
                    indent[i][0] = 0;
                    indent[i][1] = 0;
                }
            }
            if(ALLines[i][8]==' ')
            {
                if(i != 0 && i != 1)
                {
                    indent[i][1] = 2;
                    indent[i][0] = indent[i-1][1];
                }else if(i == 1){
                    indent[i][1] = 0;
                    indent[i][0] = 0;
                }else{
                    indent[i][0] = 0;
                    indent[i][1] = 0;
                }
            }
        }
        indent[i][2] = indent[i][1] - indent[i][0];
        for(int j = 0;j < Len[i]; j++)
        {
            if(ALLines[i][j] == '/')
            {
                Ftype[i] = 1;
                break;
            }
            else
            {
                Ftype[i] = 0;
            }
        }
    }
}

void getattr(char ** ALLines, unsigned short * Ftype,char ** Gid,int * FnameLen,int * Fnamebegin,char ** Uid,unsigned short * Fsize,unsigned short * ContentBegin, int * linenumber, int * Len,char ** Mode)
{
    for(int i = 0; i < *linenumber;i++)
    {
        if(i == 0)
        {
            int end;
            int begin;
            int times = 0;
            for(int j = Len[i] - 1; j > -1; j--)
            {
                if(ALLines[i][j] == '/')
                {
                    times++;
                    if(times == 1)
                    {
                        end = i - 1;
                    }
                    if(times == 2)
                    {
                        begin = i + 1;
                    }
                }
                Fnamebegin[i] = begin;
                FnameLen[i] = end - begin + 1;
            }
            for(int j = 0; j < Len[i]; j++)
            {
                if(ALLines[i][j] == 'g' && ALLines[i][j+1] == 'i' && ALLines[i][j+2] == 'd' && ALLines[i][j+3] == ':')
                {
                    int k = 0;
                    for(int l = j + 4;k < 4;k++,l++)
                    {
                        Gid[i][k] = ALLines[i][l];
                    } 
                }
                if(ALLines[i][j] == 'u' && ALLines[i][j+1] == 'i' && ALLines[i][j+2] == 'd' && ALLines[i][j+3] == ':')
                {
                    int k = 0;
                    for(int l = j + 4;k < 4;k++,l++)
                    {
                        Uid[i][k] = ALLines[i][l];
                    } 
                }
                if(ALLines[i][j] == 'm' && ALLines[i][j+1] == 'o' && ALLines[i][j+2] == 'd' && ALLines[i][j+3] == 'e' && ALLines[i][j + 4] == ':')
                {
                    int k = 0;
                    for(int l = j + 5;k < 5;k++,l++)
                    {
                        Mode[i][k] = ALLines[i][l];
                    } 
                }
                if(ALLines[i][j] == 's' && ALLines[i][j+1] == 'i' && ALLines[i][j+2] == 'z' && ALLines[i][j+3] == 'e' && ALLines[i][j + 4] == ':')
                {
                    int len = 1;
                    int index = j + 4 + len;
                    for(;;)
                    {
                        if(ALLines[i][index] != ' ')
                        {
                            len++;
                            index = j + 4 + len;
                        }else{
                            break;
                        }
                    }
                    char * cSize = (char*)malloc(len*sizeof(char));
                    int k = 0;
                    for(int l = j + 5;k < len;k++,l++)
                    {
                        cSize[k] = ALLines[i][l];
                    }
                    sscanf(cSize,"%hd",&Fsize[i]);
                }
            }
        }
        else
        {
            if(Ftype[i] == 1)
            {
                for(int j = 0; j < Len[i]; j++)
                {
                    int end;
                    if(ALLines[i][j] == '/')
                    {
                        end = j - 1;
                    }
                    for(int m = end;;m--)
                    {
                        if(ALLines[i][m] == ' ')
                        {
                            Fnamebegin[i] = m + 1;
                            FnameLen[i] = end - Fnamebegin[i] + 1; 
                            break;
                        }
                    }
                    if(ALLines[i][j] == 'g' && ALLines[i][j+1] == 'i' && ALLines[i][j+2] == 'd' && ALLines[i][j+3] == ':')
                    {
                        int k = 0;
                        for(int l = j + 4;k < 4;k++,l++)
                        {
                            Gid[i][k] = ALLines[i][l];
                        } 
                    }
                    if(ALLines[i][j] == 'u' && ALLines[i][j+1] == 'i' && ALLines[i][j+2] == 'd' && ALLines[i][j+3] == ':')
                    {
                        int k = 0;
                        for(int l = j + 4;k < 4;k++,l++)
                        {
                            Uid[i][k] = ALLines[i][l];
                        } 
                    }
                    if(ALLines[i][j] == 'm' && ALLines[i][j+1] == 'o' && ALLines[i][j+2] == 'd' && ALLines[i][j+3] == 'e' && ALLines[i][j + 4] == ':')
                    {
                        int k = 0;
                        for(int l = j + 5;k < 5;k++,l++)
                        {
                            Mode[i][k] = ALLines[i][l];
                        } 
                    }
                    if(ALLines[i][j] == 's' && ALLines[i][j+1] == 'i' && ALLines[i][j+2] == 'z' && ALLines[i][j+3] == 'e' && ALLines[i][j + 4] == ':')
                    {
                        int len = 1;
                        int index = j + 4 + len;
                        for(;;)
                        {
                            if(ALLines[i][index] != ' ')
                            {
                                len++;
                                index = j + 4 + len;
                            }else{
                                break;
                            }
                        }
                        char * cSize = (char*)malloc(len*sizeof(char));
                        int k = 0;
                        for(int l = j + 5;k < len;k++,l++)
                        {
                            cSize[k] = ALLines[i][l];
                        }
                        sscanf(cSize,"%hd",&Fsize[i]);
                    }
                }
            }
            if(Ftype[i] == 0)
            {
                for(int j = 0; j < Len[i]; j++)
                {
                    int end;
                    if(ALLines[i][j] == '/')
                    {
                        end = j - 1;
                    }
                    for(int m = end;;m--)
                    {
                        if(ALLines[i][m] == ' ')
                        {
                            Fnamebegin[i] = m + 1;
                            FnameLen[i] = end - Fnamebegin[i] + 1; 
                            break;
                        }
                    }
                    if(ALLines[i][j] == 'g' && ALLines[i][j+1] == 'i' && ALLines[i][j+2] == 'd' && ALLines[i][j+3] == ':')
                    {
                        int k = 0;
                        for(int l = j + 4;k < 4;k++,l++)
                        {
                            Gid[i][k] = ALLines[i][l];
                        } 
                    }
                    if(ALLines[i][j] == 'u' && ALLines[i][j+1] == 'i' && ALLines[i][j+2] == 'd' && ALLines[i][j+3] == ':')
                    {
                        int k = 0;
                        for(int l = j + 4;k < 4;k++,l++)
                        {
                            Uid[i][k] = ALLines[i][l];
                        } 
                    }
                    if(ALLines[i][j] == 'm' && ALLines[i][j+1] == 'o' && ALLines[i][j+2] == 'd' && ALLines[i][j+3] == 'e' && ALLines[i][j + 4] == ':')
                    {
                        int k = 0;
                        for(int l = j + 5;k < 5;k++,l++)
                        {
                            Mode[i][k] = ALLines[i][l];
                        } 
                    }
                    if(ALLines[i][j] == 's' && ALLines[i][j+1] == 'i' && ALLines[i][j+2] == 'z' && ALLines[i][j+3] == 'e' && ALLines[i][j + 4] == ':')
                    {
                        int len = 1;
                        int index = j + 4 + len;
                        for(;;)
                        {
                            if(ALLines[i][index] != ' ')
                            {
                                len++;
                                index = j + 4 + len;
                            }else{
                                break;
                            }
                        }
                        char * cSize = (char*)malloc(len*sizeof(char));
                        int k = 0;
                        for(int l = j + 5;k < len;k++,l++)
                        {
                            cSize[k] = ALLines[i][l];
                        }
                        sscanf(cSize,"%hd",&Fsize[i]);
                    }
                }
            }
        }        
    }
}

void getattri(char ** ALLines, unsigned short * Ftype,char ** Gid,int * FnameLen,int * Fnamebegin,char ** Uid,unsigned short * Fsize,unsigned short * ContentBegin,int * linenumber,int * Len,char ** Mode)
{
    FnameLen[0] = 0;
    for(int i = 0;i < (*linenumber);i++)
    {
        if(i == 0)
        {
            int time = 0;
            int temp[2];
            for(int j = Len[i]; j >= 0; j-- )
            {
                if(ALLines[i][j] == '/')
                {
                    time++;
                    temp[time-1] = j;
                    if(time==2)
                    {
                        break;
                    }
                }
            }
            Fnamebegin[0] = temp[1] + 1;
            FnameLen[0] = temp[0] - temp[1] - 1;
        }
        if(Ftype[i] == 0)
        {
            for(int j = 0; j < Len[i];j++)
            {
                if(ALLines[i][j] != ' ' && ALLines[i][j + 1] == '\t')
                {
                    FnameLen[i] = j - Fnamebegin[i] + 1;
                    break;
                }
            }

            for(int j = 0; j < Len[i];j++)
            {
                if(ALLines[i][j]=='c'&&ALLines[i][j+1]=='o'&&ALLines[i][j+2]=='n'&&ALLines[i][j+3]=='t'&&ALLines[i][j+4]=='e'&&ALLines[i][j+5]=='n'&&ALLines[i][j+6]=='t'&&ALLines[i][j+7]==':')
                {
                    ContentBegin[i] = j+8;
                }
            }
        }
    }
}