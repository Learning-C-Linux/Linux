#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
//Return type may be of any type so that we have taken generic pointer
void* func(void* args)
{
    int val=*((int*)args);
    pthread_mutex_lock(&lock);
    printf("%d Hello\n",val);
    pthread_mutex_unlock(&lock);
    return NULL;
    
}
int main()
{
    pthread_t thread[3];
    int id[3]={1,2,3};
    pthread_mutex_init(&lock,NULL);
    for(int i=0;i<3;i++)
    {
	//address of thraed, thread attributes,function,value to passed
        pthread_create(&thread[i],NULL,func,&id[i]);
    }
    for(int i=0;i<3;i++)
    {
	//thread, Return value of the function
        pthread_join(thread[i],NULL);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}
