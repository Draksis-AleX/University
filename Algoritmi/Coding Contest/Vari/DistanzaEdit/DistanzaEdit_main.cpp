#include <iostream>
#include <fstream>
using namespace std;

int EditDistance(string X, string Y, int n, int m){
    int** M = new int*[n+1];;
    for(int i = 0; i < n+1; i++) M[i] = new int[m+1];
    for(int i = 0; i < n+1; i++) M[i][0] = i;
    for(int i = 0; i < m+1; i++) M[0][i] = i;

    for (int i = 1; i < n+1; i++)
    {
        for (int j = 1; j < m+1; j++)
        {
            M[i][j] = M[i-1][j-1] + (X[i-1] == Y[j-1] ? 0 : 1);
            if(M[i-1][j] + 1 < M[i][j]) M[i][j] = M[i-1][j] + 1;
            if(M[i][j-1] + 1 < M[i][j]) M[i][j] = M[i][j-1] + 1;
        }  
    }
    
    int res = M[n][m];
    for(int i = 0; i < n+1; i++) delete[] M[i];
    delete[] M;
    return res;
}

#define NTASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        int n; in >> n;
        int m; in >> m;
        string X; in >> X;
        string Y; in >> Y;

        cout << EditDistance(X, Y, n, m) << endl;
        out << EditDistance(X, Y, n, m) << endl;
    }
    
    return 0;
}
