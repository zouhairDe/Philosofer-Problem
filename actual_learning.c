#include <pthread.h>
#include <stdio.h>

pthread_mutex_t   lock;

void    *pfff(void *arg)
{
    // pthread_mutex_lock(&lock);
    printf("Hello, World!\n");
    printf("Hello, World!\n");
    printf("Hello, World!\n");
    // pthread_mutex_unlock(&lock);
    printf("Hello, Wo ftuf ,tfjtmld!\n");
    printf("Hello, Wo ftuf ,tfjtmld!\n");
    printf("Hello, Wo ftuf ,tfjtmld!\n");
    return (NULL);
}
int main(void)
{
    pthread_t tid1, tid2;

    // pthread_mutex_init(&lock, NULL);
    pthread_create(&tid1, NULL, pfff, NULL);
    pthread_create(&tid2, NULL, pfff, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return (0);
}
