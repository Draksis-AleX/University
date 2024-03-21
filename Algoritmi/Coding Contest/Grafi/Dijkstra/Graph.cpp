#include <iostream>
using namespace std;

template <class T, class W> class Graph{
    private:
        int maxNodeNumber;
        int V, E;
        int** indexMatrix;
        W** weightMatrix;
        T* keyMap;

        Graph<T,W>* modifyEdge(T _node1, T _node2, W weight, bool flag){
            int i = findIndex(_node1);
            int j = findIndex(_node2);
            if(i < 0 || j < 0) return this;

            if(indexMatrix[i][j] == flag){
                if(flag){
                    indexMatrix[i][j] = 0;
                    E--;
                }
                else{
                    indexMatrix[i][j] = 1;
                    E++;
                }
                weightMatrix[i][j] = weight;
            }
            return this;
        }

    public:
        Graph(int _maxNodeNumber) : maxNodeNumber(_maxNodeNumber){
            V = E = 0;
            keyMap = new T[maxNodeNumber];
            indexMatrix = new int*[maxNodeNumber];
            weightMatrix = new W*[maxNodeNumber];
            for (int i = 0; i < maxNodeNumber; i++)
            {
                indexMatrix[i] = new int[maxNodeNumber];
                weightMatrix[i] = new W[maxNodeNumber];
                for (int j = 0; j < maxNodeNumber; j++)
                {
                    indexMatrix[i][j] = 0;
                    weightMatrix[i][j] = NULL;
                }
            }
        }

        int getMaxNodeNumber(){return maxNodeNumber;}
        int getNodeNumber(){return V;}
        int getEdgeNumber(){return E;}
        int** getIndexMatrix(){return indexMatrix;}
        W** getWeightMatrix(){return weightMatrix;}
        T* getKeyMap(){return keyMap;}
        T getKey(int _index){return (_index < 0 || _index > maxNodeNumber - 1) ? NULL : keyMap[_index];}
        int findIndex(T _key){
            for(int i = 0; i < V; i++) if(keyMap[i] == _key) return i;
            return -1;
        }

        Graph<T,W>* addNode(T _key){
            if(V == maxNodeNumber || findIndex(_key) >= 0) return this;

            keyMap[V++] = _key;
            return this;
        }

        Graph<T,W>* addEdge(T _key1, T _key2, W weight){return modifyEdge(_key1, _key2, weight, 0);}

        Graph<T,W>* deleteNode(T _key){
            int pos = findIndex(_key);
            if(pos < 0) return this;

            for (int i = 0; i < V-1; i++)
            {
                for (int j = pos; j < V-1; j++)
                {
                    indexMatrix[i][j] = indexMatrix[i][j+1];
                    weightMatrix[i][j] = weightMatrix[i][j+1];
                }
            }
            for (int i = pos; i < V-1; i++)
            {
                for (int j = 0; j < V-1; j++)
                {
                    indexMatrix[i][j] = indexMatrix[i+1][j];
                    weightMatrix[i][j] = weightMatrix[i+1][j];
                }
            }
            for (int i = 0; i < V; i++)
            {
                indexMatrix[i][V-1] = 0;
                weightMatrix[i][V-1] = NULL;
                indexMatrix[V-1][i] = 0;
                weightMatrix[V-1][i] = NULL;
            }    
            for(int i = pos; i < V-1; i++) keyMap[i] = keyMap[i+1];

            keyMap[V-1] = NULL;
            V--;
            return this;
        }

        Graph<T,W>* deleteEdge(T _key1, T _key2){return modifyEdge(_key1, _key2, NULL, 1);}

        void print(){
            for (int i = 0; i < V; i++)
            {
                cout << "(" << i << ", " << keyMap[i] << ") --> ";
                for (int j = 0; j < V; j++)
                {
                    if(indexMatrix[i][j]) cout << "{" << keyMap[j] << ", " << weightMatrix[i][j] << "} ";
                }
                cout << endl;
            }
        }
};