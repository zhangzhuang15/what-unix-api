// #include <unistd.h>
// pid_t fork(void)
// 创建子进程
//
// 成功时，子进程中返回0，父进程返回子进程ID
// 失败时，返回-1
//
// 子进程会继承父进程的
// 实际用户ID 实际组ID 有效用户ID 有效组ID
// 附属组ID
// 进程组ID
// 会话ID
// 控制终端
// 设置用户ID标志和设置组ID标志
// 当前工作目录
// 根目录
// 文件模式创建屏蔽字
// 信号屏蔽和安排
// 对任一打开文件描述符的执行时关闭标志（close-on-exec）
// 环境变量
// 共享存储段
// 资源限制
// 存储映像
// 文件描述符（文件表将共享）
//
// 子进程：
//   不继承父进程设置的文件锁
//   未处理闹钟被清除
//   未处理信号集为空集
//   tms_utime tms_stime tms_cutime tms_ustime设置为0


#include <unistd.h>
#include <stdio.h>

int main() {
    printf("main process\n");
    int score = 10;
    pid_t id = fork();

    if (id == 0) {
        printf("child process \n");
        score = 100;
    } else {
        printf("print in main process\n");
        sleep(5);
        // 父子进程空间独立，score依旧是10
        printf("score: %d\n", score);
    }
    return 0;
}