#include "Heap.cpp"

#define N_TASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < N_TASK; t++)
    {
        string type; in >> type;
        int n; in >> n;

        if(type == "int"){
            int* A = new int[n];
            for (int i = 0; i < n; i++) in >> A[i];
            MaxHeap<int>* heap = new MaxHeap<int>(n);
            heap->buildHeap(A, n);
            heap->empty();
            out << heap->getHeapifyCount() << endl;
        }
        else if(type == "double"){
            double* A = new double[n];
            for (int i = 0; i < n; i++) in >> A[i];
            MaxHeap<double>* heap = new MaxHeap<double>(n);
            heap->buildHeap(A, n);
            heap->empty();
            out << heap->getHeapifyCount() << endl;
        }
        else if(type == "bool"){
            bool* A = new bool[n];
            for (int i = 0; i < n; i++) in >> A[i];
            MaxHeap<bool>* heap = new MaxHeap<bool>(n);
            heap->buildHeap(A, n);
            heap->empty();
            out << heap->getHeapifyCount() << endl;
        }
        else if(type == "char"){
            char* A = new char[n];
            for (int i = 0; i < n; i++) in >> A[i];
            MaxHeap<char>* heap = new MaxHeap<char>(n);
            heap->buildHeap(A, n);
            heap->empty();
            out << heap->getHeapifyCount() << endl;
        }
    }
    
    return 0;
}
