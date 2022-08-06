// #include <fcntl.h>
// int fcntl(int fd, int cmd, ...)
// 对文件执行某个类型的操作
//
// fd-文件描述符
// cmd-操作命令
//     F_DUPFD  复制文件描述符
//     F_DUPFD_CLOEXEC 复制文件描述符
//     F_GETFD  获取文件描述符标志
//     F_SETFD  设置文件描述符标志
//     F_GETFL  获取文件状态标志，比如 O_RDWR
//     F_SETFL  设置文件状态标志
//     F_GETLK  获取记录锁
//     F_SETLK  设置记录锁
//     F_SETLKW  设置记录锁
//     F_GETOWN  获取异步IO所有权
//     F_SETOWN  设置异步IO所有权
// ...-额外参数
//
// 成功时，根据cmd不同，返回的值也不同
//   F_DUPFD F_DUPFD_CLOEXEC 返回新的文件描述符
//   F_GETFD F_GETFL  返回对应的标志，状态标志
//   F_GETOWN 返回进程ID
//   F_SETLKW F_GETLK 执行成功后，结果保存在额外参数中
// 失败时，返回-1