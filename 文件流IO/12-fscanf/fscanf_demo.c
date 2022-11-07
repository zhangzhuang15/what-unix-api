// fscanf fopen fclose 所必需
#include <stdio.h>
 
// 从 fp 中读取数据，将格式化输入的变量赋值 
// int fscanf(FILE *restrict fp, const char *restrict format, ...)
// 成功时，返回赋值输入的项数
// 失败或者达到文件末尾，返回EOF

int main() {
    FILE *file = fopen("./demo.txt", "r");
    char buff[5];
    fscanf(file, "hello I am %s", buff);
    printf("your name is %s", buff);
    fclose(file);
}