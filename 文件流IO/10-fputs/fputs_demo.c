// fputs fopen fclose 所必需
#include <stdio.h>

// 将字符串str写入到 fp 中
// int fputs(const char *restrict str, FILE *restrict fp)
// 成功时，返回非负数；
// 失败时，返回EOF；


int main() {
    FILE *file = fopen("./demo.txt", "w");
    char buff[] = "It's just a demo.\ntake it easy.";
    fputs(buff, file);
    fclose(file);
}