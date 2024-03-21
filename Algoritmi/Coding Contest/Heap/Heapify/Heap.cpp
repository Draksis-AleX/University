#include <iostream>
#include <fstream>

using namespace std;

template <class T> class Heap{
    private:
        T* queue;
        int heapsize;
        int queueLength;
        int heapify_count;

        int parent(int i) { return i >> 1; }
        int left(int i) { return i << 1; }
        int right(int i) { return (i << 1) | 1; }

        virtual double compare(T x, T y) = 0;

        void heapify(int i){
            heapify_count++;
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
            heapify_count = 0;
            queue = new T[_queueLength + 1];
        }

        int getHeapifyCount(){ return heapify_count; }

        void buildHeap(T* A, int n){
            heapsize = n;
            cout << "Heapsize : " << heapsize << endl;
            for(int i = 0; i < n; i++) queue[i+1] = A[i];
            this->print();
            for(int i = heapsize/2; i > 0; i--){
                heapify(i);
            } 
        }

        T extract(){
            T r = queue[1];
            swap(queue[1], queue[heapsize]);
            heapsize--;
            if(heapsize > 0) heapify(1);
            return r;
        }

        Heap<T>* enqueue(T key){
            if (heapsize == queueLength - 1) return this;

            heapsize++;
            queue[heapsize] = key;
            moveUpKey(heapsize);
            return this;
        }

        void empty(){
            this->print();
            while (heapsize != 0)
            {
                this->extract();
            }         
        }

        void print(){
            string res;
            for(int i = 0; i < heapsize; i++) cout << queue[i+1] << " ";
            cout << endl;
        }

        void print(ostream &out){
            string res;
            for(int i = 0; i < heapsize; i++) out << queue[i+1] << " ";
            cout << endl;
        }
};

template <class T> class MaxHeap : public Heap<T>{
    private:

        double compare(T x, T y){
            return (double)x - (double)y;
        }   

    public:

        MaxHeap(int _queueLenght) : Heap<T>(_queueLenght) {}
};

template <class T> class MinHeap : public Heap<T>{
    private:

        double compare(T x, T y){
            return (double)y - (double)x;
        }

    public:

        MinHeap(int _queueLenght) : Heap<T>(_queueLenght) {}
};