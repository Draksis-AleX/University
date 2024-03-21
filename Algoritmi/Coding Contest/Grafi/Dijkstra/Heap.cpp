#include <iostream>
using namespace std;

template <class T> class Heap{
    private:
        int maxLen;
        int heapsize;
        T* queue;


        int left(int i){return i << 1;}
        int right(int i){return (i << 1) | 1;}
        int parent(int i){return i >> 1;}

        virtual double compare(T _a,  T _b) = 0;
        virtual void printKey(int i) = 0;

        void moveUpKey(int _index){
            while (_index > 1 && compare(queue[_index], queue[parent(_index)]) < 0)
            {
                swap(queue[_index], queue[parent(_index)]);
                _index = parent(_index);
            }
        }

        void heapify(int i){
            if(i > heapsize/2) return;
            
            int l = left(i);
            int r = right(i);
            int x = i;

            if(l <= heapsize && compare(queue[x], queue[l]) > 0) x = l;
            if(r <= heapsize && compare(queue[x], queue[r]) > 0) x = r;

            if(x == i) return;
            swap(queue[i], queue[x]);
            heapify(x);
        }

    public:
        Heap(int _maxLen) : maxLen(_maxLen) {
            heapsize = 0;
            queue = new T[maxLen];
        }

        int getMaxLen(){return maxLen;}
        int getHeapsize(){return heapsize;}
        T* getQueue(){return queue;}

        Heap<T>* enqueue(T _key){
            if(heapsize == maxLen-1) return this;

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

        void modifyKey(int _i, T _key){
            if(_i < 1 || _i > heapsize) return;
            if(compare(queue[_i], _key) <= 0) return;
            queue[_i] = _key;
            moveUpKey(_i);
            return;
        }

        void print(){
            for (int i = 1; i <= heapsize; i++)
            {
                cout << i << " [";
                printKey(i);
                cout << " ]";
            }
            cout << endl;
        }
};

template <class T> class PairMinHeap : public Heap<T>{
    private:
        double compare(T _a, T _b){return (double)_a.second - (double)_b.second;}
        void printKey(int i){cout << "(" << this->getQueue()[i].first << ", " << this->getQueue()[i].second << ") ";}
    public:
        PairMinHeap(int _maxLen) : Heap<T>(_maxLen) {}
        void decreaseKey(int _i, T _key){return Heap<T>::modifyKey(_i, _key);}
        int findIndex(int index){
            for (int i = 1; i <= this->getHeapsize(); i++)
            {
                if(this->getQueue()[i].first == index) return i;
            }
            return -1;
        }
};