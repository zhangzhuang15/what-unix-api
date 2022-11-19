// #include <sys/wait.h>
// pid_t waitpid(pid_t pid, int* statloc, int option)
// 等待一个子进程终止
// 当子进程终止时，内核会发送SIGCHLD信号给当前进程， waitpid 函数就是用来接受
// 该信号，捕捉子进程的终止码和pid， 其内部实现可能使用了 sigaction 函数，这个
// 函数提供了信号回掉函数，函数参数包含了终止码、进程ID在内的更多信息。
//
// pid- 子进程ID
//      pid == -1 等待任意子进程
//      pid > 0 等待指定的子进程
//      pid == 0 等待进程组ID等于调用本函数进程的进程组ID的任一子进程
//      pid < -1 等待进程组ID等于 pid 绝对值的任一子进程
//
// statloc- 接收子进程的终止码
// option- 配置项，控制 waitpid 的执行， 可以是如下宏的 | 运算的结果，或者是 0
//         WCONTINUED - 如果操作系统支持作业控制，那么由pid指定的子进程在停止后继续执行，但其状态
//                      没有报送给父进程，则返回其状态
//
//         WNOHANG - 由pid指定的子进程无法立即可用，则 waitpid 不阻塞，直接返回0
//
//         WUNTRACED - 如果操作系统支持作业控制，那么由pid指定的子进程在停止后, 没有报送过状态给父
//                     进程，则返回其状态。
//                     WIFSTOPPED(statloc) 可以判断子进程是否停止
//
// 成功时，返回子进程ID，失败时返回 -1

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main() {


    pid_t child = fork();

    if (child < 0) {
        printf("fork error! \n");

    } else if (child > 0) { // 父进程
        int result = 0;
        waitpid(child, &result, 0);
        // 换成非阻塞的版本看看吧
        // wait(child, &result, WNOHANG);
        printf("exit code: %d\n", WEXITSTATUS(result));
    } else {
        // 子进程
        printf("子进程结束\n");
        _exit(30);
    }
}