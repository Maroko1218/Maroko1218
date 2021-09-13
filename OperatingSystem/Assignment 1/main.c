#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 5

//test comment
void* routine(void* args) {
    printf("Hello I am thread %d!\n", *(int*)args);
    sleep(1);
    printf("Goodbye! I was thread %d!\n", *(int*)args);
    free(args);
}

int main(int argc, char const *argv[]) {
    pthread_t th[NUM_THREADS];
    for (size_t i = 0; i < NUM_THREADS; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        pthread_create(&th[i], NULL, &routine, a);
    }
    for (size_t i = 0; i < NUM_THREADS; i++) {
        pthread_join(th[i], NULL);
    }
    
    return 0;
}
