#include <iostream>
#include <fstream>
using namespace std;

template <class T> class MaxHeap{
    private:
        T* queue;
        int heapsize;
        int maxLen;
        int heapifyCount;

        int left(int i){return i << 1;}
        int right(int i){return (i << 1) | 1;}
        int parent(int i){return i >> 1;}

        void moveUpKey(int i){
            while (i > 1 && queue[i] > queue[parent(i)])
            {
                swap(queue[i], queue[parent(i)]);
                i = parent(i);
            }
        }

        void heapify(int i){
            heapifyCount++;
            if(i > heapsize/2) return;

            int l = left(i);
            int r = right(i);
            int x = i;

            if(l <= heapsize && queue[l] > queue[x]) x = l;
            if(r <= heapsize && queue[r] > queue[x]) x = r;

            if(x == i) return;
            swap(queue[i], queue[x]);
            heapify(x);
        }

    public:
        MaxHeap(int _maxLen) : maxLen(_maxLen) {
            queue = new T[maxLen];
            heapsize = 0;
            heapifyCount = 0;
        }

        MaxHeap<T>* insert(T _key){
            if(heapsize == maxLen - 1) return this;

            queue[++heapsize] = _key;
            moveUpKey(heapsize);
            return this;
        }

        T extract(){
            T res = queue[1];
            swap(queue[1],queue[heapsize]);
            heapsize--;
            if(heapsize > 0) heapify(1);
            return res;
        }

        void print(ofstream &out){
            out << heapifyCount << " ";
            for(int i = 1; i <= heapsize; i++)
                out << queue[i] << " ";
        }
};