#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t 
#define BIG 1000000000UL
__uint32_t count = 0;

void *counter_to_big(void * arg)
{
    for(__uint32_t i = 0; i < BIG ; i++)
    {
        count++;
    }
    return (NULL);
}
int main()
{
    pthread_t thread;
    void *arg;
    pthread_create(&thread, NULL, counter_to_big, NULL);
    counter_to_big(arg);
    printf("Counter Done: count: %d\n", count);
    pthread_join(thread, NULL);
}