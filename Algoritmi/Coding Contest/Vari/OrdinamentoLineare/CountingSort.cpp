#include <iostream>
#include <fstream>
using namespace std;

template <class T> T findMin(T* A, int n){
    T min = A[0];
    for(int i = 1; i < n; i++)
        if(A[i] < min) min = A[i];
    return min;
}

template <class T> T findMax(T* A, int n){
    T max = A[0];
    for(int i = 1; i < n; i++)
        if(A[i] > max) max = A[i];
    return max;
}

template <class T> void CountingSort(T* &A, int n, int* &C, int &m){

    T min = findMin(A, n);
    T max = findMax(A, n);

    C = new int[(int)max - (int)min + 1];
    for(int i = 0; i <= max - min; i++) C[i] = 0;
    for(int i = 0; i < n; i++) C[(int)A[i] - (int)min]++;
    for(int i = 1; i <= max - min; i++) C[i] += C[i - 1];

    T* B = new T[n + 1];
    for (int i = n-1; i >= 0; i--)
    {
        B[C[(int)A[i] - (int)min]] = A[i];
        C[(int)A[i] - (int)min]--;
    }
    
    for(int i = 0; i < n; i++) A[i] = B[i+1];
    m = max - min + 1;
}