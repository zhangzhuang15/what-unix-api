#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int main() {
    /* 记录当前处理器时钟个数 */
    clock_t start = clock();
    for (int i = 0; i < 5; i++) { sleep(1);}
    clock_t end = clock();
    /* 换算成秒， CLOCKS_PER_SEC表示每秒中处理器的时钟个数  */
    double total = (double)(end - start)/CLOCKS_PER_SEC;
    printf("total time: %.3fs \n", total);



    time_t start_t, end_t;
    /* 计算当前到 1970-01-01 00:00:00相差的秒数 
       注意，该计算不是直接用本时区的时间，而是将本时区
       的时间转换为UTC0时区的时间后，再计算秒数
    */
    start_t = time(NULL);
    for (int i = 0; i < 5; i++) { sleep(1);}
    end_t = time(NULL);
    printf("another total time: %lds\n", end_t-start_t);
    printf("hour: %ld\n", (start_t/3600)%24); /* 打印出来的数字和本地时间差出来8小时*/


    
    time_t current_t;
    time(&current_t);
    /* 将current_t 表示的秒数转换为当地时间的时间字符串 */
    char *t1 = ctime(&current_t);
    char *t2 = ctime(&current_t);
    printf("t1 : %s \n", t1);
    printf("t2 : %s \n", t2);



    struct tm t;
    t.tm_hour = 10;  /* 10点 */
    t.tm_min = 30;   /* 30分 */
    t.tm_sec = 50;   /* 50秒 */
    t.tm_year = 121; /* 2021-1900 = 121 */
    t.tm_mon = 9;    /* 10月 */
    t.tm_mday = 1;   /* 1日 */
    t.tm_wday = 0;   /* 周日 */
    /* 将t定义的时间组成一个当地时间的时间字符串
       该函数认为 t就是当前时区下的时间信息，不会做时间转换
     */
    char *t3 = asctime(&t);
    printf("t3 we defined : %s \n", t3);
    // free(t3);  报错， 表示asctime返回的字符串不是使用malloc


    current_t = time(NULL);
    /* 将 time_t 转换成 struct tm 结构体, 里面的时间信息按照UTC0时区计算 */
    struct tm *curr = gmtime(&current_t);
    printf("UTC-0 year: %d\n", curr->tm_year);
    printf("UTC-0 hour: %d\n", curr->tm_hour);
    printf("UTC-0 second: %d\n", curr->tm_sec);
    printf("UTC-0 weekday: %d\n", curr->tm_wday);
    /* 将 time_t 转换成 struct tm 结构体, 里面的时间信息按照当地时区计算 */
    curr = localtime(&current_t);
    printf("local hour: %d\n", curr->tm_hour);



    struct tm m;
    m.tm_year = 121;
    m.tm_hour = 10;
    m.tm_mon = 5;
    m.tm_mday = 13;
    m.tm_min = 30;
    /* 将 struct tm -> time_t */
    current_t = mktime(&m);
    printf("current time : %ld\n",(current_t/3600)%24);
    struct tm *tmp1 = gmtime(&current_t);
    printf("converted year: %d\n", tmp1->tm_year);



    char buffer[20];
    time_t now;
    time(&now);
    struct tm *tp = localtime(&now);
    /* 按照格式"%Y-%m-%d %H:%M:%S"将 tp指向的struct tm 信息写入到buffer中，只写入15个字节 */
    strftime(buffer, 15, "%Y-%m-%d %H:%M:%S", tp);
    printf("buffer[0~14] : %s\n", buffer);
    printf("year: %d\n", tp->tm_year);


    /* 总结一下：
       获取当前本时区的时间字符串   
                time_t t; 
                time(&t); 
                ctime(&t);
                
       获取当前本时区的时间结构体
                time_t t;
                time(&t);
                localtime(&t);

       获取当前UTC时区的时间结构体:
                time_t t;
                time(&t);
                gmtime(&t);
                
       将一个时间结构体转换为本时区的时间字符串：
                struct tm t;
                asctime(&t);
                */
}