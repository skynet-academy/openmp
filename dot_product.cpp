#include<iostream>
#include<omp.h>
#include<vector>
#include<stdlib.h>
#include<random>

using namespace std;

static long NUM_ELEMTS = 100000000;

void initializeVector(vector<int>& my_vec)
{
    for(int i{0}; i < my_vec.size(); i++)
        my_vec[i] = rand()% NUM_ELEMTS + 1;
}

int main()
{

    vector<int> A(NUM_ELEMTS), B(NUM_ELEMTS);
    initializeVector(A);
    initializeVector(B);
    // without openmp
    double start, end;
    long int dot_product = 0;
    start = omp_get_wtime();
    for(int i=0; i<NUM_ELEMTS; i++)
        dot_product += A[i] * B[i];

    end = omp_get_wtime();
    cout<< dot_product << " dot product "<< endl;
    cout<< "The elapsed time is: "<< (end - start)*1000000 << endl;

    // parallel section with openmp
    double start_p, end_p;
    start = omp_get_wtime();
    long int dot = 0,sum=0;
    #pragma omp parallel for reduction(+:sum) 
        for(int i = 0; i < NUM_ELEMTS; i++)
            sum += A[i] * B[i];
        //dot +=sum;

    dot+=sum;
    end = omp_get_wtime();
    cout<< dot << " dot product "<<endl;
    cout<< "The elapsed time is: "<< (end_p - start_p)*1000000 << endl;

    return 0;
}


