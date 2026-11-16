#define _POSIX_C_SOURCE 199309L

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SEED 123
// #define MAX_DATA_VALUE 999
#define MAX_DATA_VALUE RAND_MAX
#define QS_LIMIT_START 2
#define QS_LIMIT_MAX 32

void generateData(int *const data, unsigned int n);
void printArray(int *const array, unsigned int size);

void testAlgorithm(const int *const reference_data, const unsigned int size);
void qsWarmup();

void swap(int *a, int *b);
int compareIntsDesc(const void *a, const void *b);

void quickSortNormal(int *const array, int p, int q);
void quickSortLimited(int *const array, int p, int q, const unsigned int limit);
int qsPartition(int *const array, int p, int q);

void bubbleSort(int *const array, unsigned int n);

int main(int argc, char *argv[])
{
    const int test_size[] = {
        10000,
        50000,
        100000,
        150000,
    };

    // const int test_size[] = {
    //     20,
    // };

    const unsigned int test_len = sizeof(test_size) / sizeof(test_size[0]);

    int *test_case_data = NULL;

    setvbuf(stdout, NULL, _IONBF, 0);
    srand(SEED);
    qsWarmup();

    printf("SEED %d\n", SEED);

    printf("%-8s\t%-11s", "size", "normalny");

    for (int i = QS_LIMIT_START; i < QS_LIMIT_MAX; i = i * 2)
    {
        printf("\tc=%-9d", i);
    }

    printf("\nDANE LOSOWE\n");

    for (unsigned int i = 0; i < test_len; i++)
    {
        test_case_data = malloc(sizeof(int) * test_size[i]);

        generateData(test_case_data, test_size[i]);

        testAlgorithm(test_case_data, test_size[i]);

        free(test_case_data);
        test_case_data = NULL;
    }

    printf("DANE NIEKORZYSTNE\n");

    for (unsigned int i = 0; i < test_len; i++)
    {
        test_case_data = malloc(sizeof(int) * test_size[i]);

        generateData(test_case_data, test_size[i]);
        qsort(test_case_data, test_size[i], sizeof(int), compareIntsDesc);

        testAlgorithm(test_case_data, test_size[i]);

        free(test_case_data);
        test_case_data = NULL;
    }

    return 0;
}

void generateData(int *const data, unsigned int n)
{
    if (data == NULL)
    {
        return;
    }

    for (size_t i = 0; i < n; i++)
    {
        data[i] = rand() % MAX_DATA_VALUE;
    }
}

void printArray(int *const array, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void testAlgorithm(const int *const reference_data, const unsigned int size)
{
    int *test_array = malloc(sizeof(int) * size);
    struct timespec start, end;
    double duration;

    printf("n=%-6d", size);

    memcpy(test_array, reference_data, sizeof(int) * size);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    quickSortNormal(test_array, 0, size - 1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    duration = end.tv_sec + 1e-9 * end.tv_nsec - (start.tv_sec + 1e-9 * start.tv_nsec);
    printf("\tt=%09.6lf", duration);

    for (size_t qs_limit = QS_LIMIT_START; qs_limit < QS_LIMIT_MAX; qs_limit = qs_limit * 2)
    {
        memcpy(test_array, reference_data, sizeof(int) * size);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
        quickSortLimited(test_array, 0, size - 1, qs_limit);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

        duration = end.tv_sec + 1e-9 * end.tv_nsec - (start.tv_sec + 1e-9 * start.tv_nsec);
        printf("\tt=%09.6lf", duration);
    }

    printf("\n");

    free(test_array);
    test_array = NULL;
}

void qsWarmup()
{
    const unsigned int test_size = 1000;
    const unsigned int test_count = 10;

    int *test_data = malloc(sizeof(int) * test_size);

    for (unsigned int i = 0; i < test_count; i++)
    {
        generateData(test_data, test_size);
        quickSortNormal(test_data, 0, test_size - 1);
    }

    for (unsigned int i = 0; i < test_count; i++)
    {
        generateData(test_data, test_size);
        quickSortLimited(test_data, 0, test_size - 1, 8);
    }

    free(test_data);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int compareIntsDesc(const void *a, const void *b)
{
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2)
        return 1;
    if (arg1 > arg2)
        return -1;
    return 0;
}

void quickSortNormal(int *const array, int p, int q)
{
    if (p < q)
    {
        const int pivot = qsPartition(array, p, q);
        quickSortNormal(array, p, pivot);
        quickSortNormal(array, pivot + 1, q);
    }
}

void quickSortLimited(int *const array, int p, int q, const unsigned int limit)
{
    if (p + limit + 1 < q)
    {
        const int pivot = qsPartition(array, p, q);
        quickSortLimited(array, p, pivot, limit);
        quickSortLimited(array, pivot + 1, q, limit);
    }
    else
    {
        bubbleSort(&array[p], q - p + 1);
    }
}

int qsPartition(int *const array, int p, int q)
{
    const int pivot_value = array[q];

    int i = p - 1;

    for (int j = p; j <= q; j++)
    {
        if (array[j] <= pivot_value)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    if (i < q)
    {
        return i;
    }

    return i - 1;
}

void bubbleSort(int *const array, unsigned int n)
{
    bool swapped;
    for (unsigned int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (unsigned int j = 0; j < n - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                swap(&array[j], &array[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
}
