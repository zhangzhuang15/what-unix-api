// #include <sys/stat.h>
// int stat(const char *restrict pathname, struct stat *restrict buf)
// 获取文件信息
//
// pathname-文件路径
// buf-记录文件信息的结构体
//     struct stat {
//            mode_t st_mode;   文件类型和文件访问权限
//            ino_t  st_ino;    i-node number
//            dev_t  st_dev;    文件系统中的设备号
//            dev_t  st_rdev;   特殊文件的设备号
//            nlink_t  st_nlink; 文件的连接数
//            uid_t  st_uid;    文件拥有者的 user ID
//            gid_t  st_gid;    文件拥有者的 组 ID
//            off_t  st_size;   普通文件的字节大小
//            struct timespec st_atime; 最近访问的时间
//            struct timespec st_ctime; 最近文件i-node状态改变的时间
//            struct timespec st_mtime; 最近修改的时间
//            blksize_t st_blksize;  对文件IO时，最佳缓存大小
//            blkcnt_t st_blocks;  文件占据多少512字节的块
//      }
//
// 成功，返回0，文件信息记录到 buf 中；
// 失败，返回-1

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void judgeFileType(struct stat* buf) {
    if (S_ISREG(buf->st_mode)) {
        printf("普通文件\n");
    } 
    else if (S_ISDIR(buf->st_mode)) {
        printf("目录\n");
    }
    else if (S_ISFIFO(buf->st_mode)) {
        printf("FIFO或者管道\n");
    }
    else if (S_ISLNK(buf->st_mode)) {
        printf("符号链接\n");
    }
    else if (S_ISSOCK(buf->st_mode)) {
        printf("套接字文件\n");
    }
    else if (S_ISBLK(buf->st_mode)) {
        printf("块特殊文件\n");
    }
    else if (S_ISCHR(buf->st_mode)) {
        printf("字符特殊文件\n");
    }
    else if (S_TYPEISMQ(buf)) {
        printf("消息队列\n");
    }
    else if (S_TYPEISSEM(buf)) {
        printf("信号量\n");
    }
    else if (S_TYPEISSHM(buf)) {
        printf("共享存储对象\n");
    }
    else {
        perror("非法文件");
    } 
}

int main() {
    // 准备文件
    int fd = open("./test.txt", O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);

    if (fd < 0) {
        perror("无法打开文件");
        return -1;
    }

    // 更新文件内容
    char buffer[] = "yes, go on";
    write(fd, buffer, sizeof(buffer) - 1);
    close(fd);

    // 查看文件信息
    struct stat buf;
    int r = stat("./test.txt", &buf);
    if (r < 0) {
        perror("调用stat失败");
        return -1;
    }

    // 判断文件类型
    judgeFileType(&buf);

    if (buf.st_mode & S_ISUID) {
        printf("将访问文件的进程User ID 自动设置为文件所有者的User ID\n");
    }

    if (buf.st_mode & S_ISGID) {
        printf("将访问文件的进程Group ID 自动设置为文件所有者的Group ID\n");
    }
}