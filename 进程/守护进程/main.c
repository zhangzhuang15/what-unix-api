// 创建守护进程的步骤
// 1. fork子进程，关闭主进程
// 2. 子进程调用 setsid，开启新会话，成为进程组组长，会话首进程
// 3. 子进程调用umask关闭所有文件模式屏蔽字，防止子进程缺少某些文件权限
// [4]. 子进程关闭多余的文件（子进程会从父进程继承文件描述符）
// [5]. 子进程将当前工作目录，改为根目录
// 6. 子进程关闭标准输入、标准输出、标准错误
// 至此，子进程成为一个守护进程。
//
//
// 注： []表示非必需


// 查看守护进程
// 开启终端，执行 ps -efj, 观察输出
// tty 为 ？的，都是守护进程；
// 进程的启动命令用 [] 括起来的，是内核守护进程；
// 其余的是 用户守护进程；

// 我们编程实现的守护进程，其父进程是1号进程。


// #include <unistd.h>
// pid_t setsid(void)
// 创建新会话，令调用进程成为会话首进程
//
// 成功返回会话首进程ID，失败返回 -1
//
// 注意：
// 1. 如果调用进程是进程组组长，则调用失败；
// 2. 调用成功返回后，调用进程成为新会话首进程，成为一个新进程组组长，不会拥有控制终端；

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <fcntl.h>


int main() {
    // 来，开子进程
    pid_t child = fork();

    if (child < 0) {
        printf("fork failed\n");
        return -1;
    }

    // 父进程赶紧退出
    if (child > 0) {
        exit(0);
    }

    // 好了，子进程成了孤儿进程，还不是进程组组长

    // 清空文件创建屏蔽字，以后创建文件无阻碍了
    umask(0);

    // 走起，转身成为 会话首进程
    setsid();

    // 当前工作目录改为 根目录，防止文件系统中无法卸载子文件夹
    if (chdir("/") < 0) {
        exit(0);
    }

    // 获取文件描述符上限，关闭它们
    // 毕竟，都没控制终端了🐶
    struct rlimit r;
    if (getrlimit(RLIMIT_NOFILE, &r) < 0) {
        exit(0);
    };
    for(int fd = 0; fd < r.rlim_max; fd++) {
        close(fd);
    }

    // 开一个文件，写日志
    int fd = open("/Users/zhangzhuang/message.txt", O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        exit(0);
    }

    // 应该还有一部分信号处理逻辑，为了 demo 的简单性，暂时不加了；
    // 有关信号的处理，移步到 信号 章节

    char buffer[512];
    for (int j = 0; j < 20; j++) {
        if (sprintf(buffer, "hello world %d %d\n", j, fd) < 0) {
            close(fd);
            exit(0);
        };
        // 注意这里，写完之后，不会立即看到 日志文件
        write(fd, buffer, strlen(buffer));
        sleep(10);
    }
    close(fd);
    // 好啦，此时肯定能看到日志文件了
    return 0;
}

// 文件编译执行后，
// ps -efj     查看 ./main 的进程
// 之后隔一段时间查看日志文件吧
//
// kill -9 [./main的 pid] 就可以干掉进程了