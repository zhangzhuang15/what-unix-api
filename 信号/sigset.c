// #include <signal.h>
// int sigemptyset(sigset_t *set)
// 清空信号集合中的信号
//
// set - 信号集合指针
//
// 成功返回 0， 失败返回 -1


// #include <signal.h>
// int sigfillset(sigset_t *set)
// 将所有的信号加入信号集
//
// set - 信号集合指针
//
// 成功返回 0， 失败返回 -1


// #include <signal.h>
// int sigaddset(sigset_t *set, int signo)
// 将信号signo加入信号集
//
// set - 信号集合指针
// signo - 信号码值
//
// 成功返回 0， 失败返回 -1


// #include <signal.h>
// int sigdelset(sigset_t *set, int signo)
// 从信号集合中删除信号 signo
//
// set - 信号集合指针
// signo - 信号码值
//
// 成功返回 0， 失败返回 -1


// #include <signal.h>
// int sigismember(sigset_t *set, int signo)
// 信号 signo 是否在信号集合里
//
// set - 信号集合指针
// signo - 信号码值
//
// 成功返回 0， 失败返回 -1