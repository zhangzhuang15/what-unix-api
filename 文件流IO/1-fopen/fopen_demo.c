// FILE fopen fclose perror 所必需
#include <stdio.h>

// 
// FILE* fopen(const char* pathname, const char * restrict type)
// 成功时，返回 FILE指针；
// 失败时，返回 NULL；
//
// pathname   文件路径名
// type       文件访问模式
//             "r"    只读， 文件不存在时报错
//             “r+”   读写， 文件不存在时报错
//             "w"    只写， 文件内容先被截断
//             "w+"   读写， 文件内容先被截断
//             "a"    追加写
//             "a+"   追加读写

int main() {
    FILE* file = fopen("./demo.txt", "w+");
    if(file == NULL) {
        perror("文件打开失败");
    } else {
        printf("文件打开成功");
    }
    fclose(file);
}

// 删除 demo.txt, 将 第19行 改为 "r+"，再运行看看效果