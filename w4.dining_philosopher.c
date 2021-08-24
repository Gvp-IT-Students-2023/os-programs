#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t forks[5];
sem_t room;

void *philosopher(void *arg)
{
    int i = *(int*)arg;
    sem_wait(&room);
    printf("Philosopher %d has entered room\n", i);
    sem_wait(&forks[i]);
    sem_wait(&forks[(i + 1) % 5]);
    printf("Philosopher %d is eating\n", i);
    sleep(2);
    printf("Philosopher %d finished eating\n", i);
    sem_post(&forks[(i + 1) % 5]);
    sem_post(&forks[i]);
    sem_post(&room);
}

int main()
{
    pthread_t tid[5];
    sem_init(&room, 0, 4);
    for (int i = 0; i < 5; i++)
        sem_init(&forks[i], 0, 1);

    int a[5];
    for (int i = 0; i < 5; i++)
    {
        a[i] = i;
        pthread_create(&tid[i], NULL, philosopher, (void *)&a[i]);
    }

    for (int i = 0; i < 5; i++)
        pthread_join(tid[i], NULL);
    return 0;
}
