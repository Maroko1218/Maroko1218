#include "main.h"

#define INPUT_BUFFER_SIZE 5

void* producer(void* args) {
    sem_t *full = ((thread_args*)args)->full, *empty = ((thread_args*)args)->empty, *critical_sem = ((thread_args*)args)->critical_sem;
    int id = *(((thread_args*)args)->id), *buffer = ((thread_args*)args)->buffer, sleep_duration = ((thread_args*)args)->sleep, *index = ((thread_args*)args)->index;
    free(((thread_args*)args)->id);
    free((thread_args*)args);
    printf("Producer thread: %d initialized\n", id);
    while (true) {
        sleep(sleep_duration);
        sem_wait(empty);
        sem_wait(critical_sem); //This could've been a mutex instead
        buffer[(*index)++] = id;
        sem_post(critical_sem);
        sem_post(full);
    }
}

void* consumer(void* args) {
    sem_t *full = ((thread_args*)args)->full, *empty = ((thread_args*)args)->empty, *critical_sem = ((thread_args*)args)->critical_sem;
    int id = *(((thread_args*)args)->id), *buffer = ((thread_args*)args)->buffer, *index = ((thread_args*)args)->index, produce;
    free(((thread_args*)args)->id);
    free((thread_args*)args);
    printf("Consumer thread: %d initialized\n", id);
    while (true) {
        sem_wait(full);
        sem_wait(critical_sem); //This could've been a mutex instead
        produce = buffer[--(*index)];
        buffer[*index] = 0;
        printf("Consumer thread: %d just consumed: %d\n", id, produce);
        sem_post(critical_sem);
        sem_post(empty);
    }
}

int main(int argc, char const *argv[]) {
    int producer_count, consumer_count, buffer_size, sleep_duration;
    char input_buffer[INPUT_BUFFER_SIZE];
    bool isdone = false;
    do {
        printf("How many producer threads: ");
        fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
        producer_count = atoi(input_buffer);
        printf("How many consumer threads: ");
        fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
        consumer_count = atoi(input_buffer);
        printf("How big is the buffer: ");
        fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
        buffer_size = atoi(input_buffer);
        printf("How long do producers sleep: ");
        fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
        sleep_duration = atoi(input_buffer);
        if (producer_count <= 0 || consumer_count <= 0 || buffer_size <= 0 || sleep_duration <= 0) {
            continue;
        }
        isdone = true;
    } while(!isdone);

    sem_t *full = malloc(sizeof(sem_t)), *empty = malloc(sizeof(sem_t)), *critical_sem = malloc(sizeof(sem_t));
    sem_init(full, 0, 0);
    sem_init(empty, 0, buffer_size);
    sem_init(critical_sem, 0, 1);
    pthread_t producers[producer_count];
    pthread_t consumers[consumer_count];
    int *buffer = calloc(buffer_size, sizeof(int)), *index = malloc(sizeof(int));
    *index = 0;
    for (size_t i = 0; i < producer_count; i++) {
        thread_args* args = malloc(sizeof(thread_args));
        int* a = malloc(sizeof(int));
        *a = i + 1;
        args->full = full;
        args->empty = empty;
        args->critical_sem = critical_sem;
        args->id = a;
        args->buffer = buffer;
        args->sleep = sleep_duration;
        args->index = index;
        assert(pthread_create(&producers[i], NULL, &producer, args) == 0);
    }
    for (size_t i = 0; i < consumer_count; i++) {
        thread_args* args = malloc(sizeof(thread_args));
        int* a = malloc(sizeof(int));
        *a = i + 1;
        args->full = full;
        args->empty = empty;
        args->critical_sem = critical_sem;
        args->id = a;
        args->buffer = buffer;
        args->index = index;
        assert(pthread_create(&consumers[i], NULL, &consumer, args) == 0);  
    }
    while(true);
}