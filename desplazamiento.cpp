#include <iostream>
#include <string>
using namespace std;

int modulo (int a, int n){
    int  q = a / n;
    int r = a - (q * n);
    
    if (r < 0){
        q--;
        r = a - (q * n);
    }          
    return r;
}

class cesar{
    string alfabeto = "abcdefghijklmnopqrstuvwxyz";
    int k = 0;
    
    string text;
    int clave;
    string nuevo;

    public:
        cesar(int clav){
            clave = clav;
        }

        string cifrado(string text){
            for(int i = 0; i < text.size(); i++){
                for(int j = 0; j < alfabeto.size(); j++){
                    if (text[i] == alfabeto[j]){
                        k = j + clave;
                        if (k >= alfabeto.size()){
                            k = modulo(k,alfabeto.size());
                        }
                        nuevo.push_back(alfabeto[k]);
                        k=0;  
                    }
                }      
            }
            cout << nuevo;
            return nuevo;
        }

        string descifrado(string nuevo){
            string nuevo_2;
            for(int i = 0; i < nuevo.size(); i++){
                for(int j = 0; j < alfabeto.size(); j++){
                    if (nuevo[i] == alfabeto[j]){
                        k = j - clave;
                        if (k < 0){
                            k = modulo(k,alfabeto.size());
                        }
                        nuevo_2.push_back(alfabeto[k]);
                        k = 0;  
                    }
                }      
            }
            cout << nuevo_2;
        }
};

int main(){
    string a = "xultpaajcxitltlxaarpjhtiwtgxktghidhipxciwtvgtpilpitghlxiwiwtxgqadds";
    cout << endl;

    int clave = 11;
    cout << endl;

    cesar x(clave);

    string c = x.cifrado(a);
    cout << endl;
    x.descifrado(c);
}