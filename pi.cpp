#include<iostream>
#include<omp.h>

static long num_steps = 100000000;
double step;
#define PAD 32
#define NUM_THREADS 8


int main()
{
    int i, nthreads;
    double pi, sum[NUM_THREADS][PAD];
    double start, stop;
    step = 1.0/(double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    start = omp_get_wtime();
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if(id == 0) nthreads = nthrds;
        for(i=id, sum[id][0]=0.0 ; i < num_steps; i=i+nthrds)
        {
            x = (i + 0.5)*step;
            sum[id][0]+=4.0/(1.0 + x*x);
        }
    }
    for(i=0, pi=0.0; i <nthreads ;i++)
        pi +=sum[i][0]*step;
    stop = omp_get_wtime();
    std::cout<< "this is the elapsed time: "<< stop - start << std::endl;
    std::cout<< "the value of Pi is: " << pi << std::endl;
    return 0;
}
