#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

// SCREEN* newterm(char* , FILE* out, FILE* in)
// 创建一个虚拟的终端（并不会创建一个新的终端出来）；
// 该虚拟终端的标准输出定位到 out 中， 标准输入定位到 in 中；

// set_term(SCREEN* term)
// 切换当前的虚拟终端到 term

// delscreen(SCREEN* term)
// 销毁虚拟终端 term， 释放其占用的资源；

int main() {
   FILE* f = fopen("./test.txt", "w+");

   SCREEN* s =  newterm(NULL, stdout, stdin);
   SCREEN* c = newterm(NULL, f, stdin);

   char i = 0;
   
   SCREEN* current = c;
   while((i = getch()) != 'q') {
       if (i == 'c') {
           set_term(current == c ? s: c);
           current = current == c? s: c;
       }
       printf("ok\n");
   }
   fclose(f);
   delscreen(c);
   delscreen(s);
}