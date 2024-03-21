#include <iostream>
#include <fstream>
using namespace std;

template <class T> class Graph{
    private:
        T *keymap;
        int **indexMatrix;
        int **weightMatrix;
        int V, E, maxDim;

    public:
        Graph(int _maxDim) : maxDim(_maxDim){
            V = E = 0;
            keymap = new T[maxDim];
            indexMatrix = new int*[maxDim];
            weightMatrix = new int*[maxDim];
            for(int i = 0; i < maxDim; i++){
                indexMatrix[i] = new int[maxDim];
                weightMatrix[i] = new int[maxDim];
                keymap[i] = 0;
                for(int j = 0; j < maxDim; j++){
                    indexMatrix[i][j] = 0;
                    weightMatrix[i][j] = 0;
                }
            }
        }

        int getNodeNumber(){return V;}
        int** getIndexMatrix(){return indexMatrix;}
        int** getWeightMatrix(){return weightMatrix;}

        int findIndex(T key){
            for(int i = 0; i < V; i++) if(key == keymap[i]) return i;
            return -1;
        }

        void addNode(T _key){
            if(findIndex(_key) >= 0) return;
            keymap[V++] = _key;
        }

        void addEdge(T _srcKey, T _destKey, int _weight){
            int i = findIndex(_srcKey);
            int j = findIndex(_destKey);
            if(i < 0 || j < 0) return;

            indexMatrix[i][j] = 1;
            weightMatrix[i][j] = _weight;
            E++;
        }
};