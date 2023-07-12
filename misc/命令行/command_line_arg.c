// 使用 main 参数 char* argv[] 获取command line 数据
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    if (argc < 2) {
        printf("command line length < 2\n");
    } else {
        for (int i = 1; i < argc; i++) {
            const char* token = argv[i];

            if (strcmp(token, "-h") == 0) {
                printf("this is help message\n"
                       "welcome to the simple command line demo\n");
            }
        }
    }
}

// compile this file, and get an executable file named "main";
// run "./main -h" in shell;
// then, argc will be 2, argv will be ["./main", "-h"];

// pretty easy!