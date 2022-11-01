// #include <unistd.h>
// pid_t vfork()
// 创建一个子进程，该进程共享父进程的空间，并且当
// 子进程调用 exec 或 exit 后，父进程才会被调度执行

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    printf("main process\n");

    int score = 10;

    pid_t child = vfork();

    if (child == -1) {
        printf("failed to create child process");
        exit(0);
    }

    if (child == 0) {
       
        printf("child process score: %d\n", score);
        sleep(4);
        exit(0);

    } else {
        score = 50;
        printf("main process score: %d\n", score);

    }
}