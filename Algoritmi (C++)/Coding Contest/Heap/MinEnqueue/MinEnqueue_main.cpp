#include "Heap.cpp"
#include <fstream>
using namespace std;

template <class T> void fillHeap(MinHeap<T>* &heap, int n_op, ifstream &in){
    for (int i = 0; i < n_op; i++)
    {
        T key; in >> key;
        heap->enqueue(key);
    }
}

#define N_TASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < N_TASK; t++)
    {
        string type; in >> type;
        int n_op; in >> n_op;

        if(type == "int"){
            MinHeap<int>* heap = new MinHeap<int>(n_op);
            fillHeap(heap, n_op, in);
            heap->print(out);
            out << endl;
        }
        else if(type == "double"){
            MinHeap<double>* heap = new MinHeap<double>(n_op);
            fillHeap(heap, n_op, in);
            heap->print(out);
            out << endl;
        }
        else if(type == "bool"){
            MinHeap<bool>* heap = new MinHeap<bool>(n_op);
            fillHeap(heap, n_op, in);
            heap->print(out);
            out << endl;
        }
        else if(type == "char"){
            MinHeap<char>* heap = new MinHeap<char>(n_op);
            fillHeap(heap, n_op, in);
            heap->print(out);
            out << endl;
        }
    }
    
    return 0;
}
