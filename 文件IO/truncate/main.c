// #include <unistd.h>
// int truncate(const char *pathname, off_t length)
// 截断文件内容
//
// pathname-文件路径
// length-截断长度(单位：字节)，超过该长度的部分会被截断
//
// 成功返回0
// 失败返回-1

#include <fcntl.h>
#include <unistd.h>

int main() {
    // 准备文件
    int fd = open("./test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) return -1;
    char buffer[] = "hello world";
    write(fd, buffer, sizeof(buffer) - 1);
    close(fd);
    
    sleep(20);

    truncate("./test.txt", 5);

    return 0;

}