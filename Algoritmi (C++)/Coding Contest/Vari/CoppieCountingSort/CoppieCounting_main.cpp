#include <iostream>
#include <fstream>

using namespace std;

pair<double, double> findMaxMin(pair<double, double>* &A, int n){
    double max = A[0].first;
    double min = A[0].first;
    for (int i = 1; i < n; i++)
    {
        if(A[i].first < min) min = A[i].first;
        if(A[i].first > max) max = A[i].first;
    }
    return pair<double, double>(max, min);
}

void CountingSort(pair<double, double>* &A, int n, int* &c, int &m){
    pair<double, double> max_min = findMaxMin(A, n);
    int max = max_min.first;
    int min = max_min.second;
    cout << "Max = " << max << " - Min = " << min << endl;
    m = max-min+1;

    c = new int[m];
    for(int i = 0; i < m; i++) c[i] = 0;
    for(int i = 0; i < n; i++) c[(int)A[i].first-min]++;
    for(int i = 1; i < m; i++) c[i] += c[i-1];

    pair<double, double>* B = new pair<double, double>[n];
    for (int i = n-1; i >= 0; i--)
    {
        B[c[(int)A[i].first - min]-1] = A[i];
        c[(int)A[i].first - min]--;
    }
    
    for(int i = 0; i < n; i++) A[i] = B[i];
}

#define N_TASK 100
int main(int argc, char const *argv[])
{   
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < N_TASK; t++)
    {
        int n; in >> n;
        pair<double, double>* A = new pair<double, double>[n];
        cout << t+1 << ") A [ ";
        for (int i = 0; i < n; i++)
        {
            char tmp; in >> tmp;
            double n1; in >> n1; //in >> tmp;
            double n2; in >> n2; in >> tmp;
            n1 *= 10;
            A[i].first = n1;
            A[i].second = n2;
            cout << "(" << A[i].first << ", " << A[i].second << ") ";
        }
        cout << "]\n\n";
        int* c;
        int m;
        CountingSort(A, n, c, m);
        cout << "A [ ";
        for(int i = 0; i < n; i++) cout << "(" << A[i].first << ", " << A[i].second << ") ";
        cout << "]\n\n";
        for(int i = 0; i < m; i++) out << c[i] << " ";
        for(int i = 0; i < n; i++) out << "(" << (double)A[i].first/10 << " " << A[i].second << ") ";
        out << endl;
    }
    return 0;
}
