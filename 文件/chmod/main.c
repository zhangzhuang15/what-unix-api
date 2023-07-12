// #include <sys/stat.h>
// int chmod(const char *pathname, mode_t mode)
// 修改文件访问权限
//
// pathname-文件路径
// mode-权限
//  S_ISUID 执行时设置用户ID
//  S_ISGID 执行时设置组ID
//  S_ISVTX 保存正文（粘着位）
//  S_IRWXU 用户（所有者）读、写和抉
//  S_IRUSR 用户（所有者）读
//  S_IWUSR 用户 （所有者）写
//  S_IXUSR 用户（所有者）执行
//  S_IRWXG 组读、写和执行
//  S_IRGRP 组读
//  S_IWGRP 组写
//  S_IXGRP 组执行
//  S_IRWXO 其他读、写和执行
//  S_IROTH 其他读
//  S_IWOTH 其他写
//  S_IXOTH 其他执行
//
// 成功返回0
// 失败返回-1

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    // 准备文件
    int fd = open("./test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    if (fd < 0) {
        return -1;
    }

    close(fd);

    sleep(20);

    chmod("./test.txt", S_IRUSR | S_IWUSR | S_IXUSR | S_IXGRP);

    return 0;
}














