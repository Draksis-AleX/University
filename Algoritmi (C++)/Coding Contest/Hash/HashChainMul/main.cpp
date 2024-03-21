#include <iostream>
#include <fstream>
#include "HashTable.cpp"

template <class T> void InsertElements(MulChainedHashTable<T>* &table, int n, ifstream &in){

    for (int i = 0; i < n; i++)
    {
        T newKey; in >> newKey;
        table->insertKey(newKey);
    }

}

#define N_TASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < N_TASK; t++)
    {
        string type; in >> type;
        int nslot; in >> nslot;
        int n; in >> n;
        if(type == "int"){
            MulChainedHashTable<int>* table = new MulChainedHashTable<int>(nslot);
            InsertElements(table, n, in);
            table->printSlotSize(out);
            out << endl;
        }
        else if(type == "double"){
            MulChainedHashTable<double>* table = new MulChainedHashTable<double>(nslot);
            InsertElements(table, n, in);
            table->printSlotSize(out);
            out << endl;
        }
        if(type == "char"){
            MulChainedHashTable<char>* table = new MulChainedHashTable<char>(nslot);
            InsertElements(table, n, in);
            table->printSlotSize(out);
            out << endl;
        }
        if(type == "bool"){
            MulChainedHashTable<bool>* table = new MulChainedHashTable<bool>(nslot);
            InsertElements(table, n, in);
            table->printSlotSize(out);
            out << endl;
        }
    }
    
    return 0;
}
