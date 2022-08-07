// #include <sys/stat.h>
// mode_t umask(mode_t cmask)
// 当前进程设置新的文件屏蔽字，返回之前的文件屏蔽字
//
// cmask-文件访问权限 如 S_IRUSR 等
//
// 注意，该函数是屏蔽访问权限，屏蔽了哪个权限，进程将丧失该权限！

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    umask(S_IRUSR);

    int fd = open("./test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("设置了屏蔽字，无法打开文件");
        return 0;
    }

    close(fd);
    return 0;
}