// #include <sys/uio.h>
// ssize_t readv(int fd, const struct iovec *iov, int iovcnt)
// 从 fd 指定的文件中读取数据到多个内存区
//
// fd-文件描述符
// iov-struct iovec 数组
// iovcnt-struct iovec 数组长度

#include <sys/uio.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
/*
   在I/O读写操作中，还有一个scatter读和gather写的概念。
   在Java语言中，这两个操作已经被实现在Channel对象的接口
   中了，可是它的底层是怎么回事呢？这就是本例程要向你展示的
   底层内容。使用readv和writev底层库函数实现scatter读，
   gather写。
   
   scatter读: 从数据源中读取数据，并将这些数据
   拷贝到多个用户空间缓存区中，值得强调的是，这个过程遵循 一个
   缓冲区存储满了，再存储下一个缓存区的原则。
*/

int main() {
    // 准备内存区
    char buffer_1[11], buffer_2[21];

    // 准备iovec数组，设置好存储区的地址和大小
    struct iovec iov[2];
    iov[0].iov_base = buffer_1;
    iov[0].iov_len = sizeof(buffer_1) - 1;
    iov[1].iov_base = buffer_2;
    iov[1].iov_len = sizeof(buffer_2) - 1;

    // 准备文件
    int fd = open("./test.txt", O_RDONLY, S_IRUSR);
    if (fd < 0) {
        perror("文件无法打开");
        return -1;
    }

    // 读取数据
    ssize_t num = readv(fd, iov, sizeof(iov)/sizeof(struct iovec));
    if (num < 0) {
        perror("读取数据失败");
        return -1;
    }

    printf("读取数据%ld 字节\n", num);


    // 给内存区设置字符串截止符号
    buffer_1[10] = '\0';
    buffer_2[20] = '\0';

    // 展示读取到的数据
    printf("buffer_1: %s\n", buffer_1);
    printf("buffer_2: %s\n", buffer_2);
    
    close(fd);

    return 0;
}

