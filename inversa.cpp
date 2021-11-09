#include<iostream>
using namespace std;

int modulo(int a, int b){
    int r = a - ((a/b)*b);
    if (r < 0){
        return r += b;
    }
    return r;
}

int euclides_extendido(int a, int b){
    int q, r = 1;
    int r1, r2, s1, s2, t1, t2;

    r1 = a; r2 = b;
    s1 = 1; s2 = 0;
    t1 = 0; t2 = 1;

    while (r != 0){
        q = r1/r2;
        r = r1 - (q*r2);

        if (r != 0){
            r1 = r2;
            r2 = r;
        }

        int s = s1 - q * s2;
        s1 = s2;
        s2 = s;

        int t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }

    return s1;
}

int inversa (int a, int b){
    a = euclides_extendido(a,b);

    if (a < 0){
        a = modulo(a,b);
    }

    return a;
}

int main(){
    int a;
    cout << "ingrese a";
    cin >> a;
    int n;
    cout << "ingrese n";
    cin >> n;
    cout << "x = " << inversa(a,n);
}