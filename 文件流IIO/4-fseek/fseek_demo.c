// fopen fread fseek fclose 所必需
#include <stdio.h>

// 将fp所指的文件流定位到 offset 和 whence 所指定的位置
// int fseek(FILE *fp, long offset, int whence)
// 成功时, 返回0；
// 失败时, 返回-1;
//
// whence   SEEK_SET   从文件起始位置开始
//          SEEK_CUR   从文件当前位置开始
//          SEEK_END   从文件末尾开始
//
// offset   偏移量。偏移量的起始处由 whence 决定。

int main() {
    FILE* file = fopen("./demo.txt", "r");
    char buff[1024];
    fseek(file, 5, SEEK_SET);
    fread(buff, sizeof(char), 20, file);
    printf("读取到数据: %s\n", buff);
    fclose(file);
}

// fopen之后，流的位置处于 demo.txt 中 “yes” 的 ‘y’。
// fseek向后移动5个字节，流的位置处于 "your answer is right" 的 'y'。