#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

#define ADD 0
#define DELETE 1

template <class H, class T> class Graph{

    private:
        int max_len, V, E;
        H** keymap;
        T** weight_matrix;
        int** index_matrix;
        int root_index;

        Graph<H, T>* modifyEdge(H x, H y, T weight, int flag){
            int i = findIndex(x);
            int j = findIndex(y);

            if(i < 0 || j < 0) return this;

            if(index_matrix[i][j] == flag){
                if(flag == ADD){
                    index_matrix[i][j] = 1;
                    E++;
                }
                else{
                    index_matrix[i][j] = 0;
                    E--;
                }
                weight_matrix[i][j] = weight;
            }
            return this;
        }

    public:

        Graph(int _max_len){
            this->max_len = _max_len;
            index_matrix = new int*[max_len];
            weight_matrix = new T*[max_len];
            keymap = new H*[max_len];
            V = E = 0;
            root_index = -1;
            for (int i = 0; i < max_len; i++)
            {
                keymap[i] = NULL;
                index_matrix[i] = new int[max_len];
                weight_matrix[i] = new T[max_len];
                for (int j = 0; j < max_len; j++)
                {
                    index_matrix[i][j] = 0;
                    weight_matrix[i][j] = NULL;
                }
            }
        }

        //========================= GETTERS ==============================

        int getRootIndex(){ return root_index; }
        int getMaxNodeNumber(){ return max_len; }
        int getNodeNumber(){ return V; }
        int GetEdgeNumber(){ return E; }
        H** getKeyMatrix(){ return keymap; }
        T** getWeightMatrix(){ return weight_matrix; }
        int** getIndexMatrix(){ return index_matrix; }
        H* getKey(int index){
            if(index < 0 || index >= V) return NULL;
            return keymap[index];
        }

        int findIndex(H x){
            for(int i = 0; i < V; i++)
                if(*keymap[i] == x) return i;
            return -1;
        }

        //======================== EDITING ================================

        Graph<H, T>* addNode(H k){
            if(V == max_len) return this;
            if(findIndex(k) >= 0) return this;

            keymap[V] = new H(k);
            V++;
            return this;
        }

        Graph<H, T>* deleteNode(H k){
            int pos = findIndex(k);
            if(pos < 0 || V == 0 || pos == root_index) return this;

            for (int i = pos; i < V - 1; i++)
                for (int j = 0; j < V - 1; j++)
                {
                    index_matrix[j][i] = index_matrix[j][i+1];
                    weight_matrix[j][i] = weight_matrix[j][i+1];
                }
            
            for(int i = pos; i < V - 2; i++)
                for (int j = 0; j < V - 2; j++)
                {
                    index_matrix[i][j] = index_matrix[i+1][j];
                    weight_matrix[i][j] = weight_matrix[i+1][j];
                }
                
            for (int i = 0; i < V; i++)
            {
                index_matrix[i][V-1] = 0;
                index_matrix[V-1][i] = 0;
                weight_matrix[i][V-1] = NULL;
                weight_matrix[V-1][i] = NULL;
            }
            
            for(int i = pos; i < V; i++) keymap[i] = keymap[i+1];
            keymap[V-1] = NULL;
            V--;
            return this;
        }

        Graph<H, T>* addEdge(H x, H y, T weight){
            return this->modifyEdge(x, y, weight, ADD);
        }

        Graph<H, T>* deleteEdge(H x, H y, T weight){
            return this->modifyEdge(x, y, NULL, DELETE);
        }

    //=========================== PRINT =================================

    void print(){
        for (int i = 0; i < V; i++)
        {
            cout << "(" << i << ", " << *keymap[i] << ")" << " --> ";
            for(int j = 0; j < V; j++)
                if(index_matrix[i][j]) cout << "{" << *keymap[j] << ", " << weight_matrix[i][j] << "} ";
            cout << endl;
        }   
    }

    void printIndexMatrix(){
        for (int i = 0; i < V; i++)
        {
            for(int j = 0; j < V; j++)
                cout << index_matrix[i][j];
            cout << endl;
        }   
    }

    void printWeightMatrix(){
        for (int i = 0; i < V; i++)
        {
            for(int j = 0; j < V; j++)
                cout << weight_matrix[i][j];
            cout << endl;
        }   
    }
};