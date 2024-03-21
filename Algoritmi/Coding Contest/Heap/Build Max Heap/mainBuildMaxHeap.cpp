#include <iostream>
#include <fstream>
#include "MaxHeap.cpp"
using namespace std;

#define TASKNUMBER 100

int main(int argc, char const *argv[])
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt", ios::app);
    string *op;
    string type;
    int n_e;

    for (int i = 0; i < TASKNUMBER; i++)
    {
        input_file >> type;
        //cout << type << endl;

        input_file >> n_e;
        //cout << n_e << endl;

        if (type == "bool")
        {
            bool *arr = new bool[n_e];
            for(int i = 0; i < n_e; i++) input_file >> arr[i];

            MaxHeap<bool> *max_heap = new MaxHeap<bool>(n_e);
            max_heap->buildMaxHeap(arr, n_e);
            max_heap->print();
            max_heap->print(output_file);
        }
        else if (type == "int")
        {
            int *arr = new int[n_e];
            for(int i = 0; i < n_e; i++) input_file >> arr[i];

            MaxHeap<int> *max_heap = new MaxHeap<int>(n_e);
            max_heap->buildMaxHeap(arr, n_e);
            max_heap->print();
            max_heap->print(output_file);
        }
        if (type == "double")
        {
            double *arr = new double[n_e];
            for(int i = 0; i < n_e; i++) input_file >> arr[i];

            MaxHeap<double> *max_heap = new MaxHeap<double>(n_e);
            max_heap->buildMaxHeap(arr, n_e);
            max_heap->print();
            max_heap->print(output_file);
        }
        if (type == "char")
        {
            char *arr = new char[n_e];
            for(int i = 0; i < n_e; i++) input_file >> arr[i];

            MaxHeap<char> *max_heap = new MaxHeap<char>(n_e);
            max_heap->buildMaxHeap(arr, n_e);
            max_heap->print();
            max_heap->print(output_file);
        }
        
    }
    
    input_file.close();
    output_file.close();
    return 0;
}