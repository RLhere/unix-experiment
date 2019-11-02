/*
 * @Description: Copy standardinput to standardoutput
 * @Version: 1.0
 * @Author: Kevin Liu
 * @Date: 2019-11-02 00:14:40
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-11-02 00:16:26
 */
#include "apue.h"
#define BUFFSIZE    4096
int
main(void)
{
    int     n;
    char    buf[BUFFSIZE];
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");
    
    if (n < 0)
        err_sys("read error");
        
    exit(0);
}