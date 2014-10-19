// foo.cpp : Defines the entry point for the console application.
#include <malloc.h>
#include <omp.h>
//Why not #define true false
//#define TWO 2

#define INREAL(i)	field[i]
#define INCMPL(i)	field[i+1]
#define OUTREAL(i)	field[i]
#define OUTCMPL(i)	field[i+1]
#define A		8
#define B		13


long worker(int* field, long flength)
{
	for (int evolution = 0; evolution < 1000; evolution++) {
//I think about 32 cores.
#pragma omp parallel for //num_threads(ths) 
//real part must be separated from imaginary one
			for (long i = 0; i < flength; i+=2) {
				OUTREAL(i) = (INREAL(i) + INCMPL(i))*(INREAL(i) - INCMPL(i)) + A;
				OUTCMPL(i) = 2*INREAL(i)*INCMPL(i) + B;
			}
		printf("evolution %d\n", evolution);
	}
//count is very good, but perfomance cup...
	return 1000*flength;
}
void init(int* field, long length)
{
	for (long i = 0; i < length * 2; i += 2) {
		field[i] = 1;
		field[i + 1] = 0;
	}
}

int main()
{
	int* field;
	const int width = 200;
	const int height = 200;

	field = (int*) malloc(width * height * sizeof(int) * 2);

	init(field, 40000);
	long res = worker(field, 40000);

	printf("Woohoo!11\n");
	printf("Count %li \n", res);
//Nash programist opyat' nakodil v kuchu))
	free(field);
	return 0;
}
