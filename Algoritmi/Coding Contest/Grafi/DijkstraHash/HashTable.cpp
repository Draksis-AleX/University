#include <iostream>
#include <climits>
using namespace std;

template <class T> class OpenHashTable{
    private:
        T* table;
        int nslot;
        int nelem;

        int hash(T _key, int _i){return ((int)_key + (3*_i)) % nslot;}

    public:
        OpenHashTable(int _nslot) : nslot(_nslot) {
            nelem = 0;
            table = new T[nslot];
            for (int i = 0; i < nslot; i++)
            {
                table[i] = INT_MAX;
            }
            
        }

        OpenHashTable<T>* insert(T _key){
            int i = 0;
            do
            {
                int j = hash(_key, i);
                if(table[j] == INT_MAX){
                    nelem++;
                    table[j] = _key;
                    return this;
                }
                else i++;
            } while (i < nslot);
            return this;
        }

        int search(T _key){
            int i = 0;
            do
            {
                int j = hash(_key, i);
                if(table[j] == _key)
                    return j;
                else i++;
            } while (i < nslot);
            return -1;
        }

        void print(){
            cout << "[ ";
            for (int i = 0; i < nelem; i++)
            {
                cout << table[i] << " ";
            }
            cout << "]";
        }
};