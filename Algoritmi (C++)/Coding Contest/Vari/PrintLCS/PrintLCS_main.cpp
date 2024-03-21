#include "LCS.cpp"
using namespace std;

#define N_TASK 100
int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    for (int t = 0; t < N_TASK; t++)
    {
        int n; in >> n;
        int m; in >> m;
        string x; in >> x;
        string y; in >> y;

        cout << "Comparing:\n- X : " << x << " [" << n << "]\n- Y : " << y << " [" << m << "]\n";
        char** print_matr;
        int lcs_len = LCS_Lenght(x, y, n, m, print_matr);
        cout << "[ " << lcs_len << " ] : ";
        print_LCS(print_matr, x, n, m, out);
        out << endl;
        cout << endl << endl;
    }
    
    return 0;
}
