#include "RBTree.cpp"
using namespace std;

template <class T> void insertNodes(RBT<T>* &rbt, int n, ifstream &in){
    for (int i = 0; i < n; i++)
    {
        T key; in >> key;
        rbt->insertKey(key);
    }
}

#define N_TASK 3
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < N_TASK; t++)
    {
        string type; in >> type;
        int n; in >> n;
        if (type == "int")
        {
            RBT<int>* rbt = new RBT<int>();
            insertNodes(rbt, n, in);
            rbt->print(PREORDER, true, out);
            out << rbt->getBlackHeight() << endl;
        }
        else if(type == "double")
        {
            RBT<double>* rbt = new RBT<double>();
            insertNodes(rbt, n, in);
            out << rbt->getBlackHeight() << endl;
        }
    }
    
    return 0;
}
