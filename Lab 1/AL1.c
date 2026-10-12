// kompilować z opcjami -lrt -lm, tj. np. gcc ALL_01.c -lrt -lm
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MLD 1000000000.0

double procedura1(long n);
long procedura2(long n);
long procedura3(long int n);

/////////////////////////////////////////////
//   POMIAR CZASU DLA WIELU PRÓB           //
/////////////////////////////////////////////
int main() {
	struct timespec tp0, tp1;
	double Tn, Fn, x;
	long n; 
	for(n=0; n<=40000; n=n+2500) {
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
// 		obliczenia
		x=procedura1(n);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);

// 		zgadywana funkcja czasu
// 		Fn=log(n);
// 		Fn=sqrt(n);
		Fn=n*n;
		Tn = (tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);

		printf("n: %5ld \tczas: %3.10lf \twspolczynnik: %3.5lf\n", n, Tn, Fn/Tn);
	}
	return 1;
}

/////////////////////////////////////////////
//   PROCEDURA 1                           //
/////////////////////////////////////////////
double procedura1(long n) {
	double x = 0;
	for(long i=n-1; i>=1; i--) {
		if((i % 2) == 1) {
			for(long j=1; j<i+1; j++);
			for(long k=i+1; k<n+1; k++) 
				x = x * 1.1;
		}
	}
	return x;
}

/////////////////////////////////////////////
//   PROCEDURA 2                           //
/////////////////////////////////////////////
long procedura2(long n) {
	long ret = 0;
	long *A = (long*) malloc(n*sizeof(long )); 
	for(long i=0; i<n; i++)
		A[i] = rand() % n;
	for(long d=0; d<n; d++) {
		long k = d;
		while (A[k]!=-1) {
			ret++;
			k = A[k];
			A[k] = -1;
		}
	}
	free(A);           
	return ret; 
}

/////////////////////////////////////////////
//   PROCEDURA 3                           //
/////////////////////////////////////////////
long procedura3(long int n) {
	long j = 0;
	for (long i=1; i<n; i++) {
		long k = 0;
		while (k*k<i) {
			j += 1;
			k += 1;
		}
	}
	return j;
}
