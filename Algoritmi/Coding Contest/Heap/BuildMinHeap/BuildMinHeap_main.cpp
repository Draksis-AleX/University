#include "Heap.cpp"
using namespace std;

#define NTASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        string type; in >> type;
        int n; in >> n;
        if(type == "int"){
            MinHeap<int>* heap = new MinHeap<int>(n);
            int* A = new int[n];
            for(int i = 0; i < n; i++) in >> A[i];
            cout << t+1 << ") : New Task, A = ";
            for(int i = 0; i < n; i++) cout << A[i] << " ";
            heap->buildHeap(A, n);
            heap->print();
            heap->print(out);
            out << endl;
            cout << endl;
        }
        else if(type == "double"){
            MinHeap<double>* heap = new MinHeap<double>(n);
            double* A = new double[n];
            for(int i = 0; i < n; i++) in >> A[i];
            cout << t+1 << ") : New Task, A = ";
            for(int i = 0; i < n; i++) cout << A[i] << " ";
            heap->buildHeap(A, n);
            heap->print();
            heap->print(out);
            out << endl;
            cout << endl;
        }
        else if(type == "bool"){
            MinHeap<bool>* heap = new MinHeap<bool>(n);
            bool* A = new bool[n];
            for(int i = 0; i < n; i++) in >> A[i];
            cout << t+1 << ") : New Task, A = ";
            for(int i = 0; i < n; i++) cout << A[i] << " ";
            heap->buildHeap(A, n);
            heap->print();
            heap->print(out);
            out << endl;
            cout << endl;
        }
        else if(type == "char"){
            MinHeap<char>* heap = new MinHeap<char>(n);
            char* A = new char[n];
            for(int i = 0; i < n; i++) in >> A[i];
            cout << t+1 << ") : New Task, A = ";
            for(int i = 0; i < n; i++) cout << A[i] << " ";
            heap->buildHeap(A, n);
            heap->print();
            heap->print(out);
            out << endl;
            cout << endl;
        }
    }
    
    return 0;
}
