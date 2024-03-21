#include <iostream>
#include <fstream>
using namespace std;

template <class T> class Heap{
    private:
        int maxLen;
        int heapsize;
        T* queue;

        int left(int i){return i << 1;}
        int right(int i){return (i << 1) | 1;}
        int parent(int i){return i >> 1;}

        virtual double compare(T a, T b) = 0;
        virtual void printKey(int i) = 0;

        void moveUpKey(int i){
            while (i > 1 && compare(queue[i], queue[parent(i)]) < 0)
            {
                swap(queue[parent(i)], queue[i]);
                i = parent(i);
            }
        }

        void heapify(int i){
            if(i < 1 || i > heapsize/2) return;

            int l = left(i);
            int r = right(i);
            int x = i;

            if(l <= heapsize && compare(queue[x], queue[l]) > 0) x = l;
            if(r <= heapsize && compare(queue[x], queue[r]) > 0) x = r;

            if(x == i) return;
            swap(queue[x],queue[i]);
            heapify(x);
        }

    public:
        Heap(int _maxLen) : maxLen(_maxLen + 1) {
            heapsize = 0;
            queue = new T[maxLen];
        }

        T* getQueue(){return queue;}

        Heap<T>* insert(T _key){
            if(heapsize == maxLen - 1) return this;

            queue[++heapsize] = _key;
            moveUpKey(heapsize);
            return this;
        }

        T extract(){
            T res = queue[1];
            swap(queue[1], queue[heapsize]);
            heapsize--;
            if(heapsize > 0) heapify(1);
            return res;
        }

        void buildHeap(T* A, int n){
            if(n > maxLen) return;
            cout << "Building Heap...\n";
            heapsize = n;
            for(int i = 0; i < n; i++) queue[i+1] = A[i];
            for(int i = heapsize/2; i > 0; i--) heapify(i);
        }

        void print(){
            for (int i = 1; i <= heapsize; i++)
                cout << queue[i] << " ";
        }

        void print(ofstream &out){
            for (int i = 1; i <= heapsize; i++)
                out << queue[i] << " ";
        }
};

template <class T> class MinHeap : public Heap<T>{
    private:
        double compare(T a, T b){return (double)a - (double)b;}
        void printKey(int i){cout << this->getQueue()[i];}
    public:
        MinHeap(int _maxLen) : Heap<T>(_maxLen) {}
};