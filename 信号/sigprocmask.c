// #include <signal.h>
// int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset)
// 根据信号集，调整进程的信号屏蔽字
//
// how - SIG_BLOCK， 向进程的信号屏蔽字中加入信号集 set 中的信号
//       SIG_UNBLOCK, 从进程的信号屏蔽字中删除信号集 set 中的信号
//       SIG_SETMASK, 设置进程的信号屏蔽字为信号集 set 中的信号
//
// set - 信号集指针
// oldset - 进程当前信号屏蔽字中的信号将存储于集合oldset里
//
// 成功返回 0， 失败返回 -1
//
// 注意： 用于单线程进程