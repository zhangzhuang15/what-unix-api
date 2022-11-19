// #include <sys/wait.h>
// pid_t wait(int *statloc)
// 等待任意一个子进程结束
//
// statloc-存储子进程终止状态码
// 
// 成功时，返回子进程ID，失败时，返回-1
//
// NOTICE: 
// 1. 父进程退出，子进程没有退出，子进程会被1号进程收养，成为孤儿进程；
// 2. 父进程没有退出，但没有等待子进程退出，一旦子进程退出，将成为僵尸进程，造成系统资源损耗；

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {

    pid_t child = fork();

    if (child < -1) {
        _exit(200);

    } else if (child == 0) {
        sleep(3);
        _exit(2);

    } else {
        printf("wait for child.....\n");
        int status = 0;
        pid_t c = wait(&status);
        
        if (c < -1) {
            perror("failed to call wait()");

        } else if (c == child) {
            printf("end code: %d\n", status);

            // 子进程正常退出
            if (WIFEXITED(status)) {
                printf("exit code: %d\n", WEXITSTATUS(status));

            // 子进程异常退出
            } else if (WIFSIGNALED(status)) {
                printf("abnormal termination, signal code: %d\n", WTERMSIG(status));
            }
        }
    }

}