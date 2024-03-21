#include "CountingSort.cpp"
#include <iostream>
#include <fstream>
using namespace std;

#define N_TASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < N_TASK; t++)
    {
        string type; in >> type;
        int n; in >> n;
        int* C;
        int m;
        if(type == "int"){
            int* A = new int[n];
            for(int i = 0; i < n; i++)
                in >> A[i];
            CountingSort(A, n, C, m);
            for(int i = 0; i < m; i++) out << C[i] << " ";
            //out << endl;
            for(int i = 0; i < n; i++) out << A[i] << " ";
            out << endl;
        }
        else if(type == "double"){
            double* A = new double[n];
            for(int i = 0; i < n; i++){
                 in >> A[i];
                 A[i] *= 10;
            }
            CountingSort(A, n, C, m);
            for(int i = 0; i < m; i++) out << C[i] << " ";
            //out << endl;
            for(int i = 0; i < n; i++) out << A[i]/10 << " ";
            out << endl;
        }
        else if(type == "bool"){
            bool* A = new bool[n];
            for(int i = 0; i < n; i++) in >> A[i];
            CountingSort(A, n, C, m);
            for(int i = 0; i < m; i++) out << C[i] << " ";
            //out << endl;
            for(int i = 0; i < n; i++) out << A[i] << " ";
            out << endl;
        }
        else if(type == "char"){
            char* A = new char[n];
            for(int i = 0; i < n; i++) in >> A[i];
            CountingSort(A, n, C, m);
            for(int i = 0; i < m; i++) out << C[i] << " ";
            //out << endl;
            for(int i = 0; i < n; i++) out << A[i] << " ";
            out << endl;
        }
    }
    
    return 0;
}
