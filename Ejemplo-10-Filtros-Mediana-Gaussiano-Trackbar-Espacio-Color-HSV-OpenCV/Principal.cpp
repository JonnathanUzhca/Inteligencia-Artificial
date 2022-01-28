
// Librerías que contienen funciones estándar de C++
#include <iostream>
#include <cstdlib>


// Librería que contiene funciones matemáticas
#include <cmath>

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


int k = 3; // Representa el tamaño del kernel
Mat imagenMediana;
Mat imagen;
Mat imagenGaussiana;

void functionTrackbar(int v, void *p){

    int *pX = (int *) p;
    cout << "Puntero: " << *pX << endl;
    
    cout << "Valor: " << k << endl;
    if(k%2==1){
        medianBlur(imagen, imagenMediana, k);
        GaussianBlur(imagen, imagenGaussiana, Size(k, k), 2, 2);
        imshow("Mediana", imagenMediana);
        imshow("GaussianBlur", imagenGaussiana);
    }
}


int main(int argc, char *argv[]){
    // En OpenCV las imágenes a color se representan como BGR:
    
    // Leemos la imagen y la guardamos en una matriz llamada "imagen"
    imagen = imread("Catedral-San-Basilio.png");//, IMREAD_GRAYSCALE);
    resize(imagen, imagen, Size(), 0.5, 0.5);
    
    medianBlur(imagen, imagenMediana, k);
    GaussianBlur(imagen, imagenGaussiana, Size(k, k), 2, 2);
    
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Mediana", WINDOW_AUTOSIZE);
    namedWindow("GaussianBlur", WINDOW_AUTOSIZE);
    
    int x = 23;
    int *pX = &x;
    
    createTrackbar("Kernel", "Original", &k, 37, functionTrackbar, (void *) pX);

    imshow("Original", imagen);
    imshow("Mediana", imagenMediana);
    imshow("GaussianBlur", imagenGaussiana);

    waitKey(0);
    
    destroyAllWindows();  
    
    VideoCapture video("OneMinute.mkv");
    
    if(video.isOpened()){
        Mat frame;
        Mat frameHSV;
        
        namedWindow("Frame", WINDOW_AUTOSIZE);
        namedWindow("HSV", WINDOW_AUTOSIZE);
        
        while(3==3){
            video >> frame;
            resize(frame, frame, Size(), 0.5, 0.5);
            cvtColor(frame, frameHSV, COLOR_BGR2HSV);
            
            imshow("Frame", frame);
            imshow("HSV", frameHSV);
            
            if(waitKey(23)==27)
                break;
        }
        
        destroyAllWindows();  
    }

    
    return 0;
}


