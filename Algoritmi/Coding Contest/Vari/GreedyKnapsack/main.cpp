#include <iostream>
#include <fstream>
using namespace std;

int Knapsack(int W, int *val, int n){
    int **K = new int*[n+1];
    for(int i = 0; i < n+1; i++) K[i] = new int[W + 1];
    for(int i = 0; i < n+1; i++) K[i][0] = 0;
    for(int i = 0; i < W+1; i++) K[0][i] = 0;

    for(int i = 1; i < n+1; i++){
        for(int w = 1; w < W+1; w++){
            K[i][w] = val[i-1] + K[i-1][w-1];
            if(K[i-1][w] > K[i][w]) K[i][w] = K[i-1][w];
        }
    }

    int res = K[n][W];
    for(int i = 0; i < n+1; i++) delete[] K[i];
    delete[] K;
    return res;
}

#define NTASK 3
int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        int n; in >> n;
        int P; in >> P;

        cout << t+1 << ") N = " << n << ", W = " << P << " ---------------\n\n";

        int* val = new int[n];
        for(int i = 0; i < n; i++) in >> val[i];

        out << Knapsack(P, val, n) << endl;
    }
    
}