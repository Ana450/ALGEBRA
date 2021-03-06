#include <NTL/ZZ.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

//Librerias para Random
#include <vector>
#include "string"
#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <sys/time.h>
#include <chrono>
//#include <NTL/vector.h>

using std::vector;
using std::cout;
using std::endl;
using NTL::conv;
using NTL::RandomBits_ZZ;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::ostringstream;
using std::istringstream;

using namespace std;
using namespace NTL;

ZZ modulo(ZZ a, ZZ b){
    ZZ r = a - ((a/b)*b);
    if (r < 0){
        return r += b;
    }
    return r;
}

ZZ pow2(ZZ a,ZZ b){
    ZZ res;
    ZZ n;
    n = 0;
    res = 1;
    while (n != b){
        res *= a;
        n++;
    }
    return res;
}

ZZ k_ary(ZZ base, ZZ exp, ZZ N){
    ZZ t = ZZ(1);
    while (exp > ZZ(0)){
        if (modulo(exp, ZZ(2)) != ZZ(0))
            t = modulo((t * base) ,N);

        base = modulo((base * base), N);
        exp /= ZZ(2);
    }
    return modulo(t, N);
}

ZZ euclides(ZZ num1, ZZ num2){
    ZZ q, r = ZZ(1);
    if (num1 < num2){
        ZZ temp = num1;
        num1 = num2;
        num2 = temp;
    }
    while (r != 0){
        q = num1/num2;
        r = num1 - (q*num2);

        if (r != 0){
            num1 = num2;
            num2 = r;
        }
    }
    ZZ mcd = num2;
    return mcd;
}

ZZ euclides_extendido(ZZ num_1, ZZ num_2){
    ZZ q, r = ZZ(1);
    ZZ r1, r2, s1, s2, t1, t2, s, t;

    r1 = num_1; r2 = num_2;
    s1 = 1; s2 = 0;
    t1 = 0; t2 = 1;

    while (r != 0){
        q = r1/r2;
        r = r1 - (q*r2);

        if (r != 0){
            r1 = r2;
            r2 = r;
        }

        s = s1 - q * s2;
        s1 = s2;
        s2 = s;

        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }

    return s1;
}

ZZ inversa (ZZ clave_a, ZZ longitud){
    clave_a = euclides_extendido(clave_a,longitud);

    if (clave_a < 0){
        clave_a = modulo(clave_a,longitud);
    }

    return clave_a;
}

string int_a_str(ZZ conversion){
    ostringstream convertido;
    convertido << conversion;
    return convertido.str();
}

ZZ pot(ZZ base, ZZ exponente){
    if(exponente == 0)
        return ZZ(1);
    ZZ x = pot(base,exponente/2);
    if (exponente % 2 == 0)
        return x*x;
    return x*x*base;
}

ZZ string_a_int(string conversion){
    istringstream convertido(conversion);
    ZZ entero;
    convertido >> entero;
    return entero;
}

ZZ newTime(){
    ZZ x;
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    x = ZZ(millisec_since_epoch);

    x = string_a_int(int_a_str(x).substr(6,9));

    x = pot(x+5,ZZ(3));
    return x;
}

ZZ get_semilla(){

    ZZ x,y;
    POINT cursor;
    GetCursorPos(&cursor);
    x = ZZ(cursor.x);
    y = ZZ(cursor.y);

    ZZ tim;
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    tim = ZZ(millisec_since_epoch);
    tim = string_a_int(int_a_str(tim).substr(6,9));
    tim = pot(tim+5,ZZ(3));

    return x*y*tim;
}

ZZ middleSquareNumber(ZZ number, ZZ bits) {
    ZZ intervalo_mayor = pot(ZZ(2),bits)-1;
    ZZ intervalo_menor = pot(ZZ(2),bits)/2;

    ZZ sqn = number * number, next_number = number;

    while(next_number < intervalo_mayor)    {
        int tam0  = int_a_str(next_number).length();
        ZZ tam1 = conv<ZZ>(tam0);
        ZZ t (tam1 / ZZ(2));
        ZZ limite = pot(ZZ(10),t);
        sqn =  next_number / limite;
        next_number = sqn * sqn * sqn;
    }

    next_number = modulo(next_number, intervalo_mayor);

    if(next_number < intervalo_menor){
        next_number += intervalo_menor;
    }
    return next_number;
}

ZZ middleSquareNumberRan(ZZ number, ZZ intervalo_mayor, ZZ intervalo_menor) {

    ZZ sqn = number * number, next_number = number;
    while(next_number < intervalo_mayor){
        int tam1  = int_a_str(next_number).length();
        int t = (tam1 / 2);
        ZZ limite = pot(ZZ(10),conv<ZZ>(t));
        sqn =  next_number / limite;
        next_number = sqn * sqn * sqn;

    }
    next_number = modulo(next_number, intervalo_mayor);
    if(next_number < intervalo_menor){
        next_number += intervalo_menor;
    }

    return next_number;
}

vector<ZZ>fact_2(ZZ n){
    vector<ZZ>facts;
    ZZ a (0);
    while(modulo(n,ZZ(2))==0){
        n = n/2;
        a++;
    }
    facts.push_back(a);
    facts.push_back(n);
    return facts;
}

bool Miller(ZZ n, ZZ k){
    bool continueFor = false;
    ZZ r(0);
    ZZ d(1);
    vector<ZZ>facts = fact_2(ZZ(n-1));
    r = facts[0];
    d = facts[1];

    ZZ a,x;
    for(int i = 0; i < k; i++){
        ZZ aux (newTime());
        a = middleSquareNumberRan(aux,n-2,ZZ(2));
        x = k_ary(a,d,n);

        if(x == 1 || x == n - 1)
            continue;
        for(int i = 0; i < r-1; i++){
            x = modulo(x*x,n);
            if(x == n-1)
                continueFor=true;
            break;
        }
        if(continueFor == true)continue;
        return true;
    }
    return false;
}

int NumberOfDigits(int num){
    int contador = 1;
    while(num/10>0){
        num=num/10;
        contador++;
    }
    return contador;
}

ZZ NumberOfDigitsZZ(ZZ num){
    ZZ contador = ZZ(1);
    while(num/10>0){
        num=num/10;
        contador++;
    }
    return contador;
}

int NumberOfDigitsRint(ZZ num){
    stringstream buffer;
    buffer << num;
    string number = buffer.str();
    return number.length();
}

int ZZ_to_int(ZZ num){
    stringstream buffer;
    buffer << num;
    string number = buffer.str();
    return atoi(number.c_str());
}

ZZ String_To_ZZ(string str){
    ZZ result(NTL::INIT_VAL, str.c_str());
    return result;
}

string IncreaseZeros(ZZ pos, ZZ total_number_digits, string mensaje_num){
    ZZ contador = NumberOfDigitsZZ(pos);
    string num_alf =  int_a_str(pos);
    while ( contador < total_number_digits)    {
        mensaje_num.append("0");
        contador++;
    }
    mensaje_num.append(num_alf);

    return mensaje_num;
}

string ObtainMessageInNumbers(string mensaje, string alfabeto){
    string mensaje_num;
    int total_number_digits = NumberOfDigits( alfabeto.length() );

    for (int i = 0; i < mensaje.length(); i++){
        for (int pos = 0; pos < alfabeto.length(); pos++){
            if ( mensaje[i] == alfabeto[pos]){
                mensaje_num = IncreaseZeros(ZZ(pos),ZZ(total_number_digits),mensaje_num);
                break;
            }
        }
    }
    return mensaje_num;
}

string SeparateIntoBlocks( int indice, int k, string mensaje_num){
    vector <string> matriz;
    int inicio = 0;
    for (int i = 0; i < (mensaje_num.length() / k); i++){
        matriz.push_back(mensaje_num.substr(inicio,k));
        inicio = inicio + k;
    }

    return matriz.at(indice);
}

string ObtainMessageInLetters( int pos, string alfabeto){
    string mensaje_num;

    for (int i = 0; i < alfabeto.length(); i++){
        if ( pos == i){
            mensaje_num = alfabeto[i];
            break;
        }
    }
    return mensaje_num;
}

string cypher(string mensaje_cifrado, ZZ e_R, ZZ n_R, string mensaje, string alfabeto){
    string s_fin_temp;
    bool flag;
    do{//para completar mas caracteres
        ZZ verificadorAddCaracteres = mensaje.length() * NumberOfDigitsZZ( ZZ(alfabeto.length()));

        if ( modulo(verificadorAddCaracteres, NumberOfDigitsZZ(n_R)-1) == 0 ){
            flag = false;
        }
        else{
            mensaje.append( "#" );// se inserta al final
            flag = true;
        }
    } while (flag);

    s_fin_temp = ObtainMessageInNumbers(mensaje,alfabeto); // CIFRADO: mensaje en numeros completo

    ZZ i_fin_temp = NumberOfDigitsZZ(n_R)-1;
    ZZ i_fin_temp2 = ZZ(s_fin_temp.length()) / i_fin_temp;

    for (int i = 0; i < i_fin_temp2; ++i){
        int k = NumberOfDigitsRint(n_R);
        string s_num_of_matriz = SeparateIntoBlocks(i, k-1,s_fin_temp);
        ZZ i_num_of_matriz = String_To_ZZ(s_num_of_matriz);

        ZZ i_aux;
        i_aux = k_ary(i_num_of_matriz,e_R,n_R);

        ZZ total_number_digits = NumberOfDigitsZZ(n_R); //hacer que sea de tama?o N
        mensaje_cifrado = IncreaseZeros(i_aux, total_number_digits,mensaje_cifrado);
    }
    return mensaje_cifrado;
}

string cypher_rubrica(ZZ d_E, ZZ n_E, string alfabeto){
    string datos = "Ana Concha";

    //sumar "#" a la rubrica
    bool flag2;
    do {//para completar mas caracteres
        ZZ verificadorAddCaracteres = datos.length() * NumberOfDigitsZZ( ZZ(alfabeto.length()));

        if ( modulo(verificadorAddCaracteres, NumberOfDigitsZZ(n_E)-ZZ(1)) == ZZ(0) ){//se le quita la resta a len N -1, porque en firma digital no lo especifica o no
            flag2 = false;
        }
        else{
            datos.append( "#" ); //"Aumentamos caracter #"
            flag2 = true;
        }
    } while (flag2);

    string datos_fin_temp = ObtainMessageInNumbers(datos,alfabeto); //CIFRADO: mensaje en numeros completo
    ZZ rubrica_temp = NumberOfDigitsZZ(n_E) - ZZ(1);
    ZZ rubrica_temp2 = ZZ(datos_fin_temp.length()) / rubrica_temp;

    string rubrica_r;
    for (int i = 0; i < rubrica_temp2; ++i){
        int k = NumberOfDigitsRint(n_E);
        string s_num_of_matriz = SeparateIntoBlocks(i, k-1,datos_fin_temp);
        ZZ i_num_of_matriz = String_To_ZZ(s_num_of_matriz);

        ZZ i_aux;
        i_aux = k_ary(i_num_of_matriz,d_E,n_E); //nuestras claveS

        ZZ total_number_digits = NumberOfDigitsZZ(n_E); //hacer que sea de tama?o N

        rubrica_r = IncreaseZeros(i_aux, total_number_digits,rubrica_r);
    }
    return rubrica_r;
}

string cypher_firma(string rubrica_r, ZZ e_R, ZZ n_R, string alfabeto){

    ZZ i_fin_temp = NumberOfDigitsZZ(n_R)-1;
    ZZ i_fin_temp2 = ZZ(rubrica_r.length()) / i_fin_temp;

    string firma_digital;
    for (int i = 0; i < i_fin_temp2; ++i){
        int k = NumberOfDigitsRint(n_R);
        string s_num_of_matriz = SeparateIntoBlocks(i, k-1,rubrica_r);
        ZZ i_num_of_matriz = String_To_ZZ(s_num_of_matriz);

        ZZ i_aux;
        i_aux = k_ary(i_num_of_matriz,e_R,n_R);

        ZZ total_number_digits = NumberOfDigitsZZ(n_R); //HACER QUE SEA DEL TAMA?O DE n
        firma_digital = IncreaseZeros(i_aux, total_number_digits,firma_digital);
    }
    return firma_digital;
}

string decypher(string mensaje,string mensaje_decifrado, ZZ n_R, ZZ d_R, string alfabeto){
    ZZ i_fin_temp = NumberOfDigitsZZ(n_R);
    ZZ i_fin_temp2 = ZZ(mensaje.length()) / i_fin_temp;

    string mensaje_decifrado_num;
    for (int i = 0; i < i_fin_temp2; ++i){
        string s_num_matriz = SeparateIntoBlocks(i, ZZ_to_int(i_fin_temp) ,mensaje);

        ZZ i_num_matriz = String_To_ZZ(s_num_matriz);

        ZZ i_aux;
        i_aux = k_ary(i_num_matriz,d_R,n_R);

        ZZ total_number_digits = NumberOfDigitsZZ(n_R)-1;
        mensaje_decifrado_num = IncreaseZeros(i_aux,total_number_digits,mensaje_decifrado_num);
    }

    ZZ i_fin_temp3 = ZZ(NumberOfDigits(alfabeto.length()));
    ZZ i_fin_temp4 = ZZ(mensaje_decifrado_num.length()) / i_fin_temp3;
    for (int i = 0; i < i_fin_temp4; ++i){
        string s_num_matriz = SeparateIntoBlocks(i, NumberOfDigits(alfabeto.length()),mensaje_decifrado_num);

        int i_num_matriz = atoi(s_num_matriz.c_str());
        string aux = ObtainMessageInLetters(i_num_matriz,alfabeto);
        mensaje_decifrado.append(aux);
    }
    return mensaje_decifrado;
}

string decypher_firma(ZZ d_R, ZZ n_R, string firma ){
    ZZ i_fin_temp = NumberOfDigitsZZ(n_R);
    ZZ i_fin_temp2 = ZZ(firma.length()) / i_fin_temp;

    string mensaje_decifrado_num;
    for (int i = 0; i < i_fin_temp2; ++i){
        string s_num_matriz = SeparateIntoBlocks(i, ZZ_to_int(i_fin_temp) , firma);

        ZZ i_num_matriz = String_To_ZZ(s_num_matriz);

        ZZ i_aux;
        i_aux = k_ary(i_num_matriz,d_R,n_R);

        ZZ total_number_digits = NumberOfDigitsZZ(n_R)-1;
        mensaje_decifrado_num = IncreaseZeros(i_aux,total_number_digits,mensaje_decifrado_num);
    }
    return mensaje_decifrado_num;
}

string decypher_rubrica(string mensaje_decifrado,string mensaje_decifrado_num, ZZ e_E, ZZ n_E, string alfabeto){
    ZZ i_fin_temp = NumberOfDigitsZZ(n_E);
    ZZ i_fin_temp2 = ZZ(mensaje_decifrado_num.length()) / i_fin_temp;

    string mensaje_ceros;
    for (int i = 0; i < i_fin_temp2; ++i){
        string s_num_matriz = SeparateIntoBlocks(i, ZZ_to_int(i_fin_temp) ,mensaje_decifrado_num);
        ZZ i_num_matriz = String_To_ZZ(s_num_matriz);

        ZZ i_aux;
        i_aux = k_ary(i_num_matriz,e_E,n_E);

        ZZ total_number_digits = NumberOfDigitsZZ(n_E)-1;
        mensaje_ceros = IncreaseZeros(i_aux,total_number_digits,mensaje_ceros);
    }

    ZZ i_fin_temp3 = ZZ(NumberOfDigits(alfabeto.length()));
    ZZ i_fin_temp4 = ZZ(mensaje_ceros.length()) / i_fin_temp3;

    for (int i = 0; i < i_fin_temp4; ++i){
        string s_num_matriz = SeparateIntoBlocks(i, NumberOfDigits(alfabeto.length()),mensaje_ceros);
        int i_num_matriz = atoi(s_num_matriz.c_str());
        string aux = ObtainMessageInLetters(i_num_matriz,alfabeto);
        mensaje_decifrado.append(aux);
    }
    return mensaje_decifrado;
}
