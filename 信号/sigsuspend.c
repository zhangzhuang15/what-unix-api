// #include <signal.h>
// int sigsuspend(sigset_t *set)
// 设置当前进程的信号屏蔽字为信号集 set，并阻塞进程，直到进程收到一个信号
// 原子操作
//
// set - 信号集
//
// 返回 -1， errno 设置为 EINTR