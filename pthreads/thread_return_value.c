//Thread with return value
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t lock;

void* func(void* args)
{
    int val=*((int*)args);
    pthread_mutex_lock(&lock);
    int* res = malloc(sizeof(int)); // allocate memory for result
    *res = val + 1;
    pthread_mutex_unlock(&lock);
    return res;
}

int main()
{
    pthread_t thread[3];
    int ids[3];
    // mutex → The lock you want to set up so threads can use it.
    //Use NULL if you just want the normal/default lock.
    pthread_mutex_init(&lock,NULL);
    for(int i=0;i<3;i++)
    {
        ids[i] = i + 1;
        pthread_create(&thread[i],NULL,func,&ids[i]);
    }
    for(int i=0;i<3;i++)
    {
        int *res;
        pthread_join(thread[i],(void**)&res);
        printf("Result of thread %d is: %d\n",i,*res);
        free(res);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}

