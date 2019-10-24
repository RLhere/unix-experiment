/*
 * @Description: 
 * @Version: 2.0
 * @Author: Kevin Liu
 * @Date: 2019-10-23 16:00:50
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-24 14:04:22
 */
#include"apue.h"
#include"my_err.h"

void f(void)
{
    printf("1\n");
}

void f1(void)
{
    printf("2\n");
}

void main(void)
{
    int ff,ff1;
    ff = atexit(f);
    ff1 = atexit(f1);
    printf("%d  %d\n",ff,ff1);
}
