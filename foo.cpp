// foo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>
#include <omp.h>
#define TWO 1

void hard_code_evolution(int* real, int* complex, int a, int b) {
	float x2 = *real * *real;
	float y2 = *complex * *complex;
	double xy = *real * *complex;
	double newreal = x2 - y2 + a;
	double newcomplex = 2 * xy + b;
	*real = (int)newreal;
	*complex = (int)newcomplex;
}

double count2 = 0;

double worker(int ths, int* field, long flength) {
	double count1 = 0;
	int evolution = 0;
	for (; evolution < 1000; evolution++) {

#pragma omp parallel num_threads(ths)
		{
			long i = omp_get_thread_num() * flength / ths;
			long finish = (omp_get_thread_num() + 1) * flength / ths;
			for (; i < finish; i++) {
				hard_code_evolution(field + i, field + i + 1, 8, 13);
																										#pragma omp critical (cri)
				count1 += 1.0;	
				count2 += 1.0;
			}
		}

		printf("evolution %d\n", evolution);
	}
	
	return count1;
}

int * myAlloc(int width, int height) {
	int* arr = (int*)malloc(width * height * sizeof(int) * 2);	
	return arr;
}

void init(int* field, long length) {
	long i = 0;
	for (; i < length * 2; i++) {
		field[i] = i % 2 ? 0 : 1;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int* field = myAlloc(200, 200);
	init(field, 40000);
	double res = worker(TWO, field, 40000);

	printf("Woohoo!\n");
	printf("Count1 %lf Count2 %lf\n",res, count2);
	//have i forgot anything?
	return 0;
}

