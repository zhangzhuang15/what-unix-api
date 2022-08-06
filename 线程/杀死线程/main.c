#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

// 向线程t发送信号
// int pthread_kill(pthread_t t, int sig)
// sig 信号，记录于 <signal.h> 中
//
// 成功返回 0， 失败返回错误码 ESRCH (t 不合法) EINVAL（sig不合法） ENOTSUP（t并没有被pthread_create设置）

// 设置线程的信号屏蔽字
// int pthread_sigmask(int how, 
//                     sigset_t* set, 
//                     sigset_t* oset)
// how: SIG_BLOCK
//      SIG_UNBLOCK
//      SIG_SETMASK
// set: 新的信号位图， sigset_t 定义于 <signal.h>
// oset: 上次注册的信号位图， 一般设置为NULL 
//
// 成功返回 0， 失败返回错误码

void handler(int sig) {
    if (sig == SIGALRM) {
        printf("dont deal with SIGALRM\n");
    }
    if (sig == SIGKILL) {
        printf("receive SIGKILL, going to exit\n");
    }
    if (sig == SIGINT) {
        printf("you touch contrl+C\n");
    }
}

void* work(void* arg) {
    printf("welcome to child thread world\n");
    
    sigset_t set;
    memset(&set, 0, sizeof(set));
    sigaddset(&set, SIGALRM);
    
    // 表示线程对 set 中的信号进行屏蔽, 不去处理这些信号，
    // SIG_BLOCK 是在现有的线程屏蔽集合中增加新的屏蔽信号；
    // SIG_UNBLOCK 是在现有的线程屏蔽集合中删除屏蔽信号；
    // SIG_SETMASK 是将现有的线程屏蔽集合直接替换；
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    // 线程在执行完信号函数 handler 后，就会结束，不会继续阻塞直到15s。
    sleep(15);

    return 0;
}


int main() {
    pthread_t t;
   
    // 信号位图
    sigset_t s;
    memset(&s, 0, sizeof(s));
    // 信号加入到位图中
    sigaddset(&s, SIGALRM);
    sigaddset(&s, SIGKILL);
    sigaddset(&s, SIGINT);

    struct sigaction action;
    // 表示在信号处理函数执行中，不会发生信号位图s中信号的中断。
    // 主线程如果收到信号位图s中的信号，handler还是要执行的。
    action.sa_mask = s;
    action.__sigaction_u.__sa_handler = handler;
    // 向当前进程注册信号和信号处理
    sigaction(SIGALRM, &action, NULL); 
    sigaction(SIGINT, &action, NULL);

    pthread_create(&t, NULL, work, NULL);

    sleep(2);

    // ALRM 信号不会被子线程处理！
    pthread_kill(t, SIGALRM);

    pthread_kill(t, SIGINT);

    pthread_join(t, NULL);

    // 主线程中产生信号中断，在信号处理函数 handler 执行后，
    // 会回到主线程中继续执行。

    printf("child thread is dead\n");

    return 0;
}

