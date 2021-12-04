#include <NTL/ZZ.h>
#include <iostream>
#include "librerias.h"
#include <cstdlib>

using namespace std;
using namespace NTL;

void RSA(string mensaje){
    string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890[]#";

    ZZ p = ZZ(0), q = ZZ(0);
    GK_searchPQ(p,q);

    ZZ phi = (p - ZZ(1))*(q - ZZ(1));

    ZZ e = GK_searchE(phi);
    ZZ n = (p * q);
    ZZ d = inversa(e,phi);

    cout << "mensaje: " << mensaje << endl;
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    cout << "e = " << e << endl;
    cout << "n = " << n << endl;

    //CIFRADO
    string mensaje_cifrado = cypher(mensaje_cifrado,e,n,mensaje,alfabeto);
    cout << "El mensaje cifrado es: " << mensaje_cifrado << endl;

    string rubrica = cypher_rubrica(d,n,alfabeto);
    cout << "La rubrica es: " << rubrica << endl;

    string firma = cypher_firma(rubrica,e,n,alfabeto);
    cout << "La firma es: " << firma << endl;

    cout << endl;

    //DESCIFRADO
    string mensaje_descifrado = decypher(mensaje_cifrado,mensaje_descifrado,n,d,alfabeto);
    cout << "El mensaje descifrado es: " << mensaje_descifrado << endl;

    string firma_to_rubrica = decypher_firma(d,n,firma);
    cout << "La rubrica es: " << firma_to_rubrica << endl;

    string firma_descifrada = decypher_rubrica(firma_descifrada,firma_to_rubrica,e,n,alfabeto);
    cout << "La firma descifrada es: " << firma_descifrada << endl;
}

int main(){
    string mensaje = "Hola mundo";
    RSA (mensaje);
}
