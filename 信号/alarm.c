// #include <unistd.h>
// unsigned int alarm(unsigned int seconds)
// 设置闹钟信号，超过 seconds 秒后，SIGALRM 触发
// 
// seconds - 超时设定时间
//           0 - 取消上一次未触发的 ALARM 信号
//
// 成功时，返回 0 或者 上次闹钟信号剩余的秒数
// 比如上一次设定 10s， 3s 后调用本函数设置一次，将返回 7

