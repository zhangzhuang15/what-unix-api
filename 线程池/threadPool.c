#include "threadPool.h"
#include <stdlib.h>
#include  <stdio.h>
#include <string.h>

// 创建线程池
// min: 最小线程数量
// max: 最大线程数量
// queueSize：任务队列容量
//
// 注意： 用完线程池，记得释放掉，以免内存泄露
ThreadPool* createThreadPool(int min, int max, int queueSize) {
    ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
    do
    {
        if(pool == NULL)
        {
            printf("malloc threadpool fail ....");
            break;
        }

        pool->threadIDs = (pthread_t*)malloc(sizeof(pthread_t) * max);
        if(pool->threadIDs == NULL)
        {
            printf("malloc threadIDs fail ....");
            break;
        }
        memset(pool->threadIDs, 0, sizeof(pthread_t) * max);
        pool->minNum = min;
        pool->maxNum = max;
        pool->busyNum = 0;
        pool->liveNum = min;
        pool->exitNum = 0;

        if(pthread_mutex_init(&pool->mutexPool, NULL) != 0 ||
           pthread_mutex_init(&pool->mutexBusy, NULL) != 0 ||
           pthread_cond_init(&pool->notEmpty, NULL) != 0 ||
           pthread_cond_init(&pool->notFull, NULL) != 0) 
        {
            printf("init mutex or cond fail ....");
            break;
        }
        pool->taskQ = (Task*)malloc(sizeof(Task) * queueSize);
        pool->queueCap = queueSize;
        pool->queueSize = 0;
        pool->queueFront = 0;
        pool->queueRear = 0;

        pool->shutdown = 0;

        // 开启管理线程
        pthread_create(&pool->managerID, NULL, manager, pool);

        // 开启工作线程
        for (int i = 0; i < min; i++) 
        {
            pthread_create(&pool->threadIDs[i], NULL, worker, pool);
        }
        return pool;
    } while (0);
 
    // pool 中部分创建成功，部分创建失败的情形下，需要free掉已经
    // 开辟的内存，以免内存泄露
    if(pool && pool->threadIDs) free(pool->threadIDs);
    if(pool && pool->taskQ) free(pool->taskQ);
    if(pool) free(pool);

    return NULL;
}

int destroyThreadPool(ThreadPool* pool) {
    if(pool == NULL) 
    {
        return -1;
    }

    pool->shutdown = 1;

    // 等待管理线程退出
    pthread_join(pool->managerID, NULL);

    for(int i = 0; i < pool->liveNum; i++) {
        // 发送任务队列非空条件，促使工作线程结束阻塞，
        // 之后这些线程完成手上的任务后，退出循环，结束线程
        pthread_cond_signal(&pool->notEmpty);
    }

    // 这一步是安全的，不会出现线程在获取任务，
    // 但任务队列free的情形。
    // 工作线程在结束阻塞后，会先判断 shutdown是否为1，
    // 如果为1，就会退出线程，
    // 否则才会获取队列中的任务。
    if(pool->taskQ) {
        free(pool->taskQ);
    }

    // 这里可以采用加入一个条件变量改善，
    // 或者采用cas判断
    while(pool->threadIDs && pool->liveNum != 0) {}
    free(pool->threadIDs);
    
    pthread_mutex_destroy(&pool->mutexBusy);
    pthread_mutex_destroy(&pool->mutexPool);
    pthread_cond_destroy(&pool->notEmpty);
    pthread_cond_destroy(&pool->notFull);

    free(pool);
    pool = NULL;

    return 0;
}

void commit(ThreadPool* pool, void (*function)(void* args), void* args) {
    pthread_mutex_lock(&pool->mutexPool);
    // 任务队列已经满了，同时线程池没有被shutdown,
    // 此时应该阻塞调用本函数的线程，别让他再往任务队列中加入新任务了
    while(pool->queueSize == pool->queueCap && !pool->shutdown) {
        pthread_cond_wait(&pool->notFull, &pool->mutexPool);
    }
    
    // 如果线程池被shutdown了，
    // 那么本线程就不需要提交新任务了，
    // 同时要释放锁，供工作线程使用
    if(pool->shutdown) {
        pthread_mutex_unlock(&pool->mutexPool);
        return;
    }

    // 提交任务

    // 往任务队列队尾加入任务，
    // 注意：queueRear指向的元素应该是空的
    pool->taskQ[pool->queueRear].function = function;
    pool->taskQ[pool->queueRear].args = args;
    // 别光后移指针，还要保证索引的合法性
    pool->queueRear = (pool->queueRear+1) % pool->queueCap;
    pool->queueSize++;

    pthread_cond_signal(&pool->notEmpty);
    pthread_mutex_unlock(&pool->mutexPool);
}

int busyNum(ThreadPool* pool) {
    // 上锁，防止读取数据的时候，别的线程修改数据
    pthread_mutex_lock(&pool->mutexBusy);
    // 已经保存到局部变量中了，数据安全啦
    int busyNumber = pool->busyNum;
    pthread_mutex_unlock(&pool->mutexBusy);
    return busyNumber;
}

int aliveNum(ThreadPool* pool) {
    pthread_mutex_lock(&pool->mutexPool);
    int aliveNumber = pool->liveNum;
    pthread_mutex_unlock(&pool->mutexPool);
    return aliveNumber;
}

// 工作线程实现，
// 同时可以看到我们是预先知道 args指的就是 ThreadPool* 类型变量哦
void* worker(void* args) {
     // pool是不是 NULL，交给调用 worker 函数 的 上层函数判断
    ThreadPool* pool = (ThreadPool*)args;


    // 死循环，线程会不会一直消耗CPU？
    // 放心，循环里边会提供阻塞线程的方法，
    // 线程一旦被阻塞，就会挂起，不会继续占用CPU
    while(1) {
        pthread_mutex_lock(&pool->mutexPool);

        while(pool->queueSize == 0 && !pool->shutdown) {
            // 任务队列是空的，阻塞线程，释放锁
            pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);

            // 只有管理线程会令 pool->exitNum > 0,
            // 这表示管理线程检测到线程数量太多，
            // 希望删除一些线程。
            // 那么，工作线程应该去给出这个判断，
            // 配合管理线程，删除自己
            if(pool->exitNum > 0) {
                pool->exitNum--;
                if(pool->liveNum > pool->minNum) {
                    pool->liveNum--;
                    pthread_mutex_unlock(&pool->mutexPool);
                    // 内部会调用 pthread_exit函数，直接退出线程，
                    // 所以不需要考虑 break 循环。
                    exitOneThread(pool);
                }
            }
        }
        
        if(pool->shutdown) {
            pthread_mutex_unlock(&pool->mutexPool);
            exitOneThread(pool);
        }

        Task task;
        task.function = pool->taskQ[pool->queueFront].function;
        task.args = pool->taskQ[pool->queueFront].args;

        pool->queueFront = (pool->queueFront+1) % pool->queueCap;
        pool->queueSize--;

        pthread_cond_signal(&pool->notFull);
        pthread_mutex_unlock(&pool->mutexPool);

        // 该执行任务了，所以该忙起来了
        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum++;
        pthread_mutex_unlock(&pool->mutexBusy);

        task.function(task.args);
        free(task.args);
        task.args = NULL;

        // 任务执行完毕了，所以不忙了
        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexBusy);
    }
    return NULL;
}


// 管理线程
void* manager(void* args) {
    // pool是不是 NULL，交给调用 manager函数 的 上层函数判断
    ThreadPool* pool = (ThreadPool*)args;

    while(!pool->shutdown){
        // 每 3s 执行一下
        sleep(3);

        pthread_mutex_lock(&pool->mutexPool);
        int queueSize = pool->queueSize;
        int liveNumber = pool->liveNum;
        pthread_mutex_unlock(&pool->mutexPool);

        pthread_mutex_lock(&pool->mutexBusy);
        int busyNumber = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);

        // 工作线程相对于任务数量少了，要创建新线程
        if(queueSize > liveNumber && liveNumber < pool->maxNum) {
             pthread_mutex_lock(&pool->mutexPool);
             int counter = 0;
             for(int i = 0; i < pool->maxNum && pool->liveNum < pool->maxNum && counter < NUMBER; i++) {
                 if(pool->threadIDs[i] == 0) {
                     pthread_create(pool->threadIDs[i], NULL, worker, pool);
                     counter++;
                     pool->liveNum++;
                 }
             }
             pthread_mutex_unlock(&pool->mutexPool);
        }

        // 正在执行任务的线程数量不满工作线程数量的一半，
        // 说明线程多了，应该减少线程
        if(busyNumber * 2 < liveNumber && liveNumber > pool->minNum){
              pthread_mutex_lock(&pool->mutexPool);
              pool->exitNum = NUMBER;
              pthread_mutex_unlock(&pool->mutexPool);

              for(int i = 0; i < NUMBER; i++) {
                  pthread_cond_signal(&pool->notEmpty);
              }
        }
    }
    return NULL;
}

void exitOneThread(ThreadPool* pool) {
    // 获取当前线程id
    pthread_t tid = pthread_self();

    for(int i = 0; i < pool->maxNum; i++) {
        if(pool->threadIDs[i] == tid) {
            pool->threadIDs[i] = 0;
            break;
        }
    }

    pool->liveNum--;
    // 结束线程
    pthread_exit(NULL);
}