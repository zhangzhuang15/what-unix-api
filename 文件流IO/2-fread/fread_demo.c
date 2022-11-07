// fread fopen fclose 所必需
#include <stdio.h>

// 从 fp 的文件中，对去 nobj 个 对象到 ptr指向的内存区，每个对象大小为 size 字节
// size_t fread(void* restrict ptr, size_t size, size_t nobj, FILE *restrict fp)
// 成功时，返回读取的对象数

int main() {
    FILE* file = fopen("./demo.txt", "r");
    char buff[1024];
    size_t hasRead = fread(buff, sizeof(char), 20, file);
    printf("读取到 %zd 个 char\n", hasRead);
    printf("内容是 %s\n", buff);
    fclose(file);
}
