#include <iostream>
using namespace std;

int modulo(int a, int b){
    int r = a - ((a/b)*b);
    if (r < 0){
        return r += b;
    }
    return r;
}

// (a ^ b) % m
int expo_mod(int a, int b, int m)
{
    int res = 1;      
    a = modulo(a,m);  
    while (b > 0)
    {
        if (b % 2)
            res = modulo((res*a), m);

        b =  b / 2;
        a = modulo((a * a), m);
    }
    return res;
}

bool MILLER_RABIN(int n, int s)
{
    int a = rand() % (n-4) + 2;
    int x = expo_mod(a, n, s);
 
    if (x == 1  || x == s-1)
       return true;
 
    while (n != s-1)
    {
        x = (x * x) % s;
        n *= 2;
 
        if (x == 1)      
            return false;

        if (x == s-1)    
            return true;
    }
 
    return false;
}
 
bool primo(int n)
{   
    //caso base 1
    if (n <= 1)  
        return false;

    //caso base 2
    if (n <= 3) 
        return true;
 
    int d = n - 1;
    while (d % 2 == 0)
        d = d / 2;
 
    for (int i = 0; i < 1; i++)
    {
        if (!MILLER_RABIN(d, n))
            return false;
    }
    return true;
}
 
int main()
{
    for (int n = 999; n <= 9999; n++)
    {
       if (primo(n))
          cout << n << " ";
    }

}