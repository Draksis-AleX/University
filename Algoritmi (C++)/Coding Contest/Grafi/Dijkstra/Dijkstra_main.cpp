#include "Heap.cpp"
#include "Graph.cpp"
#include <climits>
#include <fstream>
using namespace std;

template <class T> void addNodes(Graph<T,int>* &g, int V, ifstream &in){
    for (int i = 0; i < V; i++)
    {
        T newKey; in >> newKey;
        g->addNode(newKey);
    }
}

template <class T> void addEdges(Graph<T, int>* &g, int E, ifstream &in){
    for (int i = 0; i < E; i++)
    {
        char tmp; in >> tmp;
        T x; in >> x; //in >> tmp;
        T y; in >> y; //in >> tmp;
        T w; in >> w; in >> tmp;
        g->addEdge(x, y, w);
    }
}

template <class T> int Djikstra(Graph<T,int>* g, T srcKey, int* &distances, int* &predecessors){
    int src = g->findIndex(srcKey);
    if(src < 0) return 0;

    int V = g->getNodeNumber();
    distances = new int[V];
    predecessors = new int[V];
    PairMinHeap< pair<int, T> > *queue = new PairMinHeap< pair<int,T> >(V);
    for (int i = 0; i < V; i++)
    {
        if(i == src) distances[i] = 0;
        else distances[i] = INT_MAX;
        predecessors[i] = -1;
        queue->enqueue(pair<int, T>(i, distances[i]));
    }

    while (queue->getHeapsize())
    {
        pair<int,T> top = queue->extract();
        if(top.second == INT_MAX) break;
        int tmp = top.first;
        for (int i = 0; i < V; i++)
        {
            if(g->getIndexMatrix()[tmp][i] == 1){
                T newWeigth = distances[tmp] + g->getWeightMatrix()[tmp][i];
                if(newWeigth < distances[i]){
                    distances[i] = newWeigth;
                    predecessors[i] = tmp;
                    int index = queue->findIndex(i);
                    queue->decreaseKey(index, pair<int,T>(i, newWeigth));
                }
            }
        }
    }
    delete queue;
    return 1;
}

#define NTASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        int V; in >> V;
        int E; in >> E;
        string type; in >> type;
        if(type == "int"){
            Graph<int, int>* graph = new Graph<int,int>(V);
            addNodes(graph, V, in);
            addEdges(graph, E, in);
            int* distances;
            int* predecessors;
            int srcKey; in >> srcKey;
            int destKey; in >> destKey;
            cout << t+1 << ") New Task : V = " << V << ", E = " << E << ", SRC = " << srcKey << ", DEST = " << destKey << ", type = " << type << "\n";
            //graph->print();
            Djikstra(graph, srcKey, distances, predecessors);
            out << distances[graph->findIndex(destKey)] << endl;
        }
        else if(type == "double"){
            Graph<double, int>* graph = new Graph<double,int>(V);
            addNodes(graph, V, in);
            addEdges(graph, E, in);
            int* distances;
            int* predecessors;
            double srcKey; in >> srcKey;
            double destKey; in >> destKey;
            cout << t+1 << ") New Task : V = " << V << ", E = " << E << ", SRC = " << srcKey << ", DEST = " << destKey << ", type = " << type << "\n";
            //graph->print();
            Djikstra(graph, srcKey, distances, predecessors);
            if(distances[graph->findIndex(destKey)] != INT_MAX) out << distances[graph->findIndex(destKey)] << endl;
            else out << "inf." << endl;
        }
    }
    
    return 0;
}
