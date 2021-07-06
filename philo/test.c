#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *myturn(void *arg){

    while (1)
    {
        sleep(1);
        printf("my turn\n");
    }
    return (NULL);
}

void yourturn(){

    while (1)
    {
        sleep(1);
        printf("your turn\n");
    }
}

int main()
{
    pthread_t new_thread;

    pthread_create(&new_thread, NULL, myturn, NULL);
    yourturn();
}