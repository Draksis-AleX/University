#include <iostream>
#include <fstream>
using namespace std;

struct Activity{
    int s;
    int f;
};

void sortActivities(Activity *A, int n){
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(A[i].f > A[j].f || (A[i].f == A[j].f && A[i].s < A[j].s)) swap(A[i], A[j]);
        }
    }
}

int greedyActivitySelector(Activity *A, int n){
    sortActivities(A, n);

    int card = 1;
    int m = 0;
    for(int i = 1; i < n; i++){
        if(A[i].s >= A[m].f){
            card++;
            m = i;
        }
    }

    return card;
}

#define NTASK 100
int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        int n; in >> n;
        Activity *A = new Activity[n];

        for(int i = 0; i < n; i++){
            char tmp; in >> tmp;
            in >> A[i].s;
            in >> A[i].f; in >> tmp;
        }

        out << greedyActivitySelector(A, n) << endl;

        delete[] A;
    }
    
}