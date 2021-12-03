#include <iostream>
using namespace std;

int modulo(int a, int b){
    int r = a - ((a/b)*b);
    if (r < 0){
        return r += b;
    }
    return r;
}

int euclides(int a, int b){
  while(b>0){
  int r=a%b;
  a=b;
  b=r;
  }
  return a;
}

int x_1 = 1, x_2 = 0;
int y_1 = 0, y_2 = 1;

int euclides_extendido(int a, int b){
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
                
        return euclides_extendido(a,b);
    }

  return x_2; 
}

int inversa(int a, int b){
  int inv = euclides_extendido(a,b);
  if(euclides(a,b) == 1){
    if (inv < 0){
        return(modulo(inv,b));
    }
    return inv;
  }
}

int pow(int a,int b){
    int res;
    int n;
    n=0;
    res =1;
    while (n != b){
        res *= a;
        n++;
    }
    return res;
}

int char_to_int(char text){
    string alfabeto = "abcdefghijklmnopqrstuvwxyz";

    for(int i = 0; i <= alfabeto.size(); i++){
        if (text == alfabeto[i]){
            return i;
        }
    }      
}

char int_to_char(int i){
    string alfabeto = "abcdefghijklmnopqrstuvwxyz";
    if(i >= alfabeto.size()){
        int mod = modulo(i, alfabeto.size());
        return alfabeto[mod];
    }
    else{
        return alfabeto[i];
    }
}

void RSA(int p, int q){
    int n = p * q;
    cout << "n = " << n << endl;

    int phi = (p - 1)*(q - 1);
    cout << "phi = " << phi << endl;

    int e;
    while (true){
        cout << "ingrese e:" ;
        cin >> e;
        int gcd = euclides(e, phi);
        if (gcd == 1){
            break;}
        cout << "gcd(" << e << ", " << phi << ") = " << gcd << endl;
    }

    int d = inversa(e, phi);
    cout << "Alice publica = {" << e << "," << n << "}" << endl;
    cout << "Alice secreta = {d, n}" << endl;

    char mensaje;
    cout << "Bob quiere enviar un mensaje: ";
    cin >> mensaje;

    int m = char_to_int(mensaje);
    cout << "m = " << m << endl;

    int c = pow(m,e) % n;
    cout << "Bob cifra el mensaje usando la clave publica de Alice: {" << e << ", " << n << "}" << endl;
    cout << "Mensaje cifrado:" << int_to_char(c) << endl;

    int md = pow(c,d) % n;
    cout << "Alice recupera el mensaje usando su clave: {" << d << ", " << n << "}" << endl;
    cout << "Mensaje recuperado:" << int_to_char(md) << endl;
}

int main(){
    RSA(3, 11);
}