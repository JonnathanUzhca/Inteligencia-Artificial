
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


int main(int argc, char *argv[]){
    // En OpenCV las imágenes a color se representan como BGR:
    
    // Leemos la imagen y la guardamos en una matriz llamada "imagen"
    Mat imagen = imread("Catedral-San-Basilio.png");
    
    // Cómo cambiar el tamaño de una imagen (resize):
    resize(imagen, imagen, Size(),0.5,0.5);
    
    // Creamos una ventana donde se mostrará la imagen
    namedWindow("Imagen", WINDOW_AUTOSIZE);
    namedWindow("Histograma", WINDOW_AUTOSIZE);
    namedWindow("Gris Promedio", WINDOW_AUTOSIZE);
    namedWindow("Gris Ponderado", WINDOW_AUTOSIZE);

    // Cómo obtener las características de una imagen dada:
    cout << "Filas: " << imagen.rows << " Columnas: " << imagen.cols << " Canales: " << imagen.channels() << endl;
    
    // Creamos una imagen llena de ceros que tenga el mismo tamaño de la imagen a color
    Mat imagenVacia = Mat::zeros(Size(512,373), CV_8UC3); // Color
    
    // Cómo clonar imágenes
    Mat grisPromedio = Mat::zeros(Size(imagen.cols,imagen.rows), CV_8UC1); // Gris
    Mat grisPonderado = Mat::zeros(Size(imagen.cols,imagen.rows), CV_8UC1);
    
    Vec3b pixel3D;
    int pixel;
    
    // Conversión Manual de Color a Gris
    for(int i=0;i<imagen.rows;i++){
        for(int j=0;j<imagen.cols;j++){
            // Para acceder a un pixel, se usa el método GENÉRICO at<tipo_dato>(fila,columna)
            pixel3D = imagen.at<Vec3b>(i,j);
            // Gris Promedio
            pixel = (pixel3D[0]+pixel3D[1]+pixel3D[2])/3;
            // Como almacenamos los pixeles en la matriz
            grisPromedio.at<uchar>(i,j) = pixel;
            // Gris Ponderado
            pixel = ((double)pixel3D[2])*0.3+((double)pixel3D[1])*0.59+((double)pixel3D[0])*0.11;
            grisPonderado.at<uchar>(i,j) = pixel;
        }
    }
    
    
    // Cálculo del histograma
    int *histo = new int[256];
    
    for(int i=0;i<256;i++)
        histo[i] = 0;
    
    double maximo = -1;
    for(int i=0;i<grisPonderado.rows;i++){
        for(int j=0;j<grisPonderado.cols;j++){
            pixel = grisPonderado.at<uchar>(i,j);
            histo[pixel]++;
        }
    }
    
    for(int i=0;i<256;i++){
        cout << histo[i] << "," ;
        if(histo[i]>maximo)
            maximo = histo[i];
    }
    cout << endl;
    
    for(int i=0;i<256;i++){
        line(imagenVacia, Point(i*2,373), Point(i*2,373-(histo[i]*373/maximo)), Scalar(10,200,200),2 );
    }
    
    
    // Mostramos la imagen en pantalla
    imshow("Imagen", imagen);
    imshow("Histograma", imagenVacia);
    imshow("Gris Promedio", grisPromedio);
    imshow("Gris Ponderado", grisPonderado);
    // Quedamos en espera de que se presione alguna tecla
    
    imwrite("GrisPonderado.png",grisPonderado);
    waitKey(0);
    
    delete [] histo;
    
    return 0;
}


