// #include <signal.h>
// signal(int sig, void (*handler)(int))
// 给进程绑定一个信号处理函数
//
// sig-信号代号
// handler-信号处理函数
//
// 当信号发生时，产生中断，执行中断函数，之后再返回原来的代码处继续执行

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