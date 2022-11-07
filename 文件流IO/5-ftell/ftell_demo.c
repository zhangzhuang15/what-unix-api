// ftell fopen fseek fclose 所必需
#include <stdio.h>

// 返回当前文件流的位置，也就是相对于文件开头来讲，向后偏移了多少字节 
// long ftell(FIFL* fp)
// 成功时，返回偏移量；
// 失败时， 返回 -1;

int main() {
    FILE *file = fopen("./demo.txt", "r");
    fseek(file, 5, SEEK_SET);
    long position = ftell(file);
    printf("当前位置距离文件开头 %ld 个字节\n", position);
    fclose(file); 
}