#include <pthread.h>
#include <stdio.h>
#include <unistd.h> //usleep
#include <stdlib.h>

unsigned int count = 1;

pthread_mutex_t lock;
void *thread_funct(void *arg)
{

    // usleep(1000000);
    int *x = (int*)arg;
    // printf("count %d\n", count);
    // if (count % 2)
    // {
    //     printf("%d Iam odd thread \n", *x);
    // }
    // else
    // {
    //     printf("%d Iam even thread \n", *x);
    // }
    for(int i = 0;i < 500;i++)
    {
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
    }
    return (NULL);
}

int main()
{
    int i;
    int j;
    pthread_t *threads;

    pthread_mutex_init(&lock,NULL);
    threads = malloc(4 * sizeof(pthread_t));
    // Create threads
    for (int i = 0; i < 100; i++)
    {
        j = i + 1;
        pthread_create(&threads[i], NULL, thread_funct, &j);
    }
    for (int i = 0; i < 100; i++)
    {
    pthread_join(threads[i], NULL);
    }
    // wait for threads
    // for (i = 0; i < 4; i++)
    // detach ressources
    printf("%u\n", count);
    printf("End threads\n");
}



// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
  
// pthread_t tid[2];
// int counter;
  
// void* trythis(void* arg)
// {
//     unsigned long i = 0;
//     counter += 1;
//     printf("\n Job %d has started\n", counter);
  
//     for (i = 0; i < (0xFFFFFFFF); i++)
//         ;
//     printf("\n Job %d has finished\n", counter);
  
//     return NULL;
// }
  
// int main(void)
// {
//     int i = 0;
//     int error;
  
//     while (i < 2) {
//         error = pthread_create(&(tid[i]), NULL, &trythis, NULL);
//         if (error != 0)
//             printf("\nThread can't be created : [%s]", strerror(error));
//         i++;
//     }
//     pthread_join(tid[0], NULL);
//     pthread_join(tid[1], NULL);
  
  
//     return 0;
// }
