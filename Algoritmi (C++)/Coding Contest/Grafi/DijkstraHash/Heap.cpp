#include <iostream>
#include <queue>
using namespace std;

template <class T> class Heap{
    protected:
        T* queue;
        int heapsize;
        int maxlen;

        int parent(int _i){return _i >> 1;}
        int left(int _i){return _i << 1;}
        int right(int _i){return (_i << 1) | 1;}

        virtual double compare(T _x, T _y) = 0;
        virtual void printKey(int _i) = 0;

        void moveUpKey(int _index){
            while (_index > 1 && compare(queue[_index], queue[parent(_index)]) < 0)
            {
                swap(queue[_index], queue[parent(_index)]);
                _index = parent(_index);
            }
        }

        void heapify(int _index){
            if(_index > heapsize/2) return;

            int l = left(_index);
            int r = right(_index);
            int x = _index;

            if(l <= heapsize && compare(queue[x], queue[l]) > 0) x = l;
            if(r <= heapsize && compare(queue[x], queue[r]) > 0) x = r;
            if(x == _index) return;

            swap(queue[_index], queue[x]);
            heapify(x);
        }

    public:

        Heap(int _maxlen) : maxlen(_maxlen + 1) {
            heapsize = 0;
            queue = new T[maxlen];
        }

        int size(){return heapsize;}
        T* getQueue(){return queue;}

        Heap<T>* enqueue(T _key){
            if(heapsize == maxlen - 1) return this;

            heapsize++;
            queue[heapsize] = _key;
            moveUpKey(heapsize);
            return this;
        }

        T extract(){
            T r = queue[1];
            swap(queue[1], queue[heapsize--]);
            if(heapsize > 0) heapify(1);
            return r;
        }

        void modify(int _i, T _key){
            if(_i < 1 || _i > heapsize) return;
            if(compare(queue[_i], _key) <= 0) return;
            queue[_i] = _key;
            moveUpKey(_i);
            return; 
        }

        void print(){
            for (int i = 1; i <= heapsize; i++)
            {
                cout << i << "[ ";
                printKey(i);
                cout << " ] ";
            }
            cout << endl;
        }
};

template <class T> class PairMinHeap : public Heap<T>{
    public:
        PairMinHeap(int _maxlen) : Heap<T>(_maxlen) {}

        void decreaseKey(int _i, T _key){return Heap<T>::modify(_i, _key);}
        double compare(T _x, T _y){return (double)_x.second - (double)_y.second;}
        void printKey(int _i){cout << "(" << this->getQueue()[_i].first << ", " << this->getQueue()[_i].second << ")";}
        int findIndex(int _index){
            for (int i = 1; i <= this->heapsize; i++)
            {
                if(this->getQueue()[i].first == _index) return i;
            }
            return -1;
        }
};