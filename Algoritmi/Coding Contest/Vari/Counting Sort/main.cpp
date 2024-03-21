#include <iostream>
#include <fstream>
using namespace std;

#define NTASK 100
#define MAX 255

int findMin(int* arr, int n){
    int min = arr[0];
    for (int i = 1; i < n; i++)
    {
        if(arr[i] < min) min = arr[i];
    }
    return min;
}

int findMax(int* arr, int n){
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if(arr[i] > max) max = arr[i];
    }
    return max;
}

void CountingSort(int* arr, int n, ofstream &output){
    int min = findMin(arr, n);
    int max = findMax(arr, n);

    int* C = new int[max - min + 1];
    for(int i = 0; i <= max-min; i++) C[i] = 0;
    for(int i = 0; i < n; i++) C[arr[i] - min]++;
    for(int i = 1; i <= max-min; i++) C[i] += C[i-1];

    cout << "C : ";
    for(int i = 0; i < max-min + 1; i++) cout << C[i] << " ";
    cout << endl;

    int* B = new int[n + 1];
    for (int i = n-1; i >= 0; i--)
    {
        //cout << arr[i] - min << endl;
        B[C[arr[i] - min]] = arr[i];
        C[arr[i] - min]--;
    }

    for(int i = 0; i < n; i++) arr[i] = B[i+1];
    for(int i = 0; i <= max - min; i++) output << C[i] << " ";
    
}

int main(int argc, char const *argv[])
{
    ifstream input("input.txt");
    ofstream output("output.txt");
    int n;

    for (int i = 0; i < NTASK; i++)
    {
        input >> n;

        int *arr = new int[n];

        for (int j = 0; j < n; j++)
        {
            input >> arr[j];
            cout << arr[j] << " ";
        }
        cout << endl;

        CountingSort(arr, n, output);

        for (int j = 0; j < n; j++)
        {
            cout << arr[j] << " ";
            output << arr[j] << " ";
        }
        cout << endl;
        output << endl;
        
    }
    
    return 0;
}

