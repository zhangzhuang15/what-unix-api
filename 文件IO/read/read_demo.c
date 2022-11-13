// #include <unistd.h>
// ssize_t read(int fd, void *buff, size_t count)
// 从 fd 中读取数据，存入到 buff 中
//
// buff  - 数据存储空间起始内存地址
// count - 数据存储空间大小，单位字节。
//         buff是一个指针，可指针所指的内存有多大并不知道，需要用count变量指明。
//
// 成功时，返回 读取到的字节数；
// 文件全部读取完毕时， 返回 0； 读取大数据时，要一小块一小块读取，啥时候大数据都读完了呢，返回 0 的时候。
// 失败时，返回 -1；
//
// 没有设置 non-block 情况下，open 一个文件，read 文件时，会出现阻塞：
// 1. 某些文件类型的数据不存在，read会阻塞， 比如 read 管道、终端设备、网络设备；
// 2. read已经加上强制性记录锁的文件，会阻塞；

#include <stdio.h>

// memset函数所必需
#include <string.h>

// read close 函数所必需
#include <unistd.h>

// open函数所必需
#include <fcntl.h>





int main() {
    int fd = open("./demo.txt", O_RDONLY);
    char buff[1024];
    memset(buff, 0, 1024);
    ssize_t bytes = read(fd, buff, 1024);
    switch (bytes)
    {
    case 0:
        printf("数据都读干净了\n");
        break;
    case -1:
        printf("读取数据发生了错误\n");
        break;
    default:
        printf("读取数据%zd bytes\n", bytes);
    }
    printf("读取到数据: %s\n", buff);

    close(fd);
}