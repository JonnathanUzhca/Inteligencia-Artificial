

#include "Cabecera.hpp"

Persona::Persona(string n, string a, string c){
    this->nombres = n;
    this->apellidos = a;
    this->cedula = c; // Puntero a la misma clase
}

void Persona::saludar(){
    cout << "Hola: " << nombres << " " << apellidos << endl;
}

void Persona::fibonacci(int limite){
    int a = 0;
    int b = 1;
    int c = a+b;
    cout << a << "," << b << "," << c;
    while(c<limite){
        a = b;
        b = c;
        c = a+b;
        cout << "," << c;        
    }
    cout << endl;
}
