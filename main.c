#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

const int PAGE_SIZE = 4096;
const int MAX_ARRAY_SIZE_PAGE = PAGE_SIZE / sizeof(double);

int main(int argc, char *argv[]){
    int i, j, cur, count, page_number;
    int N = 1000, MAX_DELTA = 1000, MISS_EVERY = 1;
    double *arr;
    double res;
    clock_t start, end;
    double cpu_time_used;

    N = atoi(argv[1]);
    MAX_DELTA = atoi(argv[2]);
    MISS_EVERY = atoi(argv[3]);

    arr = (double*) calloc(N, sizeof(double));

    srand(time(0));

    for (i = 0; i < N; i++){
        arr[i] = (double) rand() / INT_MAX;
    }

    for (j = 0; j <= 1024; j++){
        res = 0, cur = 0, count = 0, page_number = 0;

        start = clock();
        for (i = 0; i < N; i++){
            if (j != 0 && count == j){
                count = 0;
                page_number++;
            }

            cur = page_number * MAX_ARRAY_SIZE_PAGE + count;

            if (cur >= N){
                page_number = 0;
                cur = 0;
            }

            //printf("%d\n", cur);

            res += arr[cur];

            count++;
        }
        end = clock();

        cpu_time_used = ((double) end - start) / CLOCKS_PER_SEC; 

        printf("miss every = %d, sec = %f, res = %f\n", j, cpu_time_used, res);
    }

    return 0;
}