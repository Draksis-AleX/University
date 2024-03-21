#include <iostream>
using namespace std;

template <class T>
class Terna{
    public:
        T x;
        T y;
        T z;
        Terna() {x = y = z = NULL;}
};

template <class T> class MaxHeap{
    private:
        T* queue;
        int heapsize;
        int maxLen;
        int heapify_count;

        int left(int i){return i << 1;}
        int right(int i){return (i << 1) | 1;}
        int parent(int i){return i >> 1;}

        int compare(int a, int b){
            if(queue[a].x > queue[b].x) return 1;
            else if(queue[a].x < queue[b].x) return -1;
            else{
                if(queue[a].y > queue[b].y) return 1;
                else if(queue[a].y < queue[b].y) return -1;
                else{
                    if(queue[a].z > queue[b].z) return 1;
                    else if(queue[a].z < queue[b].z) return -1;
                    else return 0;
                }
            }
        }

        void heapify(int i){
            heapify_count++;
            if(i > heapsize/2) return;

            int l = left(i);
            int r = right(i);
            int x = i;

            if(l <= heapsize && compare(l, x) > 0) x = l;
            if(r <= heapsize && compare(r, x) > 0) x = r;

            if(x == i) return;
            swap(queue[x], queue[i]);
            heapify(x);
        }
    
    public:
        MaxHeap(int _maxLen) : maxLen(_maxLen + 1){
            heapsize = heapify_count = 0;
            queue = new T[maxLen];
        }

        int getHeapifyCount(){return heapify_count;}

        void buildHeap(T* A, int n){
            for (int i = 0; i < n; i++)
                queue[i+1] = A[i];
            heapsize = n;
            for (int i = heapsize/2; i >= 1; i--)
                heapify(i);
        }

        T extract(){
            T res = queue[1];
            swap(queue[1], queue[heapsize--]);
            if(heapsize > 0) heapify(1);
            return res;
        }

        void heapsort(T* &A, int n){
            buildHeap(A, n);

            while (heapsize > 0)
                extract();
            
            for(int i = 0; i < n; i++) A[i] = queue[i+1];
        }
};