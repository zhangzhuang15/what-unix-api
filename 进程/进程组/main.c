// #include <unistd.h>
// int setpgid(pid_t pid, pid_t pgid)
// 将一个进程加入到一个进程组
//
// pid- 进程ID
// pgid- 进程组ID
//
//      如果 pid == pgid, 则 pid 成为新的进程组组长
//      如果 pid == 0, 则使用 调用者进程ID
//      如果 pgid == 0， 则使用 pid 作为进程组ID
//
// 一个进程只能为自己或者子进程设置进程组ID，如果子进程执行了
// exec函数了，那么进程就无法更改子进程的进程组ID了。
//
//
// 成功时，返回0， 失败时，返回-1

// 进程组？
// 当一个进程执行 fork 后，就会创建一个子进程，此时 进程和子进程
// 位于同一个进程组中，进程组组长就是进程本身，以它的进程ID作为
// 进程组ID。

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

   pid_t child = fork();

   if (child < 0) {
     perror("fork error!");

   } else if (child > 0) {
     printf("child PID: %d\n", child);
     printf("主进程PID： %d\n", getpid());
     printf("主进程进程组ID: %d\n", getpgrp());
     sleep(2);
     setpgid(child, child);
     wait(NULL);
   } else {
    printf("子进程组ID 1: %d\n", getpgrp());
    sleep(10);
    printf("子进程组ID 2:  %d\n", getpgrp());
    exit(0);
   }
}