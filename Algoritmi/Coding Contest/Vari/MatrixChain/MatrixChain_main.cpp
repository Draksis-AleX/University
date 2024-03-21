#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

int MatrixChainOrder(int n, int* p){
    int** M = new int*[n+1];
    for(int i = 0; i < n+1; i++) M[i] = new int[n+1];
    int** s = new int*[n+1];
    for(int i = 0; i < n+1; i++) s[i] = new int[n+1];

    for(int i = 0; i < n+1; i++) M[i][i] = 0;

    for (int dlt = 1; dlt < n; dlt++)
    {
        for (int i = 1; i <= n-dlt; i++)
        {
            int j = dlt + i;
            M[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int q = M[i][k] + M[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < M[i][j]){
                    M[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    
    return M[1][n];
}

#define NTASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        int n; in >> n;
        int* p = new int[n+1];
        for (int i = 0; i < n; i++)
        {
            char tmp; in >> tmp;
            in >> p[i]; in >> tmp;
            if(i != n-1){ int itmp; in >> itmp;}
            else in >> p[i+1];
            in >> tmp;
        }
        cout << t+1 << ") New Matrix Chain : N = " << n << " [ ";
        for(int i = 0; i < n+1; i++) cout << p[i] << " ";
        cout << "]\n\n";
        out << MatrixChainOrder(n, p) << endl;
    }
    
    return 0;
}
