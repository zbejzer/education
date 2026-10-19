#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/time.h>

#define ALG_COUNT 4
#define M_INITIAL_SIZE 2

typedef struct TcType
{
    double (*func)(int n);
    char name[64];
} TcType;

typedef struct AlgType
{
    int (*func)(int n, int **M);
    char name[64];
} AlgType;

typedef struct GenType
{
    void (*func)(int n, int ***M);
    char name[64];
} GenType;

double measureAlgorithm(int n, void(* gen)(int n, int ***M), int (*alg)(int n, int **M));
void testAlgorithm(const GenType *gen, const TcType *tc, const AlgType *alg);

// PROCEDURY POMOCNICZE
void utworz_MACIERZ(int n, int ***M);
void utworz_MACIERZ_ZERO(int n, int ***M);
void utworz_MACIERZ_JEDEN(int n, int ***M);
void utworz_MACIERZ_x(int n, int ***M, int x);
void wypisz_MACIERZ(int n, int **M);
void zwolnij_MACIERZ(int n, int **M);

// ALGORYTM PIERWSZY
int ALGO_NAIWNY(int n, int **M);
// ALGORYTM DRUGI
int REKURENCJA(int **M, int x1, int y1, int x2, int y2);
int ALGO_REKURENCYJNY(int n, int **M);
// ALGORYTM TRZECI
int ALGO_DYNAMICZNY(int n, int **M);
// ALGORYTM CZWARTY
int ALGO_CZULY(int n, int **M);

double tcFact(int n);
double tcExp(int n);
double tcQuad(int n);
double tcCubic(int n);
double tcQuart(int n);
double tcPowFive(int n);
double tcPowSix(int n);
double tcNLog(int n);

int main()
{
    const TcType tc_fact = {tcFact, "n!"};
    const TcType tc_exp = {tcExp, "2^n"};
    const TcType tc_quad = {tcQuad, "n^2"};
    const TcType tc_cubic = {tcCubic, "n^3"};
    const TcType tc_quart = {tcQuart, "n^4"};
    const TcType tc_pow_five = {tcPowFive, "n^5"};
    const TcType tc_pow_six = {tcPowSix, "n^6"};
    const TcType tc_n_log = {tcNLog, "n * log(n)"};

    const AlgType algo_naiwny = {ALGO_NAIWNY, "Naiwny"};
    const AlgType algo_rekurencyjny = {ALGO_REKURENCYJNY, "Rekurencyjny"};
    const AlgType algo_dynamiczny = {ALGO_DYNAMICZNY, "Dynamiczny"};
    const AlgType algo_czuly = {ALGO_CZULY, "Czuly"};

    const GenType gen_macierz_rand = {utworz_MACIERZ, "Losowo"};
    const GenType gen_macierz_zero = {utworz_MACIERZ_ZERO, "Zero"};
    const GenType gen_macierz_jeden = {utworz_MACIERZ_JEDEN, "Jeden"};


    srand(time(NULL));

    testAlgorithm(&gen_macierz_rand, &tc_pow_six, &algo_naiwny);
    testAlgorithm(&gen_macierz_rand, &tc_pow_six, &algo_rekurencyjny);
    testAlgorithm(&gen_macierz_rand, &tc_cubic, &algo_dynamiczny);
    testAlgorithm(&gen_macierz_rand, &tc_quad, &algo_czuly);
    testAlgorithm(&gen_macierz_zero, &tc_quad, &algo_czuly);
    testAlgorithm(&gen_macierz_jeden, &tc_quart, &algo_czuly);

    return 0;
}

/////////////////////////////////////////////
//   PROCEDURY POMOCNICZE                  //
/////////////////////////////////////////////

double measureAlgorithm(int n, void(* gen)(int n, int ***M), int (*alg)(int n, int **M))
{
    int **Macierz;
    gen(n, &Macierz);

    struct timespec start, end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    alg(n, Macierz);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    double posix_dur = end.tv_sec + 1e-9 * end.tv_nsec - (start.tv_sec + 1e-9 * start.tv_nsec);

    zwolnij_MACIERZ(n, Macierz);

    return posix_dur;
}

void testAlgorithm(const GenType *gen, const TcType  *tc, const AlgType  *alg)
{
    int is_progress_exp = 1;
    double time_measured = 1;
    double last_time = time_measured;
    double time_limit = 15.0;
    double cumulative_time_limit = 40.0;
    double cumulative_time = 0;
    double time_complexity = 1.0;
    int m_size = M_INITIAL_SIZE;
    int m_size_step = m_size;

    double ref_tc_ratio = 0;
    for (size_t k = 0; k < 3; k++)
    {
        ref_tc_ratio += tc->func(16) / measureAlgorithm(16, gen->func, alg->func);
    }
    ref_tc_ratio /= 3;

    printf("Typ algorytmu: %s\n", alg->name);
    printf("Generowanie macierzy: %s\n", gen->name);
    printf("Oszacowana zlozonosc czasowa: %s\n", tc->name);
    printf("Wspolczynnik dla n=16: %lf\n", ref_tc_ratio);

    while (time_measured < time_limit && cumulative_time < cumulative_time_limit)
    {
        last_time = time_measured;
        time_measured = measureAlgorithm(m_size, gen->func, alg->func);
        time_complexity = tc->func(m_size);
        cumulative_time += time_measured;
        printf("n=%-6d", m_size);
        printf("\tt=%09.6lf", time_measured);
        printf("\tf=%-16.0lf", time_complexity);
        printf("\tf/t_ratio=%-20.3lf", time_complexity / time_measured);
        printf("\tnorm_ratio=%-10.6lf", time_complexity / (ref_tc_ratio * time_measured));
        printf("\n");

        if ((time_measured / last_time < 2.0 || time_measured - last_time < 0.01) && is_progress_exp)
        {
            m_size_step = m_size / 2;
            m_size = m_size * 2;
        }
        else
        {
            is_progress_exp = 0;
            m_size = m_size + m_size_step;
        }
    }
}


// alokuje pamięć na tablicę rozmiaru nxn i wpisuje losowe wartości 0/1
void utworz_MACIERZ(int n, int ***M)
{
    (*M) = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        (*M)[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            (*M)[i][j] = rand() % 2;
}

void utworz_MACIERZ_ZERO(int n, int ***M)
{
    (*M) = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        (*M)[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            (*M)[i][j] = 0;
}

void utworz_MACIERZ_JEDEN(int n, int ***M)
{
    (*M) = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        (*M)[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            (*M)[i][j] = 1;
}

// alokuje pamięć na tablicę rozmiaru nxn i wpisuje wszędzie wartość x
void utworz_MACIERZ_x(int n, int ***M, int x)
{
    (*M) = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        (*M)[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            (*M)[i][j] = x;
}

// wypisuje wartości tablicy
void wypisz_MACIERZ(int n, int **M)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d", M[i][j]);
        printf("\n");
    }
    printf("\n");
}

// zwalania pamięć zarezerwowaną dla macierzy
void zwolnij_MACIERZ(int n, int **M)
{
    for (int i = 0; i < n; i++)
        free(M[i]);
    free(M);
}

/////////////////////////////////////////////
//   ALGORYTM PIERWSZY                     //
/////////////////////////////////////////////
int ALGO_NAIWNY(int n, int **M)
{
    int max = 0;
    for (int x1 = 0; x1 < n; x1++)
        for (int y1 = 0; y1 < n; y1++)
            for (int x2 = n - 1; x2 > x1 - 1; x2--)
                for (int y2 = n - 1; y2 > y1 - 1; y2--)
                {
                    int local_max = 0;
                    for (int x = x1; x < x2 + 1; x++)
                        for (int y = y1; y < y2 + 1; y++)
                            local_max += M[x][y];
                    if ((local_max == (x2 - x1 + 1) * (y2 - y1 + 1)) && (local_max > max))
                        max = local_max;
                }
    return max;
}

/////////////////////////////////////////////
//   ALGORYTM DRUGI                        //
/////////////////////////////////////////////
int REKURENCJA(int **M, int x1, int y1, int x2, int y2)
{
    if (x2 == x1 && y2 == y1)
        return M[x1][y1];
    else if (x2 - x1 > y2 - y1)
        return REKURENCJA(M, x1, y1, (int)(x1 + x2) / 2, y2) * REKURENCJA(M, (int)(x1 + x2 + 1) / 2, y1, x2, y2);
    else
        return REKURENCJA(M, x1, y1, x2, (int)(y1 + y2) / 2) * REKURENCJA(M, x1, (int)(y1 + y2 + 1) / 2, x2, y2);
}

int ALGO_REKURENCYJNY(int n, int **M)
{
    int max = 0;
    for (int x1 = 0; x1 < n; x1++)
        for (int y1 = 0; y1 < n; y1++)
            for (int x2 = x1; x2 < n; x2++)
                for (int y2 = y1; y2 < n; y2++)
                {
                    int local_max = REKURENCJA(M, x1, y1, x2, y2) * (x2 - x1 + 1) * (y2 - y1 + 1);
                    if (local_max > max)
                        max = local_max;
                }
    return max;
}

/////////////////////////////////////////////
//   ALGORYTM TRZECI                       //
/////////////////////////////////////////////
int ALGO_DYNAMICZNY(int n, int **M)
{
    int **MM;
    utworz_MACIERZ_x(n, &MM, 0);

    int max = 0;
    for (int y = 0; y < n; y++)
        for (int x1 = 0; x1 < n; x1++)
        {
            int iloczyn = 1;
            for (int x2 = x1; x2 < n; x2++)
            {
                iloczyn *= M[x2][y];
                MM[x1][x2] = iloczyn * (x2 - x1 + 1 + MM[x1][x2]);
                if (MM[x1][x2] > max)
                    max = MM[x1][x2];
            }
        }
    return max;
}

/////////////////////////////////////////////
//   ALGORYTM CZWARTY                      //
/////////////////////////////////////////////
int ALGO_CZULY(int n, int **M)
{
    int max = 0;
    for (int x1 = 0; x1 < n; x1++)
        for (int y1 = 0; y1 < n; y1++)
        {
            int local_max = 0;
            int x2 = x1;
            int ymax = n - 1;
            while (x2 < n && M[x2][y1] == 1)
            {
                int y2 = y1;
                while (y2 < ymax + 1 && M[x2][y2] == 1)
                {
                    y2++;
                }
                ymax = y2 - 1;
                local_max = (x2 - x1 + 1) * (ymax - y1 + 1);
                if (local_max > max)
                    max = local_max;
                x2++;
            }
        }
    return max;
}

double tcFact(int n)
{
    long long int f = 1;
    for (size_t i = 1; i <= n; ++i)
        f *= i;
    return (double)f;
}

double tcExp(int n)
{
    return exp2((double)n);
}

double tcQuad(int n)
{
    return pow((double)n, 2.0);
}

double tcCubic(int n)
{
    return pow((double)n, 3.0);
}

double tcQuart(int n)
{
    return pow((double)n, 4.0);
}

double tcPowFive(int n)
{
    return pow((double)n, 5.0);
}

double tcPowSix(int n)
{
    return pow((double)n, 6.0);
}

double tcNLog(int n)
{
    return (double)n * log2((double)n);
}
