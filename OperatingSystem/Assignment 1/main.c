#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 5

void* producer(void* args) {
    
}

void* consumer(void* args) {
    
}

int main(int argc, char const *argv[]) {
    int producer_count, consumer_count, buffer_size, sleep_duration;
    char input_buffer[BUFFER_SIZE];
    int isdone = 0;
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
        isdone = 1;
    } while(!isdone);

    sem_t full, empty;
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, buffer_size);
    pthread_t producers[producer_count];
    pthread_t consumers[consumer_count];
    char* buffer = malloc(sizeof(char[buffer_size]));

    

    for (size_t i = 0; i < producer_count; i++) {
        thread_args* args = malloc(sizeof(thread_args));
        args->full = full;
        args->empty = empty;
        args->buffer = buffer;
        if (pthread_create(&producers[i], NULL, &producer, args) != 0) {
            perror("Failed to create producer thread");
        }
    }
    for (size_t i = 0; i < consumer_count; i++) {
        thread_args* args = malloc(sizeof(thread_args));
        args->full = full;
        args->empty = empty;
        args->buffer = buffer;
        if (pthread_create(&consumers[i], NULL, &producer, args) != 0) {
            perror("Failed to create consumer thread");
        }   
    }
}