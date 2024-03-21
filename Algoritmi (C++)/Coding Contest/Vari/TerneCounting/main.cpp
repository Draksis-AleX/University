#include <iostream>
#include <fstream>
using namespace std;

typedef struct{
    double x, y, z;
} Terna;

Terna findMin(Terna* A, int n){
    Terna min = A[0];
    for(int i = 1; i < n; i++){
        if(A[i].x < min.x) min = A[i];
    }
    return min;
}

Terna findMax(Terna* A, int n){
    Terna max = A[0];
    for(int i = 1; i < n; i++){
        if(A[i].x > max.x) max = A[i];
    }
    return max;
}

int CountingSort(Terna* &A, int n, int* &C, int &m){
    int min = findMin(A, n).x;
    int max = findMax(A, n).x;

    m = max - min + 1;
    C = new int[m];
    for(int i = 0; i < m; i++) C[i] = 0;
    for(int i = 0; i < n; i++) C[(int)A[i].x - min]++;
    for(int i = 1; i < m; i++) C[i] += C[i-1];

    Terna* B = new Terna[n];
    for(int i = n-1; i >= 0; i--){
        B[C[(int) A[i].x - min] - 1] = A[i];
        C[(int) A[i].x - min]--;
    }

    for(int i = 0; i < n; i++) A[i] = B[i];

    delete[] B;
}

#define NTASK 100

int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        int n; in >> n;
        Terna* A = new Terna[n];
        for(int i = 0; i < n; i++){
            char tmp; in >> tmp;
            in >> A[i].x; //in >> tmp;
            A[i].x *= 10;
            in >> A[i].y; //in >> tmp;
            A[i].y *= 10;
            in >> A[i].z; in >> tmp;
            A[i].z *= 10;
        }

        cout << t+1 << ") N = " << n << " -------------\n\n";

        int* C;
        int m;
        CountingSort(A, n, C, m);

        for(int i = 0; i < m; i++) out << C[i] << " ";
        for(int i = 0; i < n; i++) out << "(" << A[i].x/10 << " " << A[i].y/10 << " " << A[i].z/10 << ") ";
        out << endl;

        delete[] C;
        delete[] A;
    }
    
    return 0;
}
