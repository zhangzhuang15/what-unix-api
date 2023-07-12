#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/select.h>
#include <sys/stat.h>

/* select方法用于非阻塞读写文件
   使用read读取某个文件描述符对应的文件时，可能因为部分缘故，导致read方法阻塞，该阻塞结束后，在读取下一个文件描述符时也会遇到类似的情况，
   导致整个程序“走走停停”，速度很差；
   使用select方法后，可以向其中注册多个文件描述符，在调用select方法时，会产生阻塞，但阻塞结束后，
   就会通过 fd_set中各文件描述符对应的bit位告诉我们，这个文件描述符是否准备好了，准备好的描述符在
   调用read、write时就不会阻塞，这样就可以避免“走走停停”的现象，提升性能
*/
void before_test() {
    int fd = mkdir("/Users/zhangzhuang/Project/c_project/c_demo/select_demo", S_IRUSR | S_IWUSR | S_IXUSR);
    if (fd < 0)
        printf("select_demo文件夹已经存在\n");
    else 
        printf("select_demo文件夹创建成功\n");

    fd = open("/Users/zhangzhuang/Project/c_project/c_demo/select_demo/test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
    if (fd < 0) 
        printf("select_demo/test.txt文件创建失败\n");
    else
        printf("select_demo.test.txt文件已经打开\n");

    char buff[1024] = "first line is not very long, I do promise that "\
                      "I don't lie.But even though I admit this, some people "\
                      "still don't trust in me, it's terrible.\n";
    write(fd, buff, strlen(buff));
  
    memset(buff, '\0', strlen(buff));
    strcpy(buff, "second line is very very long, and you never know why is so "\
                 "long, hahahah, you still konw it, right?"\
                 "It's very very boring day in day out.I cannot stand the life."\
                 "Nobody wanna try nothing, retrieve nothing, think nothing.Oh MY GOD!\n");
    write(fd, buff, strlen(buff));

    memset(buff, '\0', strlen(buff));
    strcpy(buff, "third line is not so long, but it takes many space,"\
                 "I wanna make it longer so that we could get pretty test result.\n"\
                 "I guess you really wanna know the result of this test.So, just run this "\
                 "program, waiting for the end, expecting the output looking like.");
    write(fd, buff, strlen(buff));

    close(fd);
    printf("\n");
}

void io_test() {
    printf("io_test demo \\/ \n");

    time_t start = time(NULL);
    
    int fd = open("/Users/zhangzhuang/Project/c_project/c_demo/select_demo/test.txt", O_RDONLY);
    char buff[512];
    int n_read = 0;
    if (fd < 0) printf("open select_demo/test.txt failed\n");
    else {
        while((n_read = read(fd, buff, 512)) > 0) {
            printf("read: %s\n", buff); 
            memset(buff, '\0', 512);
        }
        if (n_read < 0) printf("read err!\n");
        else printf("read til the end\n");
        close(fd);
    }

    time_t end = time(NULL);
    printf("io test cost %lds\n", (end - start));
    printf("\n");
}

void select_test() {
    printf("select_test demo \\/ \n");

    time_t start = time(NULL);

    int fd = open("/Users/zhangzhuang/Project/c_project/c_demo/select_demo/test.txt", O_RDONLY | O_NONBLOCK);
    char buff[512];
    int n_read = 0;

    fd_set read_set;
    FD_ZERO(&read_set);
    FD_SET(fd, &read_set);


    if (fd < 0) printf("open select_demo/test.txt failed\n");
    else {
        /* select将返回已经准备好的文件符总数 
           已经准备好的文件符fd 所对应的 fd_set 的 bit位继续保持是 1，否则会被select 设置为0
          
           int select(int maxfdpl, fd_set *restrict readfds, fd_set *restrict writefds,
                      fd_set *restrict exceptfds, struct timeval *restrict tvptr)
        */
        int result = select(fd + 1, &read_set, NULL, NULL, NULL);
        if (result == -1) printf("select err !\n");
        else if (result == 0) printf("no fd is ready\n");
        /* 判断fd已经准备好可以读了
           普通io会阻塞，直到可以读为止，这里不需要阻塞
        */
        else if (FD_ISSET(fd, &read_set) != 0) {
            while((n_read = read(fd, buff, 512)) > 0) {
                printf("read: %s\n", buff);
                memset(buff, '\0', 512);
            }
            if (n_read < 0) printf("read err!\n");
            else printf("read til the end\n");
        }
        else{}
        close(fd);
    }

    time_t end = time(NULL);
    printf("select io test cost %lds\n", (end - start));
}

void pselect_test() {
    printf("\npselect_test is starting\n");

    time_t start_time = time(NULL);
    fd_set read_set;
    FD_ZERO(&read_set);
    int fd = open("/Users/zhangzhuang/Project/c_project/c_demo/select_demo/test.txt", O_RDONLY);
    if (fd < 0) {
        printf("打开文件失败\n");
        return;
    }
    FD_SET(fd, &read_set);

    struct timespec tsp;
    tsp.tv_sec = 10; // 10s
    tsp.tv_nsec = 3000; // 3000ns

    char *buff = (char*)malloc(512*sizeof(char));
    memset(buff, '\0', 512);

    while(1){
        int already_fds = pselect(fd+1, &read_set, NULL, NULL, &tsp, NULL);
        if (already_fds < 0) {
            printf("pselect执行期间发生了什么错误\n");
            break;
        }
        else if(already_fds == 0) {
            continue;
        }
        else {
            int read_size = 0;
            // fd就绪时，返回非0
            if (FD_ISSET(fd, &read_set) != 0) {
                while((read_size = read(fd, buff, 511)) > 0) {
                    printf("has read: %s\n", buff);
                    memset(buff, '\0', read_size);
                }
                break;
            }
        }
    }
    free(buff);
    close(fd);
    time_t end_time = time(NULL);
    printf("pselect is end, cost time: %lds\n", end_time - start_time);
}

int main() {
    before_test();
    io_test();
    select_test();
    pselect_test();
}