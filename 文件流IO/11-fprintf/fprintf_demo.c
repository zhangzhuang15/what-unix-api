// fprintf fopen fclose 所必需
#include <stdio.h>

// 将 格式化的字符串 输入到 fp中
// int fprintf(FILE *restrict fp, const char *restrict format, ...)
// 成功时，返回输出的字符数；
// 失败时，返回负数


int main() {
    FILE *file = fopen("./demo.txt", "w");
    const char *message = "wonderful time";
    fprintf(file, "this is %s", message);
    fclose(file);
}
