#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    /* 创建一个文件夹 */
    int f = mkdir("/Users/zhangzhuang/Project/candcppProject/c_demo/io_demo", S_IRUSR | S_IWUSR | S_IXUSR);
    if (f < 0) {
        printf("io_demo 文件夹已经存在\n");
    }
    else {
        printf("io_demo 文件夹创建完成\n");
    }

    /* 获取文件夹对应的文件描述符 dir_d 
       打开文件夹的文件描述符，必须指定为 O_RDONLY, 指定O_RDWR无效 
    */
    int dir_d = open("/Users/zhangzhuang/Project/candcppProject/c_demo/io_demo", O_RDONLY);

    char write_buf[50] = "this line is just a test\nok,everything is well.\n";

    /* openat可以指定当前工作路径为 dir_d描述符对应的路径 */
    int fd_in_dir = openat(dir_d, "./io_test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    /* 创建一个文本文件 
       文件路径名使用的是相对路径，相对的是当前工作路径，
       什么是当前工作路径？ 比如本文件被编译为二进制文件后，
       你在 /a/b文件夹下执行本文件，则当前工作路径就是 /a/b
    */
    int fd = open("./test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    /* 写入数据 
       写入数据时，写入的字节数不要超过write_buf的长度50，否则多出来的字节将是意料之外的数据
    */
    ssize_t has_write =  write(fd, write_buf, strlen(write_buf));
    printf("has written %ld bytes\n", has_write);
    write(fd_in_dir, write_buf, strlen(write_buf));
    close(fd_in_dir);
    close(dir_d);

    /* 设置文件读取位置 
       SEEK_SET   表示文件开头
       SEEK_END   表示文件结尾
       SEEK_CUR   表示文件当前位置
    */
    lseek(fd, 0, SEEK_SET);
    
    /* pwrite也是写入数据的，但是其不会改变当前文件偏移量，
       通过leek已经回到文件开头了，为了文件尾写入数据，
       写入点应该定位当前文件位置向后偏移 strlen(write_buf)
    */
    pwrite(fd, write_buf, strlen(write_buf), strlen(write_buf));
    char read_buf[50];
    /* 读取56个字节，此时56要大于read_buf长度，只读取50个字节数据 */
    ssize_t has_read = read(fd, read_buf, 2*strlen(write_buf));
    printf("从文件中读取%ld字节数据: %s\n", has_read, read_buf);

    /* 清空 write_buf */
    memset(write_buf, '\0', 50);
    sprintf(write_buf, "\nMacBook Pro 14.1 is comming\n");
    write(fd, write_buf, strlen(write_buf));
    /* write命令会将数据写入到内核缓存区中，使用fsync强制刷入磁盘*/
    fsync(fd);
    
   /* 获取文件描述符的 o_flag信息 
      必须在 close方法执行前调用，否则fd就失效了
    */
   int flag = fcntl(fd, F_GETFL, 0);
   switch(flag & O_ACCMODE){
       case O_RDWR:
         printf("文件描述符%d 可读可写\n", fd);
         break;
       case O_RDONLY:
         printf("文件描述符%d 只读\n", fd);
         break;
        default:
         printf("查不到了\n");
   }

   close(fd);

   /* 以上使用了 open read write lseek pread mkdir
      这些都是系统调用，进入内核态执行，这种操作更底层，
      以至于写出来的test.txt文件不是完美的.txt文件格式，
      和 fopen系列的文件操作有明显的区别
    */
}