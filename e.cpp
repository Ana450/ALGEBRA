#include <iostream>
using namespace std;

//auxiliares
int x_1 = 1, x_2 = 0;
int y_1 = 0, y_2 = 1;

int mcd(int a, int b){
    //mcd
    int q = a / b;
    int r = a - (q * b);//residuo
    
    int x = x_1 - q * x_2;
    int y = y_1 - q * y_2;

    while(r > 0){      
        a = b;
        b = r;
        
        x_1 = x_2;
        x_2 = x;
                
        y_1 = y_2;
        y_2 = y;
                
        return mcd(a,b);
    }
  
  cout << "mcd = " << b << endl;
  cout << "q = " << q << endl;
  cout << "x = " << x_2 << endl;
  cout << "y = " <<y_2 << endl;
  
}

int main(){
    int a;
    cout << "ingrese a";
    cin >> a;
    int b;
    cout << "ingrese b";
    cin >> b;
    
    mcd(a,b);
}