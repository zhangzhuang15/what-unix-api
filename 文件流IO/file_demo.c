#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* 展示标准I/O库用法 
   标准I/O库中的函数是对 open read write等更底层的I/O操作的封装。
   标准I/O库的函数围绕 FILE对象展开；
   更底层的I/O操作函数围绕 文件描述符展开;
   fopen
   fputc
   putc
   getchar
   gets
   fgets
   fseek
   fwrite
   fprintf
   sprintf
   snprintf
*/

void test() {
    int okey = mkdir("./file_demo", S_IXUSR | S_IRUSR | S_IWUSR);
    if (okey < 0) {
        printf("创建file_demo文件夹失败，或file_demo文件夹已经存在\n");
    }
    printf("创建file_demo文件夹成功\n");
    printf("\n");

    /* 用标准I/O中的fopen函数创建一个文件
       r   rb          O_RDONLY
       r+  rb+         O_RDWR
       w   wb       O_WRONLY | O_CREAT | O_TRUNC
       w+  wb+         O_RDWR | O_CREAT | O_TRUNC
       a   ab         O_WRONLY | O_CREAT | O_APPEND
       a+  ab+         O_RDWR | O_CREAT | O_APPEND
    */
    FILE *f;
    f = fopen("./file_demo/test.txt", "w+");
    if (f == NULL) {
        printf("file_demo/test.txt文件创建失败\n");
        exit(-1);
    }
    printf("file_demo/test.txt文件创建成功\n");
    printf("\n");

    /* 输出单个字符 */
    printf("向文件输出'a'  ----------\n");
    int c = fputc('a', f);
    if (c == EOF) printf("输出'a'失败\n");
    else printf("成功\n");
    printf("\n");
    

    /* 输出单个字符 */
    printf("向文件输出 'b'  ----------\n");
    c = putc('b', f);
    if (c == EOF) printf("输出'b'失败\n");
    else printf("成功\n");
    printf("\n");

    /* 向终端输出一个字符 */
    printf("向终端输出'c'  ----------\n");
    c = putchar('c');
    if (c == EOF) printf("输出'c'失败\n");
    else printf("成功\n");
    printf("\n");

    /* 从终端读取一个字符 */
    printf("getchar 从终端读取一个字符  ----------\n");
    c = getchar();
    printf("从终端读取的字符是\t%c\n", (char)c);
    printf("\n");

    /* 向终端输出一行字符 
       puts输出的字符串不是以字符串中的 \n 为结束标志的，而是以 \0
    */
    printf("puts 向终端输出一行字符  -------\n");
    c = puts("this is first\0line\nthis is second line");
    if (c == EOF) printf("输出失败\n");
    else printf("输出成功\n");
    printf("\n");

    /* 从终端读入一行字符*/
    printf("gets 从终端读取一行字符  -------\n");
    char buff[10]; // 指定读入的缓存区大小
    /* 终端输入的时候不要不要超过10个字符（换行符包括在内），否则出现缓冲区溢出问题，留下程序引患 
       程序运行到这里的时候 ，直接输出警告，不允执行
    */
    char *result = gets(buff); 
    if (result == NULL) printf("读取一行字符失败\n");
    else printf("读取的一行字符是 %s\n", buff);
    printf("\n");

    /* 向文件输出一行字符 
       fputs输出的字符串也不会以 \n 为行结束标志，而是以 \0
    */
    printf("fputs 向文件输出一行字符  -------\n");
    c = fputs("this is a new line\nthis is also a new line.", f);
    if (c == EOF) printf("输出一行字符到文件中失败\n");
    else printf("输出一行字符到文件中成功\n");
    printf("\n");

    /* 从文件中读入一行字符 */
    fseek(f, -5, SEEK_CUR);
    printf("fgets 从文件中读入一行字符  -------\n");
    /* 5 指定读取的字节数 */
    result = fgets(buff, 5, f); // 可以指定读入的字节数，比gets方法安全
    if (result == NULL) printf("从文件中读取一行字符失败\n");
    else printf("从文件中读取一行字符： %s\n", result);
    printf("\n");

    /* fgets再次从终端读入一行字符*/
    printf("fgets 从终端读入一行字符  -------\n");
    /* 输入 abc后，按下回车， abc\n\0就会存储到buff中，这会导致第二次fgets调用没有获得输入而被阻塞
       如果输入 abcd后，按下回车，abcd\0就会存储到buff中，剩下的\n会存入到第二次fgets调用时的buff中，
       因而第二次的fgets并没有阻塞（也就是不提示你再输入一些字符）
    */
    result = fgets(buff, 5, stdin);
    if (result == NULL) printf("从终端读取一行字符失败\n");
    else printf("从终端读取一行字符：%s\n", result);
    result = fgets(buff, 5, stdin);
    if (result == NULL) printf("从终端读取一行字符失败\n");
    else printf("从终端读取一行字符：%s\n", result);
    printf("\n");

    /* 写入文件任意的数据 */
    printf("fwrite 写入任意数据  -------\n");
    strncpy(buff, "MacBook is coming, but tooo expensive", 10);
    /* 
       param_1 指定写数据时数据的起始地址
       param_2 指定写入的一块数据有几个字节
       param_3 指定写入几块数据
       param_4 FILE*
       数据流动方向  内存 ----> FILE

       如果是 fread，参数含义不变，只是数据流动方向反了   内存 <----- FILE
    */
    if (fwrite(buff, sizeof(buff), 1, f) != 1) printf("输出任意数据到文件中失败了\n");
    else printf("成功输出任意数据到文件中\n");
    printf("\n");

    /* 格式化I/O 
       对于格式化输出：
           printf
           fprintf   param_1是 FILE*
           dprintf   param_1是 文件描述符
           sprintf   param_1是 数组名
           snprintf  param_1是 数组名，且该函数可以指定输出到数组的字节数
    */
    printf("格式化I/O\n");
    printf("fprintf 格式化I/O输出到文件中\n");
    if (fprintf(f, "element %d\n", 1) >= 0)  printf("成功\n");
    else printf("失败\n");
    printf("\n");

    printf("sprintf 格式化输出到数组中\n");
    if (sprintf(buff, "okeyye%d\n", 2) >= 0) printf("成功，数组buff： %s\n", buff);
    else printf("失败\n");
    printf("\n");
    
    printf("snprintf 格式化输出到数组中\n");
    if (snprintf(buff, 10, "MacOS %d Montery", 12) >=0) printf("成功，数组buff: %s\n", buff);
    else printf("失败\n");
    printf("\n");
  
    fclose(f);
}

int main() {
    test();
}