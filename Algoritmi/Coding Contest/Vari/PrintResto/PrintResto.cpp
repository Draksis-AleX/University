#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

void printResult(int* res, int n, ofstream& out){
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if(res[i] > res[j]) swap(res[i], res[j]);
        }
    }

    for(int i = 0; i < n; i++) out << res[i] <<" ";
    out << endl;
}

void Resto(int r, int* tagli, int n, ofstream &out){
    int* table = new int[r+1];
    int* s = new int[r+1];
    table[0] = 0;
    s[0] = 0;

    for(int i = 1; i < r+1; i++){
        table[i] = INT_MAX;
        s[i] = 0;
    }

    for (int i = 1; i < r+1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(tagli[j] <= i){
                int sub_res = table[i - tagli[j]];
                if(sub_res != INT_MAX && sub_res + 1 < table[i]){
                    table[i] = sub_res + 1;
                    s[i] = j;
                }
            }
        }
    }

    int k = r;
    int i = 0;
    int* res = new int[table[r]];
    while(k > 0){
        res[i] = tagli[s[k]];
        i++;
        k -= tagli[s[k]];
    }

    out << table[r] << " ";
    printResult(res, table[r], out);
};

#define N_TASK 100
int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int t = 0; t < N_TASK; t++){
        int r; in >> r;
        int n; in >> n;
        
        int* vett = new int[n];

        for(int j = 0; j < n; j++)
            in >> vett[j];

        for(int i = 0; i < n; i++)
            for(int j = i+1; j < n; j++)
                if(vett[i] > vett[j]) swap(vett[i], vett[j]);

        cout << t+1 <<"] ";
        for(int j = 0; j < n; j++)
            cout << vett[j] << " ";
        cout << "\n\n";

        Resto(r, vett, n, out);

        delete[] vett; 
    }
}
