#include <stdio.h>
#include <stdlib.h>

#define INITIAL_DATA_SIZE 1

typedef struct HeapSortData
{
    unsigned int size;
    unsigned int *data;
} HeapSortData;

void Swap(unsigned int *a, unsigned int *b);

void InitHSD(HeapSortData *obj);
void FreeHSD(HeapSortData *obj);
void LoadInput(HeapSortData *obj, unsigned int *x, unsigned int *y);
void PrintHSD(HeapSortData *obj);
void PrintRangeHSD(HeapSortData *obj, const unsigned int start, const unsigned int end);
void HeapSortRange(HeapSortData *obj, const size_t start, const size_t end);
void Heapify(HeapSortData *obj, size_t i);

int main(int argc, char *argv[])
{
    HeapSortData heap_data;
    unsigned int x, y;

    InitHSD(&heap_data);
    LoadInput(&heap_data, &x, &y);

    printf("x = %u\n", x);
    printf("y = %u\n", y);
    printf("Stan przed sortowaniem:\n");
    PrintHSD(&heap_data);

    printf("Zakres do posortowania:\n");
    PrintRangeHSD(&heap_data, x - 1, y - 1);

    HeapSortRange(&heap_data, x - 1, y - 1);

    printf("Stan po sortowaniu:\n");
    PrintHSD(&heap_data);

    FreeHSD(&heap_data);
    return EXIT_SUCCESS;
}

void Swap(unsigned int *a, unsigned int *b)
{
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}

void InitHSD(HeapSortData *obj)
{
    obj->size = INITIAL_DATA_SIZE;
    obj->data = malloc(obj->size * sizeof(unsigned int));
}

void FreeHSD(HeapSortData *obj)
{
    free(obj->data);
}

void LoadInput(HeapSortData *obj, unsigned int *x, unsigned int *y)
{
    unsigned int num;
    unsigned int loaded = 0;

    scanf("%u", x);
    scanf("%u", y);

    while (scanf("%u", &num) != EOF)
    {
        loaded++;
        if (loaded > obj->size)
        {
            obj->size = obj->size * 2;
            obj->data = realloc(obj->data, obj->size * sizeof(unsigned int));
        }
        obj->data[loaded - 1] = num;
    }
    obj->data = realloc(obj->data, loaded * sizeof(unsigned int));
    obj->size = loaded;

    if (*x > loaded || *y > loaded)
    {
        printf("Invalid x or y value!\n");
        exit(EXIT_FAILURE);
    }
}

void PrintHSD(HeapSortData *obj)
{
    PrintRangeHSD(obj, 0, obj->size - 1);
}

void PrintRangeHSD(HeapSortData *obj, const unsigned int start, const unsigned int end)
{
    for (unsigned int i = start; i < end + 1; i++)
    {
        printf("%3u ", i + 1);
    }
    printf("\n");
    for (unsigned int i = start; i < end + 1; i++)
    {
        printf("%3u ", obj->data[i]);
    }
    printf("\n");
}

void HeapSortRange(HeapSortData *heap_data, const size_t start, const size_t end)
{
    HeapSortData to_sort;
    to_sort.data = &(heap_data->data[start]);
    to_sort.size = end - start + 1;

    for (int i = to_sort.size / 2 - 1; i >= 0; i--)
    {
        Heapify(&to_sort, i);
    }

    while (to_sort.size > 1)
    {
        Swap(&to_sort.data[0], &to_sort.data[to_sort.size - 1]);
        to_sort.size--;

        Heapify(&to_sort, 0);
    }
}

void Heapify(HeapSortData *obj, size_t i)
{
    size_t largest, left, right;

    while (i < obj->size / 2)
    {
        largest = i;
        left = 2 * i + 1;
        right = 2 * i + 2;

        if (left < obj->size && obj->data[left] > obj->data[largest])
            largest = left;

        if (right < obj->size && obj->data[right] > obj->data[largest])
            largest = right;

        if (largest != i)
        {
            Swap(&(obj->data[i]), &(obj->data[largest]));
            i = largest;
        }
        else
        {
            break;
        }
    }
}
