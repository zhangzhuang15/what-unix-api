// fputc fopen fclose 所必需
#include <stdio.h>


// 将字符c输入到 fp的文件中
// int fputc(int c, FILE *fp)
// 成功时，返回c；
// 失败时，返回EOF

int main() {
    FILE *file = fopen("./demo.txt", "w");
    fputc('N', file);
    fputc('i', file);
    fputc('u', file);
    fclose(file);
}