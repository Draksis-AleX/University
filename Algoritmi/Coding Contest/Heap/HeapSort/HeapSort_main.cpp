#include "Heap.cpp"
using namespace std;

#define NTASK 3
int main(int argc, char const *argv[])
{
        ifstream in("input.txt");
        ofstream out("output.txt");

        for (int t = 0; t < NTASK; t++)
        {
            string type; in >> type;
            int n; in >> n;
            if(type == "int"){
                int* A = new int[n];
                for(int i = 0; i < n; i++) in >> A[i];
                cout << t+1 << ") New Task : A = ";
                for(int i = 0; i < n; i++) cout << A[i] << " ";
                cout << endl;
                MinHeap<int>* heap = new MinHeap<int>(n);
                heap->heapSort(A, n);
                cout << "Heapsort (HC = " << heap->getHeapifyCount() << ") --> ";
                for(int i = 0; i < n; i++) cout << A[i] << " ";
                cout << endl << endl;
            }
            else if(type == "double"){
                double* A = new double[n];
                for(int i = 0; i < n; i++) in >> A[i];
                cout << t+1 << ") New Task : A = ";
                for(int i = 0; i < n; i++) cout << A[i] << " ";
                cout << endl;
                MinHeap<double>* heap = new MinHeap<double>(n);
                heap->heapSort(A, n);
                cout << "Heapsort (HC = " << heap->getHeapifyCount() << ") --> ";
                for(int i = 0; i < n; i++) cout << A[i] << " ";
                cout << endl << endl;
            }
            else if(type == "bool"){
                bool* A = new bool[n];
                for(int i = 0; i < n; i++) in >> A[i];
                cout << t+1 << ") New Task : A = ";
                for(int i = 0; i < n; i++) cout << A[i] << " ";
                cout << endl;
                MinHeap<bool>* heap = new MinHeap<bool>(n);
                heap->heapSort(A, n);
                cout << "Heapsort (HC = " << heap->getHeapifyCount() << ") --> ";
                for(int i = 0; i < n; i++) cout << A[i] << " ";
                cout << endl << endl;
            }
            else if(type == "char"){
                char* A = new char[n];
                for(int i = 0; i < n; i++) in >> A[i];
                cout << t+1 << ") New Task : A = ";
                for(int i = 0; i < n; i++) cout << A[i] << " ";
                cout << endl;
                MinHeap<char>* heap = new MinHeap<char>(n);
                heap->heapSort(A, n);
                cout << "Heapsort (HC = " << heap->getHeapifyCount() << ") --> ";
                for(int i = 0; i < n; i++) cout << A[i] << " ";
                cout << endl << endl;
            }
            
        }
        
    
    return 0;
}
