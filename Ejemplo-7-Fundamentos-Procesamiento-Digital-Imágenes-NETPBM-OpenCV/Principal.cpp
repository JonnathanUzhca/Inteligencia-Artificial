
// Librerías que contienen funciones estándar de C++
#include <iostream>
#include <cstdlib>

// Librerías de OpenCV

// Se pueden cargar todas las Librerías incluyendo
//#include <opencv2/opencv.hpp>

// Contiene las definiciones fundamentales de las matrices e imágenes 
#include <opencv2/core/core.hpp> 
// Procesamiento de imágenes
#include <opencv2/imgproc/imgproc.hpp>
// Códecs de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp>
// Manejo de ventanas y eventos de ratón, teclado, etc.
#include <opencv2/highgui/highgui.hpp>
// Lectura de video
#include <opencv2/video/video.hpp>
// Escritura de video
#include <opencv2/videoio/videoio.hpp>

using namespace std;
using namespace cv; // Espacio de nombres de OpenCV (Contiene funciones y definiciones de varios elementos de OpenCV)


int main(int argc, char *argv[]){
    // En OpenCV las imágenes a color se representan como BGR:
    
    // Leemos la imagen y la guardamos en una matriz llamada "imagen"
    Mat imagen = imread("Catedral-San-Basilio.jpg");
    // Creamos una ventana donde se mostrará la imagen
    namedWindow("Imagen", WINDOW_AUTOSIZE);
    // Mostramos la imagen en pantalla
    imshow("Imagen", imagen);
    
    // Guardar la imagen
    imwrite("Catedral-San-Basilio.png", imagen);
    
    // Quedamos en espera de que se presione alguna tecla
    waitKey(0);
    return 0;
}


