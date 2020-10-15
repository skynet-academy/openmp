#include<iostream>
#include<omp.h>
#include<vector>
#include<stdlib.h>
#include<random>
using namespace std;

static long NUM_ELEMTS = 1000000;


void initializeVector(vector<int>& my_vec)
{
    for(int i{0}; i < my_vec.size(); i++)
        my_vec[i] = rand()% NUM_ELEMTS + 1;
}

int main()
{

    vector<int> my_vec(NUM_ELEMTS);
    initializeVector(my_vec);

    // without openmp
    double start, end;
    start = omp_get_wtime();
    int min = my_vec[0];
    int index = 0;
    for(int i = 1; i < my_vec.size(); i++)
    {
        if(my_vec[i] < min)
        {
            min = my_vec[i];
            index = i;
        }
    }
    end = omp_get_wtime();
    cout<< "The minimum value is: "<< min << " at: "<< index<< endl;
    cout<< "The elapsed time without openmp is: "<< (end - start)*1000 << " seconds\n" << endl;

    // parallel section
    double start_parallel, end_parallel;
    int index_p = 0;
    int min_p = my_vec[0];
    start_parallel = omp_get_wtime();
    #pragma omp parallel 
    {
        int index_local = index_p;
        int min_local = min_p;
        //#pragma omp for nowait
        #pragma omp for
        for(int i = 1; i < my_vec.size(); i++)
        {
            if(my_vec[i] < min_local)
            {
                min_local = my_vec[i];
                index_local = i;
            }
        }
        #pragma omp critical
        {
            if(min_local < min_p)
            {
                min_p = min_local;
                index_p = index_local;
            }
        }
    }
    end_parallel = omp_get_wtime();
    cout<<"This is the minimum: "<< min << " at index: "<< index_p <<endl;
    cout<<"The time elapsed using openmp is: "<< (end_parallel - start_parallel)*1000 << " seconds\n" << endl;
    return 0;
}



