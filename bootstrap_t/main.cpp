#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void *incrementCounter(void *arg)
{
    //pthread_mutex_lock(&lock);
    int *i = (int *)arg;
    int j = 0;
    counter += 1;
    printf("Job %d has started\n", counter);
    while (j < 100) {
        j++;
        *i += 1;
    }
    printf("Job %d has finished\n", counter);
    //pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void)
{
    int x = 0;
    int i;
    int error;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("mutex init has failed\n");
        return 1;
    }
    for (i = 0; i < 2; i++) {
        error = pthread_create(&(tid[i]), NULL, &incrementCounter, &x);
        if (error != 0)
            printf("Thread can't be created :[%s]", strerror(error));
    }
    for (i = 0; i < 1; i++)
        pthread_join(tid[i], NULL);
    printf("%d\n", x);
    pthread_mutex_destroy(&lock);
    return 0;
}
