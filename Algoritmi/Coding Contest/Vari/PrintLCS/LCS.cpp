#include <iostream>
#include <fstream>
using namespace std;

#define UP 'u'
#define LEFT 'l'
#define DIAG 'd'

int LCS_Lenght(string x, string y, int n, int m, char** &print_matr){
    int** matr = new int*[n+1];
    print_matr = new char*[n+1];
    for(int i = 0; i < n+1; i++){ 
        matr[i] = new int[m+1];
        print_matr[i] = new char[m+1];
    }
 
    for(int i = 0; i < n+1; i++) matr[i][0] = 0;
    for(int i = 0; i < m+1; i++) matr[0][i] = 0;

    for (int i = 0; i < n+1; i++)
    {
        for (int j = 0; j < m+1; j++)
        {
            print_matr[i][j] = '-';
        }
    }

    for (int i = 1; i < n+1; i++)
    {
        for (int j = 1; j < m+1; j++)
        {
            if(x[i-1] == y[j-1]){ 
                matr[i][j] = matr[i-1][j-1] + 1;
                print_matr[i][j] = DIAG;
            }
            else if(matr[i-1][j] > matr[i][j-1]){
                matr[i][j] = matr[i-1][j];
                print_matr[i][j] = UP;
            }
            else{ 
                matr[i][j] = matr[i][j-1];
                print_matr[i][j] = LEFT;
            }
        }
    }
    
    int res = matr[n][m];
    for(int i = 0; i < n+1; i++) delete[] matr[i];
    delete[] matr;
    return res;
}

void print_LCS(char** print_matr, string x, int i, int j){
    if(i == 0 || j == 0) return;

    if(print_matr[i][j] == DIAG){
        print_LCS(print_matr, x, i-1, j-1);
        cout << x[i-1];
    }
    else if(print_matr[i][j] == UP) print_LCS(print_matr, x, i-1, j);
    else print_LCS(print_matr, x, i, j-1);
}

void print_LCS(char** print_matr, string x, int i, int j, ofstream &out){
    if(i == 0 || j == 0) return;

    if(print_matr[i][j] == DIAG){
        print_LCS(print_matr, x, i-1, j-1, out);
        out << x[i-1];
    }
    else if(print_matr[i][j] == UP) print_LCS(print_matr, x, i-1, j, out);
    else print_LCS(print_matr, x, i, j-1, out);
}
