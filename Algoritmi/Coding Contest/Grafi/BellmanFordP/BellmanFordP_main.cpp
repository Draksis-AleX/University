#include "Graph.cpp"
#include <fstream>
using namespace std;

template <class H, class T> int BellmanFord(Graph<H,T>* graph, H sourceKey, T* &distances, int* &predecessors, int k){
    int V = graph->getNodeNumber();
    distances = new T[V];
    predecessors = new int[V];
    int src = graph->findIndex(sourceKey);

    for (int i = 0; i < V; i++)
    {
        distances[i] = INT_MAX;
        predecessors[i] = -1;
    }
    distances[src] = 0;

    bool stop = false;
    for (int s = 0; s < V-1 && !stop && s < k; s++)
    {
        stop = true;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if(graph->getIndexMatrix()[i][j] == 1 && distances[i] != INT_MAX){
                    T weigth = graph->getWeightMatrix()[i][j];
                    if(distances[i] + weigth < distances[j]){
                        distances[j] = distances[i] + weigth;
                        predecessors[j] = i;
                        stop = false;
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if(graph->getIndexMatrix()[i][j] == 1 && distances[i] != INT_MAX){
                T weigth = graph->getWeightMatrix()[i][j];
                if(distances[i] + weigth < distances[j]) return 0;
            }
        }
    }
    return 1;
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
        int k; in >> k;

        Graph<int, int>* graph = new Graph<int, int>(V);

        for (int i = 0; i < V; i++) graph->addNode(i);
        
        for (int i = 0; i < E; i++)
        {
            char tmp; in >> tmp;
            int x; in >> x; //in >> tmp;
            int y; in >> y; //in >> tmp;
            int w; in >> w; in >> tmp;
            graph->addEdge(x, y, w);
        }

        cout << "Created new Graph with [ " << V << " ] nodes and [ " << E << " ] edges:\n\n";
        //graph->print();

        int source; in >> source;
        int dest; in >> dest;
        cout << "\nExecuting BellmannFord from source [ " << source << " ] to destination [ " << dest << " ]...\n\n";
        int* distances = new int[V];
        int* predecessors = new int[V];
        BellmanFord(graph, source, distances, predecessors, k);
        cout << "Res = " << distances[graph->findIndex(dest)] << "\n\n";
        if(distances[graph->findIndex(dest)] != INT_MAX) out << distances[graph->findIndex(dest)] << endl;
        else out << "inf." << endl;
        
        
        delete[] distances;
        delete[] predecessors;
        delete graph;
    }
    
    return 0;
}
