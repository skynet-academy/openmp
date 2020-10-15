#include<iostream>
#include<omp.h>


int main(int argc, char *argv[])
{
    #pragma omp parallel
    {
        std::cout
            << "Thread id: "<< omp_get_thread_num()<< " of "
            << omp_get_num_threads()<< std::endl;
    }
    return 0;
}
