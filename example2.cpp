#include<iostream>
#include<omp.h>



void pooh(int ID, double* A)
{
    for(int i{ID}; i < chunk*ID; i++)
    {
    
    }

}


int main()
{
    double A[10000];
    omp_set_num_threads(6);
    #pragma omp parallel
    {
        int ID{omp_get_threads_num()};
        pooh(ID,A);
    }
    std::cout<<" all done\n";
    return 0;

}
