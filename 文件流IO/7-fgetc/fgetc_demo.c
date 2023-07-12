// fgetc fopen fclose ferror 所必需
#include <stdio.h>


// 从 fp 中读取一个字符
// int fgetc(FILE *fp)
// 成功时， 返回这个字符
// 失败或者到达文件末尾，返回EOF, 使用ferror区分

//
// int ferror(FILE *fp)
// fp有错误，返回 非0
// 无错误， 返回 0

int main() {
    FILE *file = fopen("./demo.txt", "r");
    int letter = 0 ;
    while( (letter = fgetc(file)) !=  EOF) {
        printf("%c", letter);
    }
    if(ferror(file) != 0) {
        printf("读取文件发生了错误\n");
    }
    fclose(file);
}
