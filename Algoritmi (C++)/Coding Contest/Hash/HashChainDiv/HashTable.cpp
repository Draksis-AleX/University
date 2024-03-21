#include <iostream>
#include <fstream>
#include <list>
using namespace std;

template <class T> class ChainedHashTable{
    private:
        int nSlot;
        int nElem;
        list<T>* table;

    public:

        ChainedHashTable(int _nSlot) : nSlot(_nSlot) {
            nElem = 0;
            table = new list<T>[nSlot];
        }

        int getSlotNumber(){return nSlot;}

        virtual int hash(T _key) = 0;

        ChainedHashTable<T>* insertKey(T _key){
            int index = hash(_key);
            table[index].push_front(_key);
            nElem++;
            return;
        }

};

template <class T> class DivChainedHashTable : public ChainedHashTable<T>{
    private:
        int hash(T _key){return _key % getSlotNumber();}
    public:
        DivChainedHashTable(int _nSlot) : ChainedHashTable<T>(_nslot) {}
};