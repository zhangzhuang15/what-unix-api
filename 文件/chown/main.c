// #include <unistd.h>
// int chown(const char *pathname, uid_t owner, gid_t group)
// 修改文件的用户ID和组ID
//
// pathname-文件路径
// owner-用户ID，设置-1则不修改
// group-组ID，设置-1则不修改
//
// 成功返回0
// 失败返回-1


#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    // 准备文件啊
    int fd = open("./test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    close(fd);

    // 获取进程 uid gid
    uid_t uid = getuid();
    gid_t gid = getgid();

    // 获取文件信息
    struct stat buf;
    stat("./test.txt", &buf);

    // 验证
    if (buf.st_uid == uid) {
        printf("进程uid 和 文件uid都是 %u\n", uid);
    }

    if (buf.st_gid == gid) {
        printf("进程gid 和 文件gid都是 %u\n", gid);
    }

    // 修改文件gid，且故意修改失败
    int r = chown("./test.txt", -1, 0);
    if (r < 0) {
        printf("修改文件的拥有者发生错误\n");
    }

    return 0;
}