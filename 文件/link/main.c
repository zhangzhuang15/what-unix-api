// #include <unistd.h>
// int link(const char *existingpath, const char *newpath)
// 创建一个硬链接
//
// existingpath-已经存在的文件的路径
// newpath-链接文件的路径，如果已经存在，会报错
//
// 成功返回0
// 失败返回-1

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // 准备文案
    int fd = open("./test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        return -1;
    }
    close(fd);

    // 创建链接文件
    int r = link("./test.txt", "./test_copy");
    if (r < 0) {
        perror("创建失败");
        return -1;
    }

    return 0;
}

// 当你修改 test.txt 后，test_copy 的内容也同样修改了。
// 因为 test.txt 和 test_copy 共用一个 i-node