#include <iostream>
using namespace std;

template <class T> class MinHeap{
    private:
        T* queue;
        int maxLen;
        int heapsize;
        int heapify_counter;

        int left(int i){return i << 1;}
        int right(int i){return (i << 1) | 1;}
        int parent(int i){return i >> 1;}

        void heapify(int i){
            heapify_counter++;
            if(i < 1 || i > heapsize/2) return;

            int l = left(i);
            int r = right(i);
            int x = i;

            if(l <= heapsize && queue[l] < queue[x]) x = l;
            if(r <= heapsize && queue[r] < queue[x]) x = r;
            if(x == i) return;

            swap(queue[x], queue[i]);
            heapify(x);
        }

    public:
        MinHeap(int _maxLen) : maxLen(_maxLen+1){
            queue = new T[maxLen];
            heapsize = heapify_counter = 0;
        }

        int getHeapifyCount(){return heapify_counter;}

        void buildHeap(T* A, int n){
            heapsize = n;
            for(int i = 0; i < n; i++) queue[i+1] = A[i];
            for(int i = heapsize/2; i > 0; i--) heapify(i);
        }

        T extract(){
            T res = queue[1];
            swap(queue[1], queue[heapsize--]);
            if(heapsize > 0) heapify(1);
            return res;
        }

        void heapSort(T* &A, int n){
            buildHeap(A, n);

            while (heapsize > 0)
                extract();

            for(int i = 0; i < n; i++) A[i] = queue[i+1];   
        }
};