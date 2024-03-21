#include <iostream>

using namespace std;

template <class T>
class MaxHeap{

    private:
        T *queue;
        int heaplength;
        int heapsize;
    
        int parent(int i){ return i >> 1;}
        int left(int i){return i << 1;}
        int right(int i){return (i << 1) | 1;}

        void swap(int i, int j){
            T tmp = queue[i];
            queue[i] = queue[j];
            queue[j] = tmp;
        }

        void heapify(int i){
            if(i > heapsize/2) return;

            int l = left(i);
            int r = right(i);
            int x = i;

            if(l <= heapsize && queue[x] < queue[l]) x = l;
            if(r <= heapsize && queue[x] < queue[r]) x = r;
            if(x == i) return;

            swap(i, x);
            heapify(x);
        }

    public:
        MaxHeap(int heaplength){
            queue = new T[heaplength + 1];
            heapsize = 0;
        }

        void buildMaxHeap(T* A, int n){
            heapsize = n;
            for (int i = 0; i < n; i++)
            {
                queue[i+1] = A[i];
            }
            
            for (int i = heapsize/2; i >= 1; i--)
            {
                heapify(i);
            }
        }

        void print(){
            for (int i = 0; i < heapsize; i++)
            {
                cout << queue[i + 1] << " ";
            }
            cout << endl;
        }

        void print(ofstream &out_file){
            for (int i = 0; i < heapsize; i++)
            {
                out_file << queue[i + 1] << " ";
            }
            out_file << endl;
        }
};