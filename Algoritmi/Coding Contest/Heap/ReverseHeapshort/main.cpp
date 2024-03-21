#include "Heap.cpp"
#include <fstream>
using namespace std;

#define NTASK 100
int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        string type; in >> type;
        int n; in >> n;

        if(type == "int"){
            int *A = new int[n];
            for(int i = 0; i < n; i++) in >> A[i];
            MinHeap<int> *h = new MinHeap<int>(n);
            h->heapSort(A, n);
            out << h->getHeapifyCount() << " ";
            for(int i = 0; i < n; i++) out << A[i] << " ";
            out << endl;
        }
        else if(type == "double"){
            double *A = new double[n];
            for(int i = 0; i < n; i++) in >> A[i];
            MinHeap<double> *h = new MinHeap<double>(n);
            h->heapSort(A, n);
            out << h->getHeapifyCount() << " ";
            for(int i = 0; i < n; i++) out << A[i] << " ";
            out << endl;
        }
        else if(type == "bool"){
            bool *A = new bool[n];
            for(int i = 0; i < n; i++) in >> A[i];
            MinHeap<bool> *h = new MinHeap<bool>(n);
            h->heapSort(A, n);
            out << h->getHeapifyCount() << " ";
            for(int i = 0; i < n; i++) out << A[i] << " ";
            out << endl;
        }
        else if(type == "char"){
            char *A = new char[n];
            for(int i = 0; i < n; i++) in >> A[i];
            MinHeap<char> *h = new MinHeap<char>(n);
            h->heapSort(A, n);
            out << h->getHeapifyCount() << " ";
            for(int i = 0; i < n; i++) out << A[i] << " ";
            out << endl;
        }
    }
    
}