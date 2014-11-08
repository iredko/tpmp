/* 
 * File:   main.cpp
 * Author: iredko
 *
 * Created on October 27, 2014, 12:11 PM
 */

#include <cstdlib>
#include "thread_pool.h"
#include <cstdio>
#include <cmath>

class Job{
    long number;
public:
    Job(long n){
        number = n;
    }
    void operator() (){
	long threshold = (long)sqrt(number);
	long runner = 2;
	char *result = (char*)malloc(100), *copy;
	copy = result;
	result += sprintf(result, "%ld = ", number);
	printf("factorizing %ld\r\n", number);
	while (runner < threshold) {
		if (number % runner == 0) {
			result += sprintf(result, "%ld ", runner);
			number /= runner;
			threshold = (int)sqrt(number);
		} else {
			if (runner > 2)	runner += 2;
			else runner++;
		}
	}
	if (number > 1)
		sprintf(result, "%ld\0", number);
	else
		sprintf(result, "\0");
	printf("%s\r\n", copy);
	free(copy);
}
};
int main() {
    unsigned int thr = 8;
    thread_pool *pool =new thread_pool(thr);
    long i;
    std::vector<Job> jobs;
    jobs.reserve(10000);
    for (i = 0; i < 10000; i++) 
            jobs.push_back(Job(92346745625325325 + i * 137));

    for (i = 0; i < 10000; i++){
            *pool,jobs.back();	
            jobs.pop_back();
    }
    delete pool;        
}