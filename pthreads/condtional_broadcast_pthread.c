#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condt = PTHREAD_COND_INITIALIZER;

void* func(void* args)
{
    int val = *((int*)args);
    int range = 20;
    int prime;

    pthread_mutex_lock(&lock);

    if (range == 1 || range == 0)
    {
        printf("%d ", range);
        pthread_mutex_unlock(&lock);
        return NULL;
    }

    for (int i = 2; i <= range; i++)
    {
        prime = 1;
        for (int j = 2; j <= i / 2; j++)
        {
            if (i % j == 0)
            {
                prime = 0;
                break;
            }
        }

        if (prime)
        {
            printf("Thread %d: %d\n", val, i);
            pthread_cond_broadcast(&condt); 
        }
        
    }

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{
    pthread_t threads[3];
    int ids[3];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 3; i++)
    {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, func, &ids[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&condt);
    return 0;
}

