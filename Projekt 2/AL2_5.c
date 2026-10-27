#include <stdio.h>
#include <stdlib.h>

#define INITIAL_DATA_SIZE 1

typedef struct HeapSortData
{
    unsigned int size;
    unsigned int *data;
    unsigned int x, y;
} HeapSortData;

void InitHSD(HeapSortData *obj);
void FreeHSD(HeapSortData *obj);
void LoadInput(HeapSortData *obj);
void PrintHSD(HeapSortData *obj);
void PrintRangeHSD(HeapSortData *obj, const unsigned int start, const unsigned int end);

int main(int argc, char *argv[])
{
    HeapSortData m_data;
    InitHSD(&m_data);
    LoadInput(&m_data);

    printf("x = %u\n", m_data.x);
    printf("y = %u\n", m_data.y);
    printf("Stan przed sortowaniem:\n");
    PrintHSD(&m_data);

    printf("Zakres do posortowania:\n");
    PrintRangeHSD(&m_data, m_data.x, m_data.y);

    printf("Stan po sortowaniu:\n");
    PrintHSD(&m_data);

    FreeHSD(&m_data);
    return EXIT_SUCCESS;
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

void LoadInput(HeapSortData *obj)
{
    unsigned int num;
    unsigned int loaded = 0;

    scanf("%u", &(obj->x));
    scanf("%u", &(obj->y));

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

    // Correct for indexes
    obj->x--;
    obj->y--;
}

void PrintHSD(HeapSortData *obj)
{
    for (unsigned int i = 1; i < obj->size + 1; i++)
    {
        printf("%3u ", i);
    }
    printf("\n");
    for (size_t i = 0; i < obj->size; i++)
    {
        printf("%3u ", obj->data[i]);
    }
    printf("\n");
}

void PrintRangeHSD(HeapSortData *obj, const unsigned int start, const unsigned int end)
{
    for (unsigned int i = start; i < end + 1; i++)
    {
        printf("%3u ", i);
    }
    printf("\n");
    for (unsigned int i = start; i < end + 1; i++)
    {
        printf("%3u ", obj->data[i]);
    }
    printf("\n");
}