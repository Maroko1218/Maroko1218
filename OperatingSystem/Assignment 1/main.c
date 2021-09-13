#include "main.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 5

void* producer(void* args) {
    int id = *(((thread_args*)args)->id) + 1;
    sem_t *full = ((thread_args*)args)->full, *empty = ((thread_args*)args)->empty;
    int *buffer = ((thread_args*)args)->buffer;
    int sleep_duration = ((thread_args*)args)->sleep;
    free(((thread_args*)args)->id);
    free((thread_args*)args);
    printf("Hello I am producer thread %d!\n", id);
    int *index;
    while (true) {
        sleep(sleep_duration);
        sem_wait(empty);
        *buffer = id;
        buffer++;
        sem_post(full);
    }
}

void* consumer(void* args) {
    int id = *(((thread_args*)args)->id) + 1;
    sem_t *full = ((thread_args*)args)->full, *empty = ((thread_args*)args)->empty;
    int *buffer = ((thread_args*)args)->buffer;
    free(((thread_args*)args)->id);
    free((thread_args*)args);
    printf("Hello I am consumer thread %d!\n", id);
    int *index;
    int produce;
    while (true) {
        sem_wait(full);
        buffer--;
        produce = *buffer;
        printf("Hello I am consumer thread %d! I just ate: %d!\n", id, produce);
        sem_post(empty);
    }
}

int main(int argc, char const *argv[]) {
    int producer_count, consumer_count, buffer_size, sleep_duration;
    char input_buffer[BUFFER_SIZE];
    bool isdone = false;
    do {
        printf("How many producer threads: ");
        fgets(input_buffer, BUFFER_SIZE, stdin);
        producer_count = atoi(input_buffer);
        printf("How many consumer threads: ");
        fgets(input_buffer, BUFFER_SIZE, stdin);
        consumer_count = atoi(input_buffer);
        printf("How big is the buffer: ");
        fgets(input_buffer, BUFFER_SIZE, stdin);
        buffer_size = atoi(input_buffer);
        printf("How long do producers sleep: ");
        fgets(input_buffer, BUFFER_SIZE, stdin);
        sleep_duration = atoi(input_buffer);
        if (producer_count <= 0 || consumer_count <= 0 || buffer_size <= 0 || sleep_duration <= 0) {
            continue;
        }
        isdone = true;
    } while(!isdone);

    sem_t *full = malloc(sizeof(sem_t)), *empty = malloc(sizeof(sem_t));
    sem_init(full, 0, 0);
    sem_init(empty, 0, buffer_size);
    pthread_t producers[producer_count];
    pthread_t consumers[consumer_count];
    int* buffer = calloc(buffer_size, sizeof(int));

    

    for (size_t i = 0; i < producer_count; i++) {
        thread_args* args = malloc(sizeof(thread_args));
        int* a = malloc(sizeof(int));
        *a = i;
        args->full = full;
        args->empty = empty;
        args->buffer = buffer;
        args->id = a;
        args->sleep = sleep_duration;
        assert(pthread_create(&producers[i], NULL, &producer, args) == 0);
    }
    for (size_t i = 0; i < consumer_count; i++) {
        thread_args* args = malloc(sizeof(thread_args));
        int* a = malloc(sizeof(int));
        *a = i;
        args->full = full;
        args->empty = empty;
        args->buffer = buffer;
        args->id = a;
        assert(pthread_create(&consumers[i], NULL, &consumer, args) == 0);  
    }
    while(true);
}