#include <stdio.h>
#include <pthread.h>
pthread_mutex_t lock;

void* func_point(void *args)
{
    pthread_mutex_lock(&lock);
    for(int i=0;i<100;i++)
    {
        printf("%d ",i);
    }
    pthread_mutex_unlock(&lock);
    return NULL; 
}
int main()
{
    pthread_t thread[2];
    int ids[2]={1,2};
    pthread_mutex_init(&lock,NULL);
    for(int i=0;i<2;i++)
    {
        pthread_create(&thread[i],NULL,func_point,&ids[i]);
    }
    for(int i=0;i<2;i++)
    {
        pthread_join(thread[i],NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;

}
