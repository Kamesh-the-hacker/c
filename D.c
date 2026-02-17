#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5   // Number of philosophers

pthread_mutex_t fork[N];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Deadlock prevention: even pick right first
        if (id % 2 == 0) {
            pthread_mutex_lock(&fork[right]);
            pthread_mutex_lock(&fork[left]);
        } else {
            pthread_mutex_lock(&fork[left]);
            pthread_mutex_lock(&fork[right]);
        }

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        pthread_mutex_unlock(&fork[left]);
        pthread_mutex_unlock(&fork[right]);

        printf("Philosopher %d finished eating\n", id);
    }
}

int main() {
    pthread_t ph[N];
    int id[N];

    for (int i = 0; i < N; i++)
        pthread_mutex_init(&fork[i], NULL);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(ph[i], NULL);

    return 0;
}
