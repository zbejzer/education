#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// PROCEDURY POMOCNICZE
void utworz_MACIERZ(int n, int ***M);
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

int main() {
	int n=20; //wymiar macierzy/
	int **Macierz;
	srand(time(NULL));
	
	utworz_MACIERZ(n, &Macierz);
	wypisz_MACIERZ(n, Macierz);
	printf("Wynik 1=%d \n", ALGO_NAIWNY(n, Macierz));
	printf("Wynik 2=%d \n", ALGO_REKURENCYJNY(n, Macierz));
	printf("Wynik 3=%d \n", ALGO_DYNAMICZNY(n, Macierz));
	printf("Wynik 4=%d \n", ALGO_CZULY(n, Macierz));
	zwolnij_MACIERZ(n, Macierz);
	return 0;
}

/////////////////////////////////////////////
//   PROCEDURY POMOCNICZE                  //
/////////////////////////////////////////////

// alokuje pamięć na tablicę rozmiaru nxn i wpisuje losowe wartości 0/1 
void utworz_MACIERZ(int n, int ***M) {
	(*M) = (int **)malloc(n*sizeof(int *));
	for (int i=0; i<n; i++)
		(*M)[i]=(int *)malloc(n*sizeof(int));
	
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			(*M)[i][j]=rand()% 2;
}

// alokuje pamięć na tablicę rozmiaru nxn i wpisuje wszędzie wartość x
void utworz_MACIERZ_x(int n, int ***M, int x) {
	(*M) = (int **)malloc(n*sizeof(int *));
	for (int i=0; i<n; i++)
		(*M)[i]=(int *)malloc(n*sizeof(int));
	
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			(*M)[i][j]=x;
}

// wypisuje wartości tablicy
void wypisz_MACIERZ(int n, int **M) {
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++)
			printf("%d",M[i][j]);
		printf("\n");
	}
	printf("\n");
}

// zwalania pamięć zarezerwowaną dla macierzy
void zwolnij_MACIERZ(int n, int **M) {
	for (int i=0; i<n; i++)
		free(M[i]);
	free(M);
}

/////////////////////////////////////////////
//   ALGORYTM PIERWSZY                     //
/////////////////////////////////////////////
int ALGO_NAIWNY(int n, int **M) {
	int max=0;	
	for (int x1=0; x1<n; x1++)
		for (int y1=0; y1<n; y1++)
			for (int x2=n-1; x2>x1-1; x2--)
				for (int y2=n-1; y2>y1-1; y2--) {
					int local_max=0;
					for (int x=x1; x<x2+1; x++)
						for (int y=y1; y<y2+1; y++)
							local_max+=M[x][y];
					if ((local_max==(x2-x1+1)*(y2-y1+1)) && (local_max > max))
						max=local_max;
				}
	return max;
}

/////////////////////////////////////////////
//   ALGORYTM DRUGI                        //
/////////////////////////////////////////////
int REKURENCJA(int **M,int x1, int y1, int x2, int y2) {
	if (x2==x1 && y2==y1) 
		return M[x1][y1];
	else if (x2-x1 > y2-y1)
		return REKURENCJA(M, x1, y1, (int)(x1+x2)/2, y2) * REKURENCJA(M, (int)(x1+x2+1)/2, y1, x2, y2);
	else 
		return REKURENCJA(M, x1, y1, x2, (int)(y1+y2)/2) * REKURENCJA(M, x1, (int)(y1+y2+1)/2, x2, y2);
}

int ALGO_REKURENCYJNY(int n, int **M) {
	int max=0;
	for (int x1=0; x1<n; x1++)
		for (int y1=0; y1<n; y1++)
			for (int x2=x1; x2<n; x2++)
				for (int y2=y1; y2<n; y2++) {
					int local_max = REKURENCJA(M, x1, y1, x2, y2)*(x2-x1+1)*(y2-y1+1);
					if (local_max > max) 
						max=local_max;
				}
	return max;
}

/////////////////////////////////////////////
//   ALGORYTM TRZECI                       //
/////////////////////////////////////////////
int ALGO_DYNAMICZNY(int n, int **M) {
	int **MM;
	utworz_MACIERZ_x(n, &MM, 0);

	int max = 0;
	for (int y=0; y<n; y++)
		for (int x1=0; x1<n; x1++) {
			int iloczyn=1;
			for (int x2=x1; x2<n; x2++) {
				iloczyn *= M[x2][y];
				MM[x1][x2] = iloczyn*(x2-x1+1+MM[x1][x2]);
				if (MM[x1][x2] > max) 
					max=MM[x1][x2];
			}
		}
	return max;
}

/////////////////////////////////////////////
//   ALGORYTM CZWARTY                      //
/////////////////////////////////////////////
int ALGO_CZULY(int n, int **M) {
	int max=0;
	for (int x1=0; x1<n; x1++)
		for (int y1=0; y1<n; y1++) {
			int local_max=0;
			int x2 = x1;
			int ymax = n-1;
			while (x2<n && M[x2][y1]==1) {
				int y2=y1;
				while (y2<ymax+1 && M[x2][y2]==1) {
					y2++;
				}
				ymax=y2-1;
				local_max=(x2-x1+1)*(ymax-y1+1);
				if (local_max > max) 
					max=local_max;
				x2++;
			}
		}
	return max;
}
