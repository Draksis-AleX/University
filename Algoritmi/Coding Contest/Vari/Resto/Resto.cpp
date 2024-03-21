#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

int minCoin(int* tagli, int n, int r){
    int* table = new int[r+1];
    table[0] = 0;

    for(int i = 1; i < r+1; i++) table[i] = INT_MAX;

    for (int i = 1; i < r+1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(tagli[j] <= i){
                int sub_res = table[i - tagli[j]];
                if(sub_res != INT_MAX && sub_res + 1 < table[i]) table[i] = sub_res + 1;
            }
        }
    }
    
    int res = table[r];
    delete[] table;
    return res;
}

#define NTASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        int r; in >> r;
        int n; in >> n;

        int* tagli = new int[n];
        for (int i = 0; i < n; i++) in >> tagli[i];
        
        out << minCoin(tagli, n, r) << endl;

        delete[] tagli;
    }
    
    return 0;
}
