#ifndef MAIN_H
#define MAIN_H

#include <semaphore.h>


typedef struct {
    sem_t *full, *empty;
    int* buffer;
    int* id;
    int sleep;
} thread_args;

#endif /* MAIN_H */