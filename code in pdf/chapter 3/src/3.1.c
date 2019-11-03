/*
 * @Description: Test whether standard input is capable of seeking
 * @Version: 1.0
 * @Author: Kevin Liu
 * @Date: 2019-11-02 00:04:22
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-11-02 00:10:45
 */
#include "./apue.h"

int main(int argc, char const *argv[])
{
    if(lseek(STDIN_FILENO,0,SEEK_CUR) == -1)
        printf("cannot seek\n");
    else
    {
        printf("seek OK\n");
    }
      
    exit(0);
}
