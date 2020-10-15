#include<iostream>
#include<omp.h>

static long num_steps = 100000000;
double step;

int main()
{
    //int i;
    double result=0.0 ,result_p=0.0 ,x ,sum=0.0 ,h;
    double start_p, stop_p, start, stop;
    int a,b;
    std::cout<<"a: "<< std::endl;
    std::cin>>a;
    std::cout<<"b: "<<std::endl;
    std::cin>>b;
    //step = 1.0/(double)num_steps;
    h = (b-a)/(double)num_steps;
    start = omp_get_wtime();
    for(int i =0; i< num_steps; i++)
    {
        x += i * h;
    }
    result = h*x;
    stop = omp_get_wtime();
    std::cout<< "time elapsed is: "<< stop - start<< std::endl;
    std::cout<< "The result is : "<< result << std::endl;

    start_p = omp_get_wtime();
    #pragma omp parallel
    {
        int i;
        double x;
        #pragma omp for reduction(+:sum)
        for(i=0; i < num_steps ; i++)
        {
            x = i * h;
            //x = i * step;
            sum +=x;
        }
    }
    result_p += h*sum ;   // we don't consider it because we used "reduction(+:sum)" 
    stop_p = omp_get_wtime();
    std::cout<< "this is the elapsed time: "<< stop_p - start_p << std::endl;
    std::cout<< "the result is: " << result_p << std::endl;
    return 0;
}

