#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>

int main(int argc, char *argv[]){
    unsigned long long i, cur, page_number;
    unsigned long long N = 1000;
    int MISS_EVERY = 0;
    int count, page_size, max_array_page_size;
    double *arr;
    double res;
    clock_t start, end;
    double cpu_time_used;

    N = atoll(argv[1]);
    MISS_EVERY = atoi(argv[2]);

    page_size = getpagesize();
    max_array_page_size = page_size / sizeof(arr);

    arr = (double*) calloc(N, sizeof(arr));

    srand(time(0));

    for (i = 0; i < N; i++){
        arr[i] = (double) rand() / INT_MAX;
    }

    res = 0, cur = 0, count = 0, page_number = 0;

    start = clock();
    for (i = 0; i < N; ++i){
        if (MISS_EVERY != 0 && count == MISS_EVERY){
            count = 0;
            ++page_number;
        }

        cur = page_number * max_array_page_size + count;

        if (cur >= N){
            page_number = 0;
            cur = 0;
        }

        res += arr[cur];

        ++count;
    }
    end = clock();

    cpu_time_used = ((double) end - start) / CLOCKS_PER_SEC;

    printf("sec = %f, res = %f\n", cpu_time_used, res);

    return 0;
}
