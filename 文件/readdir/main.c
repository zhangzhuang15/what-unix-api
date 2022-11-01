// #include <dirent.h>
// struct dirent *readdir(DIR *dp)
// 读取目录
//
// dp-由opendir打开的目录指针
//
// 成功，返回目录内容的指针
// 失败，或者目录下无内容可读了，返回NULL

#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    // 准备目录
    int r = mkdir("./demo", S_IRUSR | S_IWUSR | S_IXUSR);
    if (r < 0) {
        printf("目录已存在\n");
    }

    // 准备文件
    r = creat("./demo/test1.txt", S_IRUSR | S_IWUSR);
    if (r < 0) {
        printf("文件test1.txt已经存在\n");
    }
    r = creat("./demo/test2.txt", S_IRUSR | S_IWUSR);
    if (r < 0) {
        printf("文件test2.txt已经存在\n");
    }

    // 打开目录
    DIR *dir = opendir("./demo");
    if (dir == NULL) {
        printf("目录不存在\n");
        return -1;
    }

    // 读目录
    struct dirent* item;
    while((item = readdir(dir)) != NULL) {
        printf("文件名: %s\n", item->d_name);
        printf("文件类型: %c\n", item->d_type);
    }

    // 关闭目录
    closedir(dir);
}