#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condt = PTHREAD_COND_INITIALIZER;

int current = 2;       // current number to check
int turn = 0;          // whose turn (0, 1, 2)
int max_range = 20;

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int j = 2; j <= n / 2; j++) {
        if (n % j == 0) return 0;
    }
    return 1;
}

void* func(void* args) {
    int id = *((int*)args);

    while (1) {
        pthread_mutex_lock(&lock);

        // Wait for your turn
        while (turn != id && current <= max_range) {
            pthread_cond_wait(&condt, &lock);
        }

        // Exit if done
        if (current > max_range) {
            pthread_mutex_unlock(&lock);
            pthread_cond_signal(&condt); // wake someone else to exit
            return NULL;
        }

        if (is_prime(current)) {
            printf("Thread %d: %d\n", id + 1, current);
        }

        current++;
        turn = (turn + 1) % 3;  // Give turn to next thread

        pthread_cond_signal(&condt); // wake the next thread
        pthread_mutex_unlock(&lock);
    }
}

int main() {
    pthread_t threads[3];
    int ids[3] = {0, 1, 2};

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, func, &ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&condt);

    return 0;
}

