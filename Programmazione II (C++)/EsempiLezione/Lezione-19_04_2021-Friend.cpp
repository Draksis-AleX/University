#include <iostream>

using namespace std;

/*
class A{
    int x,y;

    public:

    A(int _x, int _y) : x(_x), y(_y) {}

    friend void print(const A&a){
        cout << "\nX = " << a.x << " | Y = " << a.y;
    }
};

class B{
    string s;
    int a, b;

    public:

    B(string _s, int _a, int _b) : s(_s), a(_a), b(_b) {}

    void print(){
        cout << "\nS = " << s << " | a = " << a << " | b = " << b;
    }

    friend int somma(const B&b){
        return b.a + b.b;
    }
};

int main(){
    A a(1,2);
    print(a);

    B b("ciao", 3, 4);
    b.print();
    int c = somma(b);
    cout << "\nc = " << c;
}*/

class Punto{
    double x, y;

    public:

    Punto(){
        x=0;
        y=0;
    }

    Punto(double x, double y) : x(x), y(y) {}

    void print(){
        cout << "\nx = " << x << " | y = " << y;
    }

    friend ostream &operator <<(ostream &out, const Punto &p){
        out << "\nRedirezione - x = " << p.x << " | y = " << p.y;
        return out;
    } 

    friend istream &operator >>(istream &in, Punto &p){
        in >> p.x;
        in >> p.y;
        return in;
    }
};

int main(){
    Punto p1(4.5,6.3);
    p1.print();

    cout << p1 << endl;

    
    Punto p2;
    cin >> p2;
    cout << p2 <<endl;
}