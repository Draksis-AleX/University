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

        virtual int computeHashFunction(T key) = 0;

        list<T>* getTable(){return table;}
        int getSlotNumber(){return nSlot;}
        int getElemNumber(){return nElem;}

        ChainedHashTable<T>* insertKey(T _key){
            int index = computeHashFunction(_key);
            table[index].push_front(_key);
            nElem++;
            return this;
        }

        void searchKey(T _key, int &posOut, int &posIn){
            posOut = computeHashFunction(_key);
            typename list<T>::iterator i;
            for (i = table[posOut].begin(); i != table[posOut].end(); i++)
            {
                if(*i == _key){
                    posIn == (int) distance(table[posOut].begin(), i);
                    return;
                }
            }
            posIn = -1;
            return;
        }

        ChainedHashTable<T>* deleteKey(T _key){
            int posOut = -1;
            int posIn = -1;
            searchKey(_key, posOut, posIn);
            if(posIn == -1) return this;

            typename list<T>::iterator i = table[posOut].begin();
            advance(i, posIn);
            table[posOut].erase(i);
            nElem--;
            return this;
        }

        void printSlotSize(ofstream &out){
            for (int i = 0; i < nSlot; i++)
            {
                out << table[i].size() << " ";
            }
        }
};

template <class T> class MulChainedHashTable : public ChainedHashTable<T>{
    private: 
        double c;
        int computeHashFunction(T _key){
            double y = _key * c;
            double a = y - (int)y;
            int h = (int)(a * this->getSlotNumber());
            return h;
        }
    public:
        MulChainedHashTable(int _nslot) : ChainedHashTable<T>(_nslot){
            c = 0.61803;
        }
};