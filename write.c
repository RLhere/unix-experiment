/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-11-28 20:15:01
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-11-28 20:17:23
 */
#include<stdio.h>

int main(int argc, char const *argv[])
{
    char buf[4096];
    for( int i = 0; i < 4096 ; i++ )
    {
        buf[i] = '.';
    }
    
    while(1)
    {
        printf("%s\n",buf);
    }
    

    return 0;
}
