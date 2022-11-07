// fgets fopen fclose 所必需
#include <stdio.h>

// 从 fp 中按行读取数据，存入到buff指向的内存区，内存区大小为 n 字节
// char* fgets(char *restrict buff, int n, FILE *restrict fp)
// 成功时，返回 buff
// 出错或者达到文件末尾，返回NULL

int main() {
    char buff[5];
    FILE *file = fopen("./demo.txt", "r");
    while( fgets(buff, sizeof(buff), file) != NULL) {
        printf("读到数据: %s\n", buff);
    }
    fclose(file);
}