#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <aio.h>

/* aio中的异步方式分为几种， 由 struct aiocb 的 aio_sigevent.sigev_notify给出：
   1、无信号机制 SIGEV_NONE
       需要指定 aio_sigevent.sigev_notify = SIGEV_NONE;
       需要我们不断调用 aio_error轮询，判断异步操作是否完成
   
   2、进程信号机制 SIGEV_SIGNAL
       需要指定 
           aio_sigevent.sigev_notify = SIGEV_SIGNAL;
           aio_sigevent.sigev_signal， 并编写进程对应信号的中断函数（用sigaction函数实现）
       
   3、线程回调机制 SIGEV_THREAD
       需要指定 aio_sigevent.sigev_notify = SIGEV_THREAD;
              aio_sigevent.sigev_notify_attributes = NULL;
              aio_sigevent.sigev_notify_function = callback;
              aio_sigevent.sigev_value.sival_ptr = &aiocb;
    
    以上三个机制，linux全部支持，macos只支持第一种；
    因此，本例程打算使用线程回调是无法运行的。会在调用 aio_read处一直返回 -1
*/
struct aiocb read_aiocb, write_aiocb;
char buff[20];
int already_read = 0, already_write = 0;
int read_fd, write_fd;

void write_callback(union sigval val) {
    printf("write_callback -> PID: %d\n", getpid());
    struct aiocb *cb = (struct aiocb*)val.sival_ptr;
    int r = 0;
    if ((r = aio_error(cb)) < 0) {
        printf("本次文件写入有误");
    }
    else if (r == 0){
       r = aio_return(cb);
       printf("本次文件写入成功, 读取%d字节数据\n", r);
       already_write = already_write + r ;

       memset(buff, '\0', strlen(buff));
       read_aiocb.aio_offset = already_read;
       
       int r = aio_read(&read_aiocb);
       if (r < 0) {
           _exit(200);
       }
    }
}

/* aio读取操作的回调函数 */
void read_callback(union sigval val) {
    printf("read_callback -> PID: %d\n", getpid());
    struct aiocb *cb = (struct aiocb*)val.sival_ptr;
    int r = 0;
    if ((r = aio_error(cb)) < 0) {
        printf("本次文件读取有误\n");
    }
    else if( r == 0){
       r = aio_return(cb);
       if (r == 0) _exit(200);
       printf("本次文件读取成功, 读取%d字节数据\n", r);
       already_read = already_read + r;
      
       write_aiocb.aio_fildes = write_fd;
       write_aiocb.aio_nbytes = 20;
       write_aiocb.aio_buf = buff;
       write_aiocb.aio_offset = already_write;
       write_aiocb.aio_sigevent.sigev_notify = SIGEV_THREAD;
       write_aiocb.aio_sigevent.sigev_notify_attributes = NULL;
       write_aiocb.aio_sigevent.sigev_notify_function = write_callback;
       write_aiocb.aio_sigevent.sigev_value.sival_ptr = &write_aiocb;

       int r = aio_write(&write_aiocb);
       if (r < 0) {
           printf("异步写入操作发生错误，未能加入到队列中\n");
           _exit(200);
       }
    }
}

void before_test() {
    int dir = mkdir("./aio_demo", S_IRUSR | S_IWUSR | S_IXUSR);
    if (dir < 0) 
      printf("aio_demo文件夹已经存在\n");
    else
      printf("aio_demo文件夹创建成功\n");
    
    int fd = open("./aio_demo/test.txt",
                  O_CREAT | O_RDWR | O_TRUNC, S_IXUSR | S_IRUSR | S_IWUSR);
    if (fd < 0) 
      printf("aio_demo/test.txt文件创建失败\n");
    else
      printf("aio_demo/test.txt文件创建成功\n");
    
    char buff[512];

    memset(buff, '\0', 512);
    strcpy(buff, "I have to write down something, in order to take a test of aio API."\
                 "I guess that node.js asynchronous operation is built on this API.\n"\
                 "And now, every electronic company intends to product own sillicon chips,"\
                 "they will face intense controversy than ever before.\n");
    write(fd, buff, strlen(buff));

    memset(buff, '\0', strlen(buff));
    strcpy(buff, "Recently, I have heard that MacBook Pro 14.1 with Mini-LED Screen is coming "\
                 "soon.We will probably see it in September.It's really exciting news.\n"\
                 "But on the other hand, This new Designed Computer is considered to be much more "\
                 "expensive than advanced Intel MacBook Pro 13.3. It costs $2000 at least.\n"\
                 "In this aspect, It is bad news.\n");
    write(fd, buff, strlen(buff));

    close(fd);

    printf("aio_demo/test.txt已经写入数据\n\n");
}

void aio_test() {
    read_fd = open("./aio_demo/test.txt", O_RDONLY);
    if (read_fd < 0) {
        printf("打开aio_demo/test.txt文件时发生错误\n");
        return;
    }
    printf("aio_demo/test.txt文件已经打开\n");

    write_fd = open("./aio_demo/test_copy.txt", 
                    O_CREAT | O_RDWR | O_TRUNC, 
                    S_IWUSR | S_IRUSR | S_IXUSR);
    if (write_fd < 0) {
        printf("aio_demo/test_copy.txt 文件创建失败\n");
        return;
    }
    printf("aio_demo/test_copy.txt 文件已经打开\n");

    memset(buff, '\0', 20);

    read_aiocb.aio_fildes = read_fd;
    read_aiocb.aio_buf = buff;
    read_aiocb.aio_nbytes = 20;
    read_aiocb.aio_offset = already_read;
    read_aiocb.aio_sigevent.sigev_notify = SIGEV_THREAD;
    read_aiocb.aio_sigevent.sigev_notify_attributes = NULL;
    read_aiocb.aio_sigevent.sigev_notify_function = read_callback;
    read_aiocb.aio_sigevent.sigev_value.sival_ptr = &read_aiocb;

    for(;;) {
        int r = aio_read(&read_aiocb);
        if (r < 0) {
            printf("异步读取请求发生错误，未能加入到执行队列中\n");
        }
        else
          break;
    }
}

int main() {
   before_test();
   aio_test();
   sleep(20);
}