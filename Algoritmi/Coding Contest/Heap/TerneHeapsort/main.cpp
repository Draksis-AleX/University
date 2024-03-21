#include "Heap.cpp"
#include <fstream>
using namespace std;

#define NTASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < NTASK; t++)
    {
        string type; in >> type;
        int n; in >> n;
        cout << t+1 << ") TYPE = " << type << ", N = " << n << " ----------\n\n";

        if (type == "int")
        {
            Terna<int>* A = new Terna<int>[n];
            for (int i = 0; i < n; i++)
            {   
                char tmp; in >> tmp;
                in >> A[i].x; //in >> tmp;
                in >> A[i].y; //in >> tmp;
                in >> A[i].z; in >> tmp;
            }

            cout << "A = [ ";
            for(int i = 0; i < n; i++) cout << "(" << A[i].x << ", " << A[i].y << ", " << A[i].z <<") ";
            cout << " ]\n\n";

            cout << "Ordinamento...\n\n";

            MaxHeap< Terna<int> >* h = new MaxHeap< Terna<int> >(n);
            h->heapsort(A, n);

            cout << "A = [ ";
            for(int i = 0; i < n; i++) cout << "(" << A[i].x << ", " << A[i].y << ", " << A[i].z <<") ";
            cout << " ]\n\n";

            out << h->getHeapifyCount() << " ";
            for(int i = 0; i < n; i++) out << "(" << A[i].x << " " << A[i].y << " " << A[i].z <<") ";
            out << endl;
            
            delete h;
            delete[] A;
        }
        else if (type == "double")
        {
            Terna<double>* A = new Terna<double>[n];
            for (int i = 0; i < n; i++)
            {   
                char tmp; in >> tmp;
                in >> A[i].x; //in >> tmp;
                in >> A[i].y; //in >> tmp;
                in >> A[i].z; in >> tmp;
            }

            cout << "A = [ ";
            for(int i = 0; i < n; i++) cout << "(" << A[i].x << ", " << A[i].y << ", " << A[i].z <<") ";
            cout << " ]\n\n";

            cout << "Ordinamento...\n\n";

            MaxHeap< Terna<double> >* h = new MaxHeap< Terna<double> >(n);
            h->heapsort(A, n);

            cout << "A = [ ";
            for(int i = 0; i < n; i++) cout << "(" << A[i].x << ", " << A[i].y << ", " << A[i].z <<") ";
            cout << " ]\n\n";

            out << h->getHeapifyCount() << " ";
            for(int i = 0; i < n; i++) out << "(" << A[i].x << " " << A[i].y << " " << A[i].z <<") ";
            out << endl;
            
            delete h;
            delete[] A;
        }
        else if (type == "bool")
        {
            Terna<bool>* A = new Terna<bool>[n];
            for (int i = 0; i < n; i++)
            {   
                char tmp; in >> tmp;
                in >> A[i].x; //in >> tmp;
                in >> A[i].y; //in >> tmp;
                in >> A[i].z; in >> tmp;
            }

            cout << "A = [ ";
            for(int i = 0; i < n; i++) cout << "(" << A[i].x << ", " << A[i].y << ", " << A[i].z <<") ";
            cout << " ]\n\n";

            cout << "Ordinamento...\n\n";

            MaxHeap< Terna<bool> >* h = new MaxHeap< Terna<bool> >(n);
            h->heapsort(A, n);

            cout << "A = [ ";
            for(int i = 0; i < n; i++) cout << "(" << A[i].x << ", " << A[i].y << ", " << A[i].z <<") ";
            cout << " ]\n\n";

            out << h->getHeapifyCount() << " ";
            for(int i = 0; i < n; i++) out << "(" << A[i].x << " " << A[i].y << " " << A[i].z <<") ";
            out << endl;
            
            delete h;
            delete[] A;
        }
        else if (type == "char")
        {
            Terna<char>* A = new Terna<char>[n];
            for (int i = 0; i < n; i++)
            {   
                char tmp; in >> tmp;
                in >> A[i].x; //in >> tmp;
                in >> A[i].y; //in >> tmp;
                in >> A[i].z; in >> tmp;
            }

            cout << "A = [ ";
            for(int i = 0; i < n; i++) cout << "(" << A[i].x << ", " << A[i].y << ", " << A[i].z <<") ";
            cout << " ]\n\n";

            cout << "Ordinamento...\n\n";

            MaxHeap< Terna<char> >* h = new MaxHeap< Terna<char> >(n);
            h->heapsort(A, n);

            cout << "A = [ ";
            for(int i = 0; i < n; i++) cout << "(" << A[i].x << ", " << A[i].y << ", " << A[i].z <<") ";
            cout << " ]\n\n";

            out << h->getHeapifyCount() << " ";
            for(int i = 0; i < n; i++) out << "(" << A[i].x << " " << A[i].y << " " << A[i].z <<") ";
            out << endl;
            
            delete h;
            delete[] A;
        }
        
    }
    
    return 0;
}
