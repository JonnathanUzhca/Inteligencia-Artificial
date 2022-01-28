
// import javax.swing.JLabel;

// Cargamos las librerías básicas del sistema operativo
// Tienen funciones para impresión en pantalla, lectura desde teclado, etc.
#include <iostream> // Entrada y salida de datos, etc.
#include <cstdlib> // C++ Standard Library
// El nombre de las librerías va entre símbolos de <> cuando son librerías de sistema. Sin son cabeceras que hemos creado nosotros, va entre comillas dobles "nombre.hpp"

#include <cstring> // Permite trabajar con cadenas de texto

#include <sstream> // Librería que permite convertir números a cadenas y vicersa

#include <vector> // Es una arreglo dinámico (similar java.util.ArrayList)

#include <fstream> // Librería que permite escribir y leer archivos

#include <cmath> // Librería que contiene las funciones matemáticas (sqrt, cos, sin, etc.)

#include <dirent.h> // Libreía de C para listar directorios

/*
    En C++ se requiere tener un archivo de cabecera que contendrá la definición de la clase y otro archivo (fuente) que contendrá el código de los métodos o constructores
*/

// El espacio de nombres de funciones estándar se carga de la siguiente forma:

using namespace std; // Permite cargar las constantes y métodos de la librería estándar de C++ (posee métodos para manejo de cadenas, búsquedas, etc.).

class Persona{
    private:
        string cedula;
    public:
        string nombres;
        string apellidos;
        double edad;
        void saludar();
        void fibonacci(int = 137);
        bool validarCedula(string = "0705644110");
        Persona(string, string, string);
        vector<string> split(string,char = ';');
        
        bool escribirArchivo(string = "prueba.dat");
        vector<string> leerArchivo(string = "prueba.dat");
        void listarArchivos(string = ".");
        
        ~Persona();
};


/*
class Vehiculo{
};
*/

