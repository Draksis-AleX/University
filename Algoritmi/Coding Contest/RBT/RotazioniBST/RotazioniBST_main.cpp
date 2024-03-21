#include "BST.cpp"
using namespace std;

template <class T> void executeOperation(BST<T>* &bst, int n, ifstream &in, string type){
    for (int i = 0; i < n; i++)
    {
        string op; in >> op;
        string op_type = op.substr(0, op.find(":"));  
        T op_num;
        if(type == "int") op_num = stoi(op.substr(op.find(":")+1, op.size()));
        else if(type == "double") op_num = stod(op.substr(op.find(":")+1, op.size()));
        cout << "OP: " << op_type << "(" << op_num << ") ";
        if(op_type == "ins") bst->addNode(op_num);
        else bst->deleteNode(op_num);
    }
}

template <class T> void executeRotation(BST<T>* &bst, int m, ifstream &in, string type){
    for (int i = 0; i < m; i++)
    {
        string op; in >> op;
        string op_type = op.substr(0, op.find(":"));
        T op_num;
        if(type == "int") op_num = stoi(op.substr(op.find(":")+1, op.size()));
        else if(type == "double") op_num = stod(op.substr(op.find(":")+1, op.size()));
        cout << "ROT: " << op_type << "(" << op_num << ") ";
        if(op_type == "left") bst->rotateLeft(op_num);
        else bst->rotateRight(op_num);
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
        int nop; in >> nop;
        int nrot; in >> nrot;
        string printOrder; in >> printOrder;

        cout << t+1 << ") New Task : Type = " << type << ", N = " << nop << ", M = " << nrot << " ";

        if(type == "int"){
            BST<int>* bst = new BST<int>();
            executeOperation(bst, nop, in, type);
            executeRotation(bst, nrot, in, type);
            bst->print(printOrder, out);
            out << endl;
            delete bst;
        }
        else if(type == "double"){
            BST<double>* bst = new BST<double>();
            executeOperation(bst, nop, in, type);
            executeRotation(bst, nrot, in, type);
            bst->print(printOrder, out);
            out << endl;
            delete bst;
        }
        cout << endl << endl;
    }
    
    return 0;
}
