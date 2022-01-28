
#include "Cabecera.hpp"

int main(int argc, char *argv[]){ //public void main(String[]args){
    Persona persona("Nicolás","Añazco","0705644110");
    
    persona.saludar();
    persona.fibonacci();
    
    string cad = "23\t17";
    stringstream ss;
    ss << cad;
    int numero = 0;
    ss >> numero;
    
    cout << "Número: " << numero << endl;
    // Limpiamos el flujo de datos: 
    ss.str("");
    ss << "El número " << numero << " x 10 = " << (numero*10);
    string cadena2 = ss.str();
    
    cout << cadena2 << endl;
    
    
    vector<string> res = persona.split("Java;C/C++;Python;Ruby;Perl;Groovy");
    for(int i=0;i<res.size();i++)
        cout << res[i] << endl;
    
    bool r = persona.validarCedula();
    cout << "Cédula Correcta: " << (r==true?"True":"False") << endl;
    
    // Manejo de punteros 
    int x = 23;
    int *pX = &x;
    
    cout << "Posición de Memoria: " << pX << " Valor: " << *(pX) << endl;
    
    *(pX) = 33;
    
    cout << "Valor de X: " << x << endl;
    
    Persona *pPersona = new Persona("Juan", "Benavides", "0105817639");
    pPersona->saludar();
    pPersona->listarArchivos();
    
    
    cout << "Escribe archivo: " << pPersona->escribirArchivo() << endl;
    
    vector<string> lec = pPersona->leerArchivo();
    for(int i=0;i<lec.size();i++)
        cout << lec[i] << "\t";
    cout << endl;
    
    delete pPersona;
    
    // Arreglo común:
    double z[3];
    z[0] = 23.3;
    z[1] = 1;
    z[2] = 9.77;
    
    // Arreglo puntero:
    double *pA = new double[3];
    pA[0] = 1;
    pA[1] = 2;
    pA[2] = 3;
    
    *(pA+0) = 11;
    *(pA+1) = 12;
    *(pA+2) = 13;

    double *pS = new double[3];
    cout << "Valor pos 0 puntero S: " << pS[0] << endl;
    
    int *pM = (int *) malloc(3*sizeof(int));
    cout << "Valor pos 0 puntero M: " << *(pM) << endl;
    
    delete pM;    
    // Eliminamos el arreglo puntero
    delete [] pA;
    delete [] pS;
    return 0;
}
