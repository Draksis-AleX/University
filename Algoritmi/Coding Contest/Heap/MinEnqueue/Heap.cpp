#include <iostream>
#include <fstream>

using namespace std;

template <class T> class Heap{
    private:
        T* queue;
        int heapsize;
        int queueLength;

        int parent(int i) { return i >> 1; }
        int left(int i) { return i << 1; }
        int right(int i) { return (i << 1) | 1; }

        virtual double compare(T x, T y) = 0;

        void heapify(int i){
            if(i > heapsize/2) return;

            int l = left(i);
            int r = right(i);
            int x = i;

            if(l <= heapsize && compare(queue[x], queue[l]) < 0) x = l;
            if(r <= heapsize && compare(queue[x], queue[r]) < 0) x = r;
            if(x == i) return;

            swap(queue[i], queue[x]);
            heapify(x);
        }

        void moveUpKey(int i){
            while (i > 1 && compare(queue[i], queue[parent(i)]) > 0)
            {
                swap(queue[i], queue[parent(i)]);
                i = parent(i);
            }
        }
    
    public:

        Heap(int _queueLength){
            queueLength = _queueLength + 1;
            heapsize = 0;
            queue = new T[_queueLength + 1];
        }

        Heap(int _queueLength, T* A){
            queueLength = _queueLength;
            heapsize = 0;
            queue = new T[_queueLength + 1];
            buildHeap(A, _queueLength);
        }

        void buildHeap(T* A, int n){
            heapsize = n;
            for(int i = 0; i < n; i++) queue[i+1] = A[i];
            for(int i = heapsize/2; i > 0; i--) heapify(i);
        }

        T extract(){
            T r = queue[1];
            swap(queue[1], queue[heapsize]);
            heapsize--;
            heapify(1);
            return r;
        }

        Heap<T>* enqueue(T key){
            if (heapsize == queueLength - 1) return this;

            heapsize++;
            queue[heapsize] = key;
            moveUpKey(heapsize);
            return this;
        }

        void print(){
            string res;
            for(int i = 0; i < heapsize; i++) cout << queue[i+1] << " ";
        }

        void print(ostream &out){
            string res;
            for(int i = 0; i < heapsize; i++) out << queue[i+1] << " ";
        }
};

template <class T> class MaxHeap : public Heap<T>{
    private:

        double compare(T x, T y){
            return (double)x - (double)y;
        }   

    public:

        MaxHeap(int _queueLenght) : Heap<T>(_queueLenght) {}
        MaxHeap(int _queueLenght, T* A) : Heap<T>(_queueLenght, A) {}
};

template <class T> class MinHeap : public Heap<T>{
    private:

        double compare(T x, T y){
            return (double)y - (double)x;
        }

    public:

        MinHeap(int _queueLenght) : Heap<T>(_queueLenght) {}
        MinHeap(int _queueLenght, T* A) : Heap<T>(_queueLenght, A) {}
};