// rewind fopen fseek fclose 所必需
#include <stdio.h>


// 使文件流回归到文件开头
// void rewind(FILE *fp)

int main() {
    FILE *file = fopen("./demo.txt", "r");
    fseek(file, 4, SEEK_SET);
    rewind(file);
    long position = ftell(file);
    if(position == 0) {
          printf("回到文件开头");
    }
    fclose(file);
}