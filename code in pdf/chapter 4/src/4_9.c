/*
 * @Description: Example ofumaskfunction
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-11-09 00:18:07
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-11-09 00:19:09
 */
#include "apue.h"
#include <fcntl.h>
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
int main(void)
{
    umask(0);
    if (creat("foo", RWRWRW) < 0)
        err_sys("creat error for foo");
    
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("bar", RWRWRW) < 0)
        err_sys("creat error for bar");
        
    exit(0);
}