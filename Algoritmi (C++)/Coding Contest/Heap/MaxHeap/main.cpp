#include "Heap.cpp"
using namespace std;

#define NTASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        string type; in >> type;
        int nop; in >> nop;
        cout << t+1 << ") Type = " << type << ", NOP = " << nop << "----------------- \n\n";

        if(type == "int"){
            MaxHeap<int>* h = new MaxHeap<int>(nop);
            for (int i = 0; i < nop; i++)
            {
                string op; in >> op;
                if(op == "extract") h->extract();
                else{
                    int key = stoi(op.substr(op.find(":")+1, op.size()));
                    h->insert(key);
                }
            }
            h->print(out);
            out << endl;
        }
        else if(type == "double"){
            MaxHeap<double>* h = new MaxHeap<double>(nop);
            for (int i = 0; i < nop; i++)
            {
                string op; in >> op;
                if(op == "extract") h->extract();
                else{
                    double key = stod(op.substr(op.find(":")+1, op.size()));
                    h->insert(key);
                }
            }
            h->print(out);
            out << endl;
        }
        else if(type == "bool"){
            MaxHeap<bool>* h = new MaxHeap<bool>(nop);
            for (int i = 0; i < nop; i++)
            {
                string op; in >> op;
                if(op == "extract") h->extract();
                else{
                    bool key = stoi(op.substr(op.find(":")+1, op.size()));
                    h->insert(key);
                }
            }
            h->print(out);
            out << endl;
        }
        else if(type == "char"){
            MaxHeap<char>* h = new MaxHeap<char>(nop);
            for (int i = 0; i < nop; i++)
            {
                string op; in >> op;
                if(op == "extract") h->extract();
                else{
                    char key = op.substr(op.find(":")+1, op.size())[0];
                    h->insert(key);
                }
            }
            h->print(out);
            out << endl;
        }

        
        

    }
    
    return 0;
}
