#include "Heap.cpp"
#include "Graph.cpp"
#include "HashTable.cpp"
#include <fstream>
#include <climits>

using namespace std;

template <class H, class T> int Dijkstra(Graph<H,T>* graph, H keysrc, T* &distances, int* &predecessors, int &_dk_calls){
    int src = graph->findIndex(keysrc);
    if(src < 0) return 0;
    int V = graph->getNodeNumber();
    distances = new T[V];
    predecessors = new int[V];
    PairMinHeap< pair<int,T> >*q = new PairMinHeap< pair<int,T> >(V);
    for (int i = 0; i < V; i++)
    {
        if(i == src) distances[i] = 0;
        else distances[i] = INT_MAX;
        predecessors[i] = -1;
        q->enqueue(pair<int, T>(i, distances[i]));
    }

    while (q->size())
    {   
        pair<int, T> top = q->extract();
        if(top.second == INT_MAX) break;
        int tmp = top.first;
        for (int i = 0; i < V; i++)
        {
            if(graph->getIndexMatrix()[tmp][i] == 1){
                T newWeight = distances[tmp] + graph->getWeightMatrix()[tmp][i];
                if(newWeight < distances[i]){
                    distances[i] = newWeight;
                    predecessors[i] = tmp;
                    int index = q->findIndex(i);
                    q->decreaseKey(index, pair<int, T>(i , newWeight));
                    _dk_calls++;
                }
            }
        }
    }
    delete q;
    return 1;
}

template <class H, class T> void printDistances(Graph<H,T>* _graph, H _srckey, T* distances, int* predecessors){
    if(predecessors == NULL || distances == NULL || _graph->findIndex(_srckey) < 0) return;

    cout << "Printing Dijkstra distances...\n\n";
    int src = _graph->findIndex(_srckey);
    for (int i = 0; i < _graph->getNodeNumber(); i++)
    {
        if(i == src) continue;
        cout << _srckey << " --> " << _graph->getKey(i) << " = ";
        if(distances[i] == INT_MAX) cout << "inf." << endl;
        else cout << distances[i] << endl; 
    }

    cout << "Printing predecessor list...\n\n";
    for (int i = 0; i < _graph->getNodeNumber(); i++)
    {
        if(i == src) continue;
        cout << "pred[ " << _graph->getKey(i) << " ] = ";
        if(predecessors[i] > -1) cout << predecessors[i] << endl;
        else cout << "unreachable" << endl;
    }
}

template <class T> void insertNodes(Graph<T, int>* &_graph, int _V, ifstream &_in){
    for (int i = 0; i < _V; i++)
    {
        T newKey; _in >> newKey;
        _graph->addNode(newKey);
    }
}

template <class T> void insertEdges(Graph<T, int>* &_graph, int _E, ifstream &_in){
    for (int i = 0; i < _E; i++)
    {
        char tmp; _in >> tmp;
        T src; _in >> src;
        T dest; _in >> dest;
        int weight; _in >> weight;
        _in >> tmp;
        _graph->addEdge(src, dest, weight);
    }
    
}

#define N_TASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < N_TASK; t++)
    {
        int V; in >> V;
        int E; in >> E;
        string type; in >> type;

        if(type == "int"){
            Graph<int, int>* graph = new Graph<int,int>(V);
            insertNodes(graph, V, in);
            insertEdges(graph, E, in);
            int srckey; in >> srckey;
            int destkey; in >> destkey;
            int* distances = NULL;
            int* predecessors = NULL;
            int dk_calls = 0;
            cout << "\nNew Graph : V = " << V << ", E = " << E << ", type = " << type << ", src = " << srckey << ", dest = " << destkey << "\n\n";
            Dijkstra(graph, srckey, distances, predecessors, dk_calls);
            OpenHashTable<int>* table = new OpenHashTable<int>(E);
            for (int i = 0; i < V; i++)
            {
                table->insert((int) distances[i]);
            }
            table->print();
            //printDistances(graph, srckey, distances, predecessors);
            cout << distances[graph->findIndex(destkey)] << endl;
            cout << "Index hashTable: " << table->search(distances[graph->findIndex(destkey)]);
            out << table->search(distances[graph->findIndex(destkey)]) << " " << dk_calls << endl;
        }
        else if(type == "double"){
            Graph<double, int>* graph = new Graph<double,int>(V);
            insertNodes(graph, V, in);
            insertEdges(graph, E, in);
            double srckey; in >> srckey;
            double destkey; in >> destkey;
            int* distances = NULL;
            int* predecessors = NULL;
            int dk_calls = 0;
            cout << "New Graph : V = " << V << ", E = " << E << ", type = " << type << ", src = " << srckey << ", dest = " << destkey << "\n\n";
            Dijkstra(graph, srckey, distances, predecessors, dk_calls);
            OpenHashTable<int>* table = new OpenHashTable<int>(E);
            for (int i = 0; i < V; i++)
            {
                table->insert((int) distances[i]);
            }
            table->print();
            cout << distances[graph->findIndex(destkey)] << endl;
            cout << "Index hashTable: " << table->search(distances[graph->findIndex(destkey)]);
            out << table->search(distances[graph->findIndex(destkey)]) << " " << dk_calls << endl;
        }
    }
    
    return 0;
}
