#include "RBT.cpp"
using namespace std;

template <class T> void insertNodes(RBT<T>* &rbt, int n, ifstream &in){
    for (int i = 0; i < n; i++)
    {
        T newKey; in >> newKey;
        rbt->insertKey(newKey);
    }
}

#define NTASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    
    for (int t = 0; t < NTASK; t++)
    {
        string type; in >> type;
        int n; in >> n;
        string print_type; in >> print_type;
        if(type == "int"){
            RBT<int>* rbt = new RBT<int>();
            insertNodes(rbt, n, in);
            rbt->print(print_type, false, out);
            out << endl;
            delete rbt;
        }
        else if(type == "double"){
            RBT<double>* rbt = new RBT<double>();
            insertNodes(rbt, n, in);
            rbt->print(print_type, false, out);
            out << endl;
            delete rbt;
        }
    }
    
    return 0;
}
