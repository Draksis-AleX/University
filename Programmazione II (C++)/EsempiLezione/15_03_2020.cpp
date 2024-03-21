

int fattoriale(int n){

    if(n==1) return n;  //caso base
    //n! = (n-1)! * n
    return fattoriale(n-1)*n; //caso ricorsivo

}

int mul(int x, int y){

    if(y==0) return y;  //caso base
    //x*y = x*(y-1) + x
    return mul(x,y-1) + x;  //caso ricorsivo                                                                                                                                                                                                                                                                                                                                                                                                                                                     

}

int potenza(int x, int y){

    if(y==0) return 1;  //caso base
    //x^y = x^(y-1) * x
    return potenza(x,y-1) * x;  //caso ricorsivo

}

int potenza2(int x, int y){

    if(y==0) return 1;  //caso base 0
    if(y==1) return x;  //caso base 1
    //x^y = x^(y/2) * x^(y-y/2)
    return potenza(x,y/2) * potenza(x,y-(y/2))  //caso ricorsivo

}

//Problema della sequenza di fibonacci
// 1 1 2 3 5 8 13 21

//Problema: trovare l'ennesimo numero della sequenza

int fibonacci(int n){

    if(n<=2) return 1;  //caso base 
    return fibonacci(n-2) + fibonacci(n-1); //caso ricorsivo

}

//Abbiamo un problema con n grandi poichè il problema così risolto e intrinsecamente difficile

//Ricerca di un elemento in un array ritorna presente/non presente

int search(int *v, int n, int x){

    if(n==0) return 0;  //caso base array vuoto
    if(v[0]==x) return 1;   //caso base x primo elemento
    return search(v+1, n-1, x); //caso ricorsivo

}

int search2(int *v, int n, int x){

    if(n==0) return 0;  //caso base array vuoto
    if(n==1) return return v[0]==x; //caso base array di un elemento

    int m = n/2;    //divido l'array a meta'
    //v[0...m-1] + v[m...n-1]
    return search2(v, m, x) || search2(v+m, n-m, x); //caso ricorsivo

}

//Ricerca di un elemento in un array ritorna posizione

int search(int *v, int n, int x){

    if(n==0) return 1;  //caso base array vuoto
    if(v[0]==x) return 0;   //caso base x primo elemento
    return search(v+1, n-1, x) + 1; //caso ricorsivo

}

//Supponiamo ora che l'array sia ordinato

//Ricerca binaria o dicotomica

//restituisce un booleano
int binary_search(int *v, int n, int x){

    if(n==0) return 0;
    if(n==1) return v[x]==x;

    int m = n/2;
    if(v[m] < x)
        return binary_search(v+m, n-m, x);
    else
        return binary_search(v, m, x);

}

//verifica di una stringa palindroma

int palindroma(char *s, int n){

    if(n<=1) return 1;  //caso base 
    
    return (s[0]==s[n-1]) && palindroma(s+1,n-2);   //caso ricorsivo

}

//Ordinamento di un vettore tramite selectionsort

/*
Si prende il massimo dell'array e si mette alla fine, poi si reitera non considerando più
l'ultimo elemento
*/

int pos_max(int *v, int n)
    int pos = 0;
    for (int i = 0; i < n; i++)
    {
        if(v[i] > v[pos]) pos = i;
    }
    return pos; 
}

void swap(int *v, int i, int j){
    int t = v[i];
    v[i] = v[j];
    v[j] = v[i];
}

void selection_sort(char *v, int n){

    if(n<=1) return;

    int p = pos_max(v, n);
    swap(v, p, n-1);
    selection_sort(v, n-1)

}

//Ordinamento di un vettore tramite insertion sort

/*
Prendo un elemento alla volta e lo inserisco a sinistra
*/

//versione iterativa

void insertion_sort(int *v, int n){

    for (size_t i = 1; i < count; i++)
    {
        int j = i;
        while (j > 0 && v[j] < v[j-1])
        {
            swap(v, j, j-1);
            j--;
        }   
    }
    
}

//Versione ricorsiva

void insertion_sort(int *v, int n){

    if(n <= 1) return;

    insertion_sort(v, n-1);
    int j=n-1;
    while (j > 0 && v[j] < v[j-1])
    {
        swap(v, j, j-1);
        j--;
    }  
    
}

//Problema delle torri di Hanoi

/*
Ci sono tre pali e dei dischi inseriti nei pali, i dischi hanno diamtro di grandezza variabile
*/

//  1
//  2
//  3
//  --  --  --
//  A   B   C

/*
L'obiettivo è spostare i dischi dal palo A al palo C,
ma non posso mettere un disco più grande sopra uno più piccolo
*/

//Realizzo l'algoritmo su n dischi

//  1
//  ...
//  n-1
//  --  --  --
//  A   B   C

void Hanoi(int n, char a, char c, char b){

    static int num = 1;
    if(n==1){   //caso base
        cout << num++ << " :Sposta un disco da" << a << " a " << c << endl;
        return;
    }

    Hanoi(n-1, a, b, c);
    Hanoi(1, a, c, b);
    Hanoi(n-1, b, c, a);

}

int main(){

    char pa = 'A';
    char pb = 'B';
    char pc = 'C';
    Hanoi(3, pa, pc, pb);

}

//Calcolo delle permutazioni di una stringa

void print(char *s, int n){
    for (int i = 0; i < n; i++)
    {
        cout << s[i] << " ";
    }
    cout << endl;   
}

void swap(char *s, int i, int j){
    char t = s[i];
    s[i] = s[j];
    s[j] = t;
}

void permutazioni(char *s, int i, int n){
    
    static int lenght = n;
    if (n==0){
        print(s-lenght, lenght);
        return;
    }
    for (int j = 0; j < n; j++)
    {
        swap(s, 0, j);  //fisso s[i] con s[j]
        permutazioni(s+1, n-1);
        swap(s, j, 0);  //rimetto s[j] al suo posto
    }
    
}
