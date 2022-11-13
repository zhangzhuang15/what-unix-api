// #include <stdlib.h>
// int system(const char* shellCmd)
// 在shell环境中，执行 shellCmd 表示的命令
//
// shellCmd - shell命令字符串
//
// 成功时，返回 shell 终止码；
// 失败情况：
//    system 底层实现中，使用了 fork waitpid exec 函数，因此分为2种情况讨论：
//    1. 因 system 底层实现中，执行 fork 失败或者 waitpid 返回 EINTR 之外报错，返回 -1， 在 errno 中指明具体错误；
//    2. 因 system 底层实现中，执行 exec 失败，返回值同 shell 执行 exit(127);

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;

int main() {

   if (system(NULL) != 0) {
    printf("support system \n");
   }
   int success = system("gcc -v");
   if (success != -1) {
    printf("no: %d\n", success);
    printf("exit code: %d\n", WEXITSTATUS(success));
   }

   // 触发了 exec 执行失败的情况
   success = system("ky -a");
   if (success != 0) {
    printf("errno: %d\n", errno);
    perror("err message");
   }
   
   return 0;
}