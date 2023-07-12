// #include <unistd.h>
// pid_t tcgetpgrp(int fd)
// 返回一个终端对应的前台进程组id
//
// fd - 终端设备的文件描述符
//
// 成功，返回前台进程组ID； 失败，返回-1
//
// 注意：
//  前台进程组，后台进程组，是支持作业控制的 shell 区分的，
//  内核只知道进程组，只知道当终端信号产生时，要发送给哪个
//  进程组，内核没有前台进程组、后台进程组的概念。shell
//  程序会管理后台进程组。

#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pgid = tcgetpgrp(STDOUT_FILENO);

    if (pgid < 0) {
        printf("tcgetpgrp failed\n");
    } else {
        printf("pgrp: %d\n", pgid);
    }

    return 0;
}