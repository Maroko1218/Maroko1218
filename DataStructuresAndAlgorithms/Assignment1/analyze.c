#include "analyze.h"
#include "algorithm.h"

//
// Private
//
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
    clock_t start = clock();
    bubble_sort(arr, listSize);
    clock_t stop = clock();
    result->time = (double)(stop - start) / CLOCKS_PER_SEC;
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
    clock_t start = clock();
    insertion_sort(arr, listSize);
    clock_t stop = clock();
    result->time = (double)(stop - start) / CLOCKS_PER_SEC;
}

void bench_quick(const case_t c, result_t *result, int *arr, int listSize) {

}

void bench_linear(const case_t c, result_t *result, int *arr, int listSize) {
    clock_t start, stop;
    switch (c)
    {
    case best_t:
        arr[0] = 1;
        start = clock();
        linear_search(arr, listSize, 1);
        stop = clock();
        break;
    case worst_t:
        for (int i = 0; i < listSize; i++) {
            arr[i] = 1;
        }
        start = clock();
        linear_search(arr, listSize, 2);
        stop = clock();
        break;
    case average_t:
        srand(clock());
        for (int i = 0; i < listSize; i++) {
            arr[i] = rand()%listSize;
        }
        start = clock();
        linear_search(arr, listSize, rand()%listSize);
        stop = clock();
        break;
    }
    result->time = (double)(stop - start) / CLOCKS_PER_SEC;
}

void bench_binary(const case_t c, result_t *result, int *arr, int listSize) {
    clock_t start, stop;
    switch (c)
    {
    case best_t:
        for (int i = 0; i < listSize; i++) {
            arr[i] = 1;
        }
        start = clock();
        binary_search(arr, listSize, 1);
        stop = clock();
        break;
    case worst_t:
        for (int i = 0; i < listSize; i++) {
            arr[i] = i;
        }
        start = clock();
        binary_search(arr, listSize, listSize-1);
        stop = clock();
        break;
    case average_t:
        srand(clock());
        for (int i = 0; i < listSize; i++) {
            arr[i] = rand()%listSize;
        }
        bubble_sort(arr, listSize);
        start = clock();
        binary_search(arr, listSize, rand()%listSize);
        stop = clock();
        break;
    }
    result->time = (double)(stop - start) / CLOCKS_PER_SEC;
}
//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *result, int n)
{
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
