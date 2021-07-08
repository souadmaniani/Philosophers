#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// Mutex is a simple method of locking to control access to shared resources
#define BIG 1000000000UL
unsigned int count = 0;
// PTHREAD_MUTEX_INITIALIZER The macro does not perform error checking.
// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock;
void *counter_to_big(void * arg)
{
    for(unsigned int i = 0; i < BIG ; i++)
    {
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
    }
    return (NULL);
}
int main()
{
    pthread_t thread;
      
    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread, NULL, counter_to_big, NULL);
    counter_to_big(NULL);
    pthread_join(thread, NULL);
    printf("Counter Done: count: %d\n", count);
}