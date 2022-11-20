// #include <signal.h>
// int sigaction(int signo, const struct sigaction *restrict act, struct sigaction *restrict oldact)
// 设置信号的处理行为
// signal函数的升级版
//
// signo - 信号码值
// act   - 信号处理行为
//         struct sigaction {
//             void  (*sa_handler)(int);
//             sigset_t sa_mask;            执行信号处理函数时，屏蔽的信号
//             int sig_flags;               
//             void (*sa_sigaction)(int, siginfo_t *, void *);
//         }
//            
//         sig_flags 如果包含 SA_SIGINFO, 执行 sa_sigaction 指向的信号处理函数
//                   struct siginfo_t  {
//                      int si_signo;           信号码值
//                      int si_errno;
//                      int si_code;
//                      pid_t si_pid;           信号发送方的进程ID
//                      uid_t si_uid;           信号发送方进程的实际用户ID
//                      void  *si_addr;         引发信号的内存地址
//                      int   si_status;        进程退出码或者信号码值
//                      union sigval si_value;  应用层具体的值
//                   }
//                   如果信号是 SIGCHLD，会设置 si_pid si_uid si_status;
//                   如果信号是 SIGBUS SIGILL SIGFPE SIGSEGV, 会设置 si_addr si_errno
//                   对于 si_value, 请看 sigqueue.c 
// 
//                   sa_sigaction 最后一个参数 void* ，可以转化为 ucontext_t 使用，获取
//                   一些上下文信息，比如栈信息，信号屏蔽字等等
//
// oldact - 之前的信号处理行为
//
// 成功返回 0， 失败返回 -1