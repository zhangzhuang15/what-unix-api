// #include <stdlib.h>
// void exit(int status)
// 进程主动退出，将状态码传送给父进程（如果有父进程的话）
//
// status- 进程退出的状态码
//
// 调用 exit 后， 会执行所有的进程终止程序，执行标准I/O清理程序，
// 之后执行系统函数 _exit, 切换到内核，将退出码 status 转换成终止码，
// 发送给父进程。


// #include <unistd.h>
// void _exit(int status)
// 进程主动退出，将状态码传送给父进程（如果有父进程的话），
// 不会执行进程终止程序和进程信号函数。


// 为什么会有退出码和终止码？
// 进程结束分为正常结束，异常结束。退出码是正常结束中发生的，可在内核
// 眼里，只能看到进程结束，看不到进程是正常结束还是异常结束，因此为了
// 将两种情况统一，采用终止码。用户可以使用宏，从终止码中获取到退出码。

// 进程结束有哪些情况？
// 正常结束：
// 1. 执行 return
// 2. 执行 exit， _exit 函数
// 3. 最后一个线程return
// 4. 最后一个线程执行 pthread_exit
//
// 异常情况：
// 1. 执行abort函数
// 2. 收到一个信号
// 3. 最后一个线程对取消请求作出响应

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    pid_t child;

    child = fork();

    if (child < 0) {
        perror("执行fork 发生错误");

    } else if (child > 0) { // 父进程
        int result;
        waitpid(child, &result, 0);
        printf("result: %d\n", result);
        printf("exit code: %d\n", WEXITSTATUS(result)); // 拿到真正的退出码

    } else { // 子进程
         printf("子进程退出了哈\n");
         exit(200);
    }
    return 0;
}