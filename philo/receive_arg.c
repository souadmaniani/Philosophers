#include <pthread.h>
#include <stdio.h>
#include <unistd.h> //usleep
#include <stdlib.h>
void *myturn(void *arg){

    int *ptr = malloc(sizeof(int));
    *ptr = 5;
   for (int i = 1; i < 9; i++)
    {
        usleep(1000000);
        printf("my turn %d %d\n", i, *ptr);
        (*ptr)++;
    }
    return (ptr);
}

void yourturn(){

    for(int i = 1; i < 3; i++)
    {
        usleep(1000000);
        printf("your turn %d \n", i);
    }
}

int main()
{
    int *result;
    pthread_t new_thread;
    // I can pass argument to thread
    pthread_create(&new_thread, NULL, myturn, NULL);
    yourturn();
    // wait until the thread is done before we exit and get argument from thread
    pthread_join(new_thread, (void *)&result);
    printf("new_thread done: *result: %d\n", *result);
}