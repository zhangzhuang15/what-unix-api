// #include <unistd.h>
// int pause(void)
// 阻塞调用进程
//
// 返回 -1， errno 设置为 EINTR
//
// 注意：
//   当执行信号处理函数（你设置的，或者系统定义的）并返回后，该函数才返回