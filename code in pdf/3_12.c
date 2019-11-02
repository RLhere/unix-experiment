/*
 * @Description: 
 * @Version: 
 * @Author: Kevin Liu
 * @Date: 2019-11-02 14:19:53
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-11-02 15:22:40
 */
#include "apue.h"
#include <fcntl.h>
TODO: MAKE THE FILE COMPILED

void
set_fl(int fd, int flags) /* flags are file status flags to turn on */
{
    int     val;

    if((val = fcntl(fd, F_GETFL,0)) < 0)
        err_sys("fcntl F_GETFL error");

    val |= flags;       /*  turn on flags */

    if(fcntl(fd, F_SETFL, val) < 0)
        err_sys("fcntl F_SETFL error");
}