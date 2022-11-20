// #include <signal.h>
// int sigqueue(pid_t pid, int signo, const union sigval value)
// 给一个进程发送信号
// kill 的升级版
//
// pid - 进程ID
// signo - 信号码值
// value - 随信号发送过去的值
//       union sigval {
//         int sival_int;
//         void *sival_ptr;
//       }
//
// 成功返回 0， 失败返回 -1
//
// 注意：返回 -1时， errno 可能被设置为 EAGAIN, 表示信号排队已经满了