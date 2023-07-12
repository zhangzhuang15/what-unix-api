// #include <signal.h>
// void (*signal(int sig, void (*handler)(int))) (int)
// 给进程绑定一个信号处理函数
//
// sig-信号代号
// handler-信号处理函数
//         设置为 SIG_IGN - 忽视信号
//         设置为 SIG_DFL - 执行系统对信号的默认处理
//
// 成功，返回之前的信号处理函数；失败，返回 SIG_ERR
//
// 注意：
// 1. 当信号发生时，产生中断，执行中断函数，之后再返回原来的代码处继续执行
// 2. 函数的定义可以拆解为如下方式理解：
//    typedef void handler(int);
//    handler *signal(int, handler);
//
//    当然也可以推导出来：
//    signal 和 * 号没有用括号作为一个整体，表示 signal 是函数，不是指向函数的指针；
//    signal 的函数入参，就是 int 和 handler;
//    注意看 * 和 handler 用一个括号包在了一起，表示 handler 是一个指向函数的指针，被指向的函数入参是 int， 返回值是 void；
//    那么 signal 的返回值是什么呢？
//    令 G = signal(int sig, void (*handler)(int))
//    得到 void (*G)(int)， 表示 G 是一个指向函数的指针，被指向的函数入参数 int， 返回值是 void；

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void interrupt_handler(int signum){
    printf("there is an interrupt!\n");
    FILE *fp;
    // #include <stdio.h>
    fp = fopen("signal_error.txt", "a+");
    fprintf(fp, "the signum is %d\n", signum);
    fputs("this text is modified by c, is cool!\n", fp);
    fclose(fp);
    // #include <stdlib.h>
    exit(0);
}

int main(){
    signal(SIGINT, interrupt_handler);
    while(1){
        // #include <unistd.h>
        sleep(1);
        printf("20210501\n");
    }
    return 0;
}