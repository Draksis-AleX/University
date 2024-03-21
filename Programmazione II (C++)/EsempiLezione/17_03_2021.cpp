//
//  17-02-2021.cpp
//  
//
//  Created by Alessandro Privitera on 17/03/21.
//

#include <iostream>

using namespace std;

/*
 
 PROBLEMA DEL RESTO
 Viene dato un insieme di n tagli di momente m[n]
 Dobbiamo restituire un resto pari a r>=0
 Trovare il minor numero di moenete da restituire per ottenere r
 
 */

#define INF UINT_MAX

unsigned int resto(unsigned int r, unsigned int *m, int n);

int main(){
    
    unsigned int m[] = {3,4,8,9};
    int n = 4;
    int r = 12;
    cout << resto(r, m, n) << endl;
    
}

unsigned int resto(unsigned int r, unsigned int *m, int n){
    
    if(r == 0) return 0;    //Caso base
    
    unsigned int rmin = INF;
    for (int i=0; i<n; i++) {
        //suppongo di dare una moneta m[i]
        if (m[i]<=r) {
            unsigned int rr = 1+resto(r-m[i],m,n);
            if(rr<rmin) rmin = rr;
        }
    }
    return rmin;
}

/*
 
 PROBLEMA DELLO ZAINO
 Abbiamo n elementi di vario peso e vario valore
 il peso è indicato da un vettore w di n elementi
 il valore è indicato da un vettore v di n elementi
 abbiamo a disposizione uno zaino di capacità pari a wz
 Dobbiamo portare a casa il maggior valore di oggetti possibili rispettando il peso dello zaino
 
 */

unsigned int knapsack(unsigned int wz, unsigned int *w, unsigned int *v, int n);
unsigned int knapsack(unsigned int wz, unsigned int *w, unsigned int *v, int n, bool *x);

int main(){
    
    unsigned int w[]={2,6,7,1,8};
    unsigned int v[]={4,8,1,3,5};
    bool x[] = {0,0,0,0,0};
    int n = 5;
    int wz = 9;
    cout << knapsack(wz,w,v,n) << endl;
    
}

unsigned int knapsack(unsigned int wz, unsigned int *w, unsigned int *v, int n){
    bool *x[] = {0,0,0,0,0};
    knapsack(wz,w,v,n,x);
}

unsigned int knapsack(unsigned int wz, unsigned int *w, unsigned int *v, int n, bool *x){
    
    unsigned int vmax = 0;
    for (int i=0; i<n; i++) {
        if (w[i]<=wz && x[i]==0) {
            x[i] = 1;   //l'elemento i-esimo lo metto nello zaino
            unsigned int guad = v[i] + knapsack(wz-w[i],w,v,n,x);
            x[i] = 0;   //tolgo l'elemento i-esimo per fare un altro tentativo
            if (guad>vmax) {
                vmax=guad;
            }
        }
    }
    return vmax;
}

unsigned int knapsack2(unsigned int wz, unsigned int *w, unsigned int *v, int n){
    
    if(n==0) return 0;
    
    if (w[0]<=wz) {
        //valuto se rubare o meno il primo elemento
        unsigned int value1 = knapsack2(wz, w+1, v+1, n-1) //guadagno nel caso in cui non rubo l'elemento
        unsigned int value2 = v[0] + knapsack2(wz-w[0],w+1,v+1,n-1) //guadagno nel caso in cui rubo l'elemento
        return max(value1,value2);
    }
    else{
        //non posso rubare il primo elemento quindi vado al successivo
        return knapsack2(wz,w+1,v+1,n-1)
    }
    
}

int fibonacci(int n){
    
    if(n<=2) return 1;
    
    return fibonacci(n-2) + fibonacci(n-1);
    
}

int main(){
    
    
    
}

/*
 Albero ricorsivo nel caso di n=6
 
                  (6)
        (4)                 (5)
    [2]     (3)      (3)           (4)
         [1]  [2]  [1]  [2]      [2]  (3)
                                    [1]  [2]
 
 Lo stesso problema viene risolto più volte dunque con valori di n grandi, l'algoritmo diventa lento.
 Per risolvere questo problema possiamo usare una ricorsione con memorizzazione
 */
