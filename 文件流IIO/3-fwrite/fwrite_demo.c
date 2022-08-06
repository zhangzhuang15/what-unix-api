// fopen fwrite fclose 所必需
#include <stdio.h>

// strlen 所必需
#include <string.h>

// 将 ptr 指向的内存区中 nobj 个对象写入到 fp 文件中，每个对象大小为 size 字节
// size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp)
// 成功时，返回写入的对象数

int main() {
    char buff[] = "不怎么样啊,一切都要继续。";
    FILE* file = fopen("./demo.txt", "w");
    size_t hasWrite = fwrite(buff, strlen(buff), 1, file);
    if(hasWrite == 1) {
        printf("成功写入 1 个对象, 共 %lu 个字节\n", strlen(buff));
    } else {
        perror("写入失败");
    }
    fclose(file);
}

// 将 第14行 的 strlen(buff) 改为 sizeof(buff),
// 再运行一下，就会发现 demo.txt 的内容格式不对了