#include "Graph.cpp"
#include <fstream>
using namespace std;

template <class T> int BellmannFord(Graph<T>* g, int *&distances, T srcKey){
    int srcIndex = g->findIndex(srcKey);
    if(srcIndex == -1) return 0;

    int V = g->getNodeNumber();
    distances = new int[V];
    for(int i = 0; i < V; i++) distances[i] = INT_MAX;
    distances[srcIndex] = 0;

    bool stop = false;
    for(int s = 0; s < V-1 && !stop; s++){
        stop = true;
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                if(distances[i] != INT_MAX && g->getIndexMatrix()[i][j] == 1){
                    int newWeight = distances[i] + g->getWeightMatrix()[i][j];
                    if(newWeight < distances[j]){
                        distances[j] = newWeight;
                        stop = false;
                    }
                }
            }
        }
    }

    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(distances[i] != INT_MAX && g->getIndexMatrix()[i][j] == 1){
                int newWeight = distances[i] + g->getWeightMatrix()[i][j];
                if(newWeight < distances[j]) return 0;
            }
        }
    }
    return 1;
}

#define NTASK 100
int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        int V; in >> V;
        int E; in >> E;
        string type; in >> type;

        if(type == "int"){
            Graph<int>* g = new Graph<int>(V);

            for(int i = 0; i < V; i++){
                int key; in >> key;
                g->addNode(key);
            }

            for(int i = 0; i < E; i++){
                char tmp; in >> tmp;
                int srcKey; in >> srcKey;
                int destKey; in >> destKey;
                int weight; in >> weight;
                in >> tmp;
                g->addEdge(srcKey, destKey, weight);
            }

            int src; in >> src;
            int dest; in >> dest;

            int *distances;
            if(BellmannFord(g, distances, src)){
                if(distances[g->findIndex(dest)] != INT_MAX) out << distances[g->findIndex(dest)];
                else out << "inf.";
            }
            else out << "undef.";
            out << endl;
        }
        else if(type == "double"){
            Graph<double>* g = new Graph<double>(V);

            for(int i = 0; i < V; i++){
                double key; in >> key;
                g->addNode(key);
            }

            for(int i = 0; i < E; i++){
                char tmp; in >> tmp;
                double srcKey; in >> srcKey;
                double destKey; in >> destKey;
                int weight; in >> weight;
                in >> tmp;
                g->addEdge(srcKey, destKey, weight);
            }

            double src; in >> src;
            double dest; in >> dest;

            int *distances;
            if(BellmannFord(g, distances, src)){
                if(distances[g->findIndex(dest)] != INT_MAX) out << distances[g->findIndex(dest)];
                else out << "inf.";
            }
            else out << "undef.";
            out << endl;

        }
    }
    
}