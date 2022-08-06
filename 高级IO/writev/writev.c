// #include <sys/uio.h>
// ssize_t writev(int fd, const struct iovec *iov, int iovcnt)
// 将多个内存区的数据写入到fd表示的文件中
//
// fd-文件描述符
// iov- struct iovec 数组地址
// iovcnt- struct iovec 数组长度
// 
// 返回写入的字节数
//
// 内存区写入顺序和 iov数组的顺序保持一致


// gather写: 把用户空间多个缓存区中的内容集中写入到输出源中。
// 多个缓存区之间存储在先后顺序，写入的时候按照这个次序写入。

#include <sys/uio.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main() {

    // 准备两个内存区
    char buff_1[10], buff_2[20];

    // 准备数据
    memcpy(buff_1, "hello world", sizeof(buff_1));
    memcpy(buff_2, "miss you very much baby", sizeof(buff_2));

    // 准备 struct iovec 数组， 设置存储区的地址和大小
    struct iovec iov[2];
    iov[0].iov_base = buff_1;
    iov[0].iov_len = sizeof(buff_1);
    iov[1].iov_base = buff_2;
    iov[1].iov_len = sizeof(buff_2);

    // 准备文件
    int fd = open("./test.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        // #include <stdio.h>
        perror("文件无法打开");
        return -1;
    }

    // 写入数据
    ssize_t num = writev(fd, iov, sizeof(iov)/sizeof(struct iovec));

    printf("写入%ld字节 \n", num);

    // #include <unistd.h>
    close(fd);

    return 0;
}