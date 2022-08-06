// 代码并非原创，仅供学习借鉴，记录在此，
// 如果原作者有意见，请在github上留言，
// 将尽快删除。

#ifndef THREADPOOL
#define THREADPOOL

#include <pthread.h>

// 定义每次新加入线程或者减少的线程数量
#define NUMBER 3

typedef struct Task {
    void (*function)(void* args);
    void* args;
} Task;


typedef struct ThreadPool {
    // 任务队列
    Task* taskQ;

    // 任务队列的容量
    int queueCap;
    // 任务对列中任务的个数
    int queueSize;
    // 队列头索引 -> 取任务的地方
    int queueFront;
    // 队列尾索引 -> 存任务的地方
    int queueRear;

    pthread_t managerID;  // 管理者线程ID
    pthread_t *threadIDs; // 工作线程ID数组
    int minNum;           // 最小工作线程数
    int maxNum;           // 最大工作线程数
    int busyNum;          // 正在执行任务的线程数量
    int liveNum;          // 存活的线程数量（可能在执行任务，也可能在等待任务）
    int exitNum;          // 死亡的线程数量
    pthread_mutex_t mutexPool; // 锁住整个线程池
    pthread_mutex_t mutexBusy; // 锁住 busyNum， 同步其读写操作
    pthread_cond_t notFull;    // 任务队列没有满载，唤醒线程；否则阻塞线程
    pthread_cond_t notEmpty;   // 任务队列非空，唤醒线程；否则阻塞线程

    int shutdown;         // 是否销毁线程池， 1 销毁， 0 不销毁

} ThreadPool;

ThreadPool* createThreadPool(int min, int max, int queueSize);

int destroyThreadPool(ThreadPool* pool);

void exitOneThread(ThreadPool* pool);

void commit(ThreadPool* pool, void (*function)(void* args), void* args);

int busyNum(ThreadPool* pool);

int aliveNum(ThreadPool* pool);

void* worker(void* args);

void* manager(void* args);
#endif