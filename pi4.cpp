#include<iostream>
#include<omp.h>

static long num_steps = 100000000;
double step;

int main()
{
    int i, nthreads;
    double pi,x,sum=0.0;
    double start, stop;
    step = 1.0/(double)num_steps;
    start = omp_get_wtime();

    #pragma omp parallel
    {
        double x;
        #pragma omp for reduction(+:sum)
        for(i=0; i < num_steps; i++)
        {
            x = (i + 0.5)*step;
            sum +=4.0/(1.0 + x*x);
        }
    }
    pi += sum * step;   // we don't consider it because we used "reduction(+:sum)" 
    stop = omp_get_wtime();
    std::cout<< "this is the elapsed time: "<< stop - start << std::endl;
    std::cout<< "the value of Pi is: " << pi << std::endl;
    return 0;
}
