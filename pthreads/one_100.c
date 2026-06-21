#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // for sleep()

pthread_mutex_t lock;

void* func_point(void *args)
{
    pthread_mutex_lock(&lock);
    printf("Thread ID: %lu\n", (unsigned long)pthread_self());

    for (int i = 0; i < 100; i++)
    {
        printf("%d ", i);
    }
    pthread_mutex_unlock(&lock);
    sleep(2);
    pthread_mutex_lock(&lock);
    printf("Thread ID: %lu\n", (unsigned long)pthread_self());

    for (int i = 100; i>0; i--)
    {
        printf("%d ", i);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{
    pthread_t thread[2];
    long int n;

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 2; i++)
    {
        pthread_create(&thread[i], NULL, func_point, NULL);  // No ids used
        // n=pthread_self();
        // printf("%lu ",n);   //you can checxk any where
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(thread[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}

