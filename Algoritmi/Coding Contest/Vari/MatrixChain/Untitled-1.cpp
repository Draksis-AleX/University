#include <climits>

int MatrixChainOrder(int n, int* d){
    int** M = new int*[n+1];
    for(int i = 0; i < n+1; i++) M[i] = new int[n+1];
    int** S = new int*[n+1];
    for(int i = 0; i < n+1; i++) S[i] = new int[n+1];

    for(int i = 0; i < n+1; i++) M[i][i] = 0;

    for(int dlt = 1; dlt < n; dlt++){
        for(int i = 1; i < n+1-dlt; i++){
            int j = i + dlt;
            M[i][j] = INT_MAX;
            for(int k = i; k < j; k++){
                int q = M[i][k] + M[k+1][j] + d[i-1]*d[k]*d[j];
                if(q < M[i][j]){
                    M[i][j] = q;
                    S[i][j] = k;
                }
            }
        }
    }
    return M[1][n];
}