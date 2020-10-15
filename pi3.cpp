#include<iostream>
#include<omp.h>

static long num_steps = 100000000;
double step;
#define NUM_THREADS 8


int main()
{
    int i, nthreads;
    double pi=0.0;
    double start, stop;
    step = 1.0/(double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    start = omp_get_wtime();
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        double sum; // sum is inside of the parallel section
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if(id == 0) nthreads = nthrds;
        for(i=id, sum=0.0 ; i < num_steps; i=i+nthrds)
        {
            x = (i + 0.5)*step;
            sum +=4.0/(1.0 + x*x);
        }
        #pragma omp atomic          // this almost the same as with critical section
            pi +=sum*step;
        //#pragma omp critical        // the sum that each thread gets is stored in the variable "pi"
        //    pi +=sum*step;
    }
    stop = omp_get_wtime();
    std::cout<< "this is the elapsed time: "<< stop - start << std::endl;
    std::cout<< "the value of Pi is: " << pi << std::endl;
    return 0;
}



