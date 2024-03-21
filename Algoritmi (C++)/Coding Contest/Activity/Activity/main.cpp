#include <iostream>
#include <fstream>
using namespace std;

struct Activity{
    int s;
    int f;
};

void sortActivities(Activity *&A, int n){
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(A[i].f > A[j].f || (A[i].f == A[j].f && A[i].s < A[j].s)) swap(A[i], A[j]);
        }
    }
}

int latestNonConflict(Activity *A, int index){
    for(int i = index-1; i >= 0; i--){
        if(A[i].f <= A[index].s) return i;
    }
    return -1;
}

int activitySelector(Activity *A, int n){
    sortActivities(A, n);

    int *table = new int[n];
    table[0] = A[0].f - A[0].s;

    for(int i = 1; i < n; i++){
        int profit = A[i].f - A[i].s;
        int latest = latestNonConflict(A, i);
        if(latest != -1) profit += table[latest];

        if(profit >= table[i-1]) table[i] = profit;
        else table[i] = table[i-1];
    }

    int res = table[n-1];
    delete[] table;
    return res;
}

#define NTASK 100
int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        int n; in >> n;
        Activity* A = new Activity[n];

        for(int i = 0; i < n; i++){
            char tmp; in >> tmp;
            in >> A[i].s;
            in >> A[i].f; in >> tmp;
        }

        out << activitySelector(A, n) << endl;

        delete[] A;
    }
    
}