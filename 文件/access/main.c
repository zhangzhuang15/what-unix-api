// #include <unistd.h>
// int access(const char* pathname, int mode)
// 判断实际用户对文件有何种访问权限
//
// pathname-文件路径
// mode-文件访问权限
//      R_OK 可读
//      W_OK 可写
//      X_OK 可执行
//
// 成功返回0，
// 失败返回-1

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    // 准备文件
    int fd = open("./test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    if (fd < 0) {
        perror("无法打开文件");
        return -1;
    }

    close(fd);

    int r = access("./test.txt", X_OK);
    if (r < 0) {
        printf("对文件无执行权\n");
    }

    r = access("./test.txt", R_OK);
    if (r == 0) {
        printf("对文件有读权\n");
    }
    return 0;
}