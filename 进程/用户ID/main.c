#include <unistd.h>
#include <stdio.h>

int main() {
    // 501 是笔者的实际用户ID，请替换成读者自己的实际用户ID
    if (seteuid(501) != 0) {
        printf("failed to seteuid 501");
        return -1;
    }

    printf("uid: %d, euid: %d\n", getuid(), geteuid());

    FILE *file = fopen("./test.txt", "w+");
    if (file == NULL) {
        printf("failed to create file");
        return -1;
    }

    fclose(file);
    return 0;
}

/**
 * 使用sudo运行本程序，验证创建的文件的用户ID等于进程
 * 有效用户ID，而不是实际用户ID。
 */