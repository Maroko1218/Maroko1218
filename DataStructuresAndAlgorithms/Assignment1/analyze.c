#include "analyze.h"
#include "algorithm.h"

#include <stdlib.h>
#include <limits.h>
#include <string.h>
//
// Private
//
typedef void(*algorithm_func_t)(int *arr, int listSize, ...);
#define ALGORITHM(fn) ((algorithm_func_t)fn)

void bench_press(result_t *result, int *arr, int listSize, const int *v, algorithm_func_t alg) {
    struct timespec gtstart, gtstop;
    double gttotal = 0;
    int *backup = malloc(sizeof(int)*listSize);
    memcpy(backup, arr, sizeof(int)*listSize);

    for (int i = 0; i < ITERATIONS; i++) {
        if (v == NULL) {
            clock_gettime(CLOCK_MONOTONIC, &gtstart);
            alg(arr, listSize);
            clock_gettime(CLOCK_MONOTONIC, &gtstop);
        } else {
            clock_gettime(CLOCK_MONOTONIC, &gtstart);
            alg(arr, listSize, *v);
            clock_gettime(CLOCK_MONOTONIC, &gtstop);
        }
        memcpy(arr, backup, sizeof(int)*listSize);
        gttotal += (((double)gtstop.tv_sec + 1.0e-9 * gtstop.tv_nsec) - ((double)gtstart.tv_sec + 1.0e-9 * gtstart.tv_nsec));
    }
    result->time = gttotal / ITERATIONS;
    free(backup);
}

void bench_bubble(const case_t c, result_t *result, int *arr, int listSize) {
    switch (c)
    {
    case best_t:
        for (int i = 0; i < listSize; i++) {
            arr[i] = i;
        }
        break;
    case worst_t:
        for (int i = 0; i < listSize; i++) {
            arr[i] = INT_MAX - i;
        }
        break;
    case average_t:
        srand(clock());
        for (int i = 0; i < listSize; i++) {
            arr[i] = rand();
        }
        break;
    }
    bench_press(result, arr, listSize, NULL, ALGORITHM(bubble_sort));
}

void bench_insertion(const case_t c, result_t *result, int *arr, int listSize) {
    switch (c)
    {
    case best_t:
        for (int i = 0; i < listSize; i++) {
            arr[i] = i;
        }
        break;
    case worst_t:
        for (int i = 0; i < listSize; i++) {
            arr[i] = INT_MAX - i;
        }
        break;
    case average_t:
        srand(clock());
        for (int i = 0; i < listSize; i++) {
            arr[i] = rand();
        }
        break;
    }
    bench_press(result, arr, listSize, NULL, ALGORITHM(insertion_sort));
}

void generate_quick_sort_best_case(int arr[], int begin, int end) {
    int count = end - begin;
    if (count < 3) {
        return;
    }

    int middle = (begin + end) / 2;

    generate_quick_sort_best_case(arr, begin, middle-1);
    int temp = arr[end];
    arr[end] = arr[middle];
    arr[middle] = temp;
    generate_quick_sort_best_case(arr, middle, end);  
}


void bench_quick(const case_t c, result_t *result, int *arr, int listSize) {
    switch (c)
    {
    case best_t:
        for (int i = 0; i < listSize; i++) {
            arr[i] = i+1;
        }
        generate_quick_sort_best_case(arr, 0, listSize);
        break;
    case worst_t:
        for (int i = 0; i < listSize; i++) {
            arr[i] = i;
        }
        break;
    case average_t:
        srand(clock());
        for (int i = 0; i < listSize; i++) {
            arr[i] = rand();
        }
        break;
    }
    bench_press(result, arr, listSize, NULL, ALGORITHM(quick_sort));
}

void bench_linear(const case_t c, result_t *result, int *arr, int listSize) {
    switch (c)
    {
    case best_t:
        arr[0] = 1;
        break;
    case worst_t:
        for (int i = 0; i < listSize; i++) {
            arr[i] = 2;
        }
        break;
    case average_t:
        srand(clock());
        for (int i = 0; i < listSize; i++) {
            arr[i] = 2;
        }
        arr[rand()%listSize] = 1;
        break;
    }
    const int search_val = 1;
    bench_press(result, arr, listSize, &search_val, ALGORITHM(linear_search));
}

void bench_binary(const case_t c, result_t *result, int *arr, int listSize) {
    for (int i = 0; i < listSize; i++) {
        arr[i] = i;
    }
    static int search_val = 1;
    switch (c)
    {
    case best_t:
        search_val = (listSize-1)/2;
        break;
    case worst_t:
        search_val = 0;
        break;
    case average_t:
        srand(clock());
        search_val = rand()%listSize;
        break;
    }
    bench_press(result, arr, listSize, &search_val, ALGORITHM(binary_search));
}
//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *result, int n) {
    int *arr = malloc(sizeof(int));
    int sampleSize;
    int multiplier = 2;
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            multiplier *= 2;
        }
        sampleSize = SIZE_START * multiplier/2;
        result[i].size = sampleSize;
        arr = realloc(arr, sizeof(int)*sampleSize);
        switch (a)
        {
        case bubble_sort_t:
            bench_bubble(c, &result[i], arr, sampleSize);
            break;
        case insertion_sort_t:
            bench_insertion(c, &result[i], arr, sampleSize);
            break;
        case quick_sort_t:
            bench_quick(c, &result[i], arr, sampleSize);
            break;
        case linear_search_t:
            bench_linear(c, &result[i], arr, sampleSize);
            break;
        case binary_search_t:
            bench_binary(c, &result[i], arr, sampleSize);
            break;
        }
    }
    free(arr);
}