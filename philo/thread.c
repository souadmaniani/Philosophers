#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
 
void* thread1(void *arg)
{
    while (1)
    {
        usleep(100 * 1000);
        write(1, "thread1 running...!\n", strlen("thread1 running...!\n"));
    }
    write(1, "Leave thread1!\n", strlen("Leave thread1!\n"));
 
    return NULL;
}
 
int main(int argc, char** argv)
{
    pthread_t tid;
 
    pthread_create(&tid, NULL, (void*)thread1, NULL);
    // pthread_detach(tid); // Make the thread detached
    sleep(1);
    write(1, "Leave main thread!\n", strlen("Leave main thread!\n"));
}
