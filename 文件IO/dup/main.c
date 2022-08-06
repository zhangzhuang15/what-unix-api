// #include <unistd.h>
// int dup(int fd)
// 复制文件表
//
// fd-文件描述符
//
// 成功时，返回新的文件描述符, 该描述符是所有空闲的文件描述符中最小的
// 失败时， 返回 -1
//
// @example:
//  fd_1    --->   file
//
//  int fd_2 = dup(fd_1)
//
//  fd_1    --->   file  <---  fd_2

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    // 复制标准输出， 此时有两个文件描述符指向终端
    int fd = dup(STDOUT_FILENO);
    // 关闭默认的标准输出描述符
    close(STDOUT_FILENO);
    
    sleep(1);

    char buffer[] = "hello world, boy";
    ssize_t num = write(fd, buffer, sizeof(buffer));
    if (num < 0) {
        perror("写入数据失败");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}