#include <iostream>
#include <fstream>
using namespace std;

#define CREATE 0
#define DELETE 1

template <class H, class T> class Graph{
    private:
        int maxlen;
        int V, E;
        H* keymap;
        T** weight_matrix;
        int** index_matrix;

        Graph<H,T>* modifyEdge(H _x, H _y, T _weight, bool _ind){
            int i = findIndex(_x);
            int j = findIndex(_y);
            if(i < 0 || j < 0) return this;

            if(index_matrix[i][j] == _ind){
                if(_ind){
                    index_matrix[i][j] = 0;
                    E--;
                }
                else{
                    index_matrix[i][j] = 1;
                    E++;
                }
                weight_matrix[i][j] = _weight;
            }
            return this;
        }

    public:
        Graph(int _maxlen) : maxlen(_maxlen) {
            index_matrix = new int*[maxlen];
            weight_matrix = new T*[maxlen];
            keymap = new H[maxlen];
            V = E = 0;
            for (int i = 0; i < maxlen; i++)
            {
                index_matrix[i] = new int[maxlen];
                weight_matrix[i] = new T[maxlen];
                for (int j = 0; j < maxlen; j++)
                {
                    index_matrix[i][j] = 0;
                    weight_matrix[i][j] = NULL;
                }
            }
        }

        int getMaxNodeNumber(){return maxlen;}
        int getNodeNumber(){return V;}
        int getEdgeNumber(){return E;}
        int** getIndexMatrix(){return index_matrix;}
        T** getWeightMatrix(){return weight_matrix;}
        H* getKeyMap(){return keymap;}

        int findIndex(H _key){
            for (int i = 0; i < V; i++)
            {
                if(keymap[i] == _key) return i;
            }
            return -1;
        }

        H getKey(int _index){
            if(_index < 0 || _index >= V) return NULL;
            return keymap[_index];
        }

        Graph<H,T>* addNode(H _key){
            if(V >= maxlen || findIndex(_key) >= 0) return this;

            keymap[V++] = _key;
            return this;
        }

        Graph<H,T>* deleteNode(H _key){
            int pos = findIndex(_key);
            if(pos < 0 || V == 0) return this;

            for (int i = 0; i < V-1; i++)
            {
                for (int j = pos; j < V-1; j++)
                {
                    index_matrix[i][j] = index_matrix[i][j+1];
                    weight_matrix[i][j] = weight_matrix[i][j+1];
                }
            }
            
            for (int i = pos; i < V-1; i++)
            {
                for (int j = 0; j < V-1; j++)
                {
                    index_matrix[i][j] = index_matrix[i+1][j];
                    weight_matrix[i][j] = weight_matrix[i+1][j];
                }
            }
            
            for (int i = 0; i < V; i++)
            {
                index_matrix[i][V-1] = 0;
                index_matrix[V-1][i] = 0;
                weight_matrix[i][V-1] = NULL;
                weight_matrix[V-1][i] = NULL;
            }
            
            for(int i = pos; i < V; i++)
                keymap[i] = keymap[i+1];
            keymap[V-1] = NULL;

            V--;
            return this;
        }

        Graph<H,T>* addEdge(H _x, H _y, T _weight){return modifyEdge(_x, _y, _weight, CREATE);}
        Graph<H,T>* deleteEdge(H _x, H _y){return modifyEdge(_x, _y, NULL, DELETE);}

        void print(){
            for (int i = 0; i < V; i++)
            {
                cout << "(" << i << ", " << keymap[i] << ") -->";
                for (int j = 0; j < E; j++)
                {
                    if(index_matrix[i][j]) cout << "{" << keymap[j] << ", " << weight_matrix[i][j] << "} ";
                }
                cout << endl;
            }
        }
};