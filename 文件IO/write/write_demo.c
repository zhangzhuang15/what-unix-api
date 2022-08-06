#include <stdio.h>

// strlen 函数所必需
#include <string.h>

// write close 函数所必需
#include <unistd.h>

// open 函数所必需
#include <fcntl.h>

// 将 buff 的 count 个字节数据写入到 fd 中
// ssize_t write(int fd, void *buff, size_t count)
// 成功时，返回写入的字节数；
// 失败时，返回-1
//
// count  控制写入的字节数，buff是开辟的一块内存，count不能超过这块内存的大小

int main() {
    int fd = open("./demo.txt", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

    char buff[1024] = "还可以吧\n今天几号?\n哦, 2022-03-26。\n找工作真难呀"; // 最多写入1024个字节


    ssize_t bytes = write(fd, buff, strlen(buff));
    printf("buff有 1024byte 大小, 实际写入了 %zdbytes\n", bytes);
    close(fd);
}

// 将 25 行的 strlen(buff) 改为 1024，
// 再次运行后，程序不报错，但是 demo.txt 将无法按照 .txt 展示出来。