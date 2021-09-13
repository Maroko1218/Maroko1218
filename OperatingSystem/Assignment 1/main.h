#ifndef MAIN_H
#define MAIN_H

#include <semaphore.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    sem_t *full, *empty, *critical_sem;
    int *buffer, *id, *index, sleep;
} thread_args;

#endif /* MAIN_H */