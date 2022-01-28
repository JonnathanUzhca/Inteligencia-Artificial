
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
    Mat imagen = imread("ImagenOscura.png");
    Mat imagenEcualizada;
    
    Mat gris;
    Mat imagenVacia = Mat::zeros(Size(512,373), CV_8UC3); // Color
    Mat imagenVaciaE = Mat::zeros(Size(512,373), CV_8UC3); // Color
    
    // Función para convertir de un espacio de color a otro
    cvtColor(imagen,gris, COLOR_BGR2GRAY);
    
    equalizeHist(gris, imagenEcualizada);
    
    
    // Creamos una ventana donde se mostrará la imagen
    namedWindow("Histograma", WINDOW_AUTOSIZE);
    namedWindow("Gris", WINDOW_AUTOSIZE);
    namedWindow("Gris Ecualizada", WINDOW_AUTOSIZE);

    
    // Cálculo del histograma
    int *histo = new int[256];
    int *histoE = new int[256];
    
    for(int i=0;i<256;i++){
        histo[i] = 0;
        histoE[i] = 0;
    }
    
    double maximo = -1;
    double maximoE = -1;
    int pixel = 0;
    for(int i=0;i<gris.rows;i++){
        for(int j=0;j<gris.cols;j++){
            pixel = gris.at<uchar>(i,j);
            histo[pixel]++;
            pixel = imagenEcualizada.at<uchar>(i,j);
            histoE[pixel]++;
        }
    }
    
    for(int i=0;i<256;i++){
        cout << histo[i] << "," ;
        if(histo[i]>maximo)
            maximo = histo[i];
        
        if(histoE[i]>maximoE)
            maximoE = histoE[i];
    }
    cout << endl;
    
    for(int i=0;i<256;i++){
        line(imagenVacia, Point(i*2,373), Point(i*2,373-(histo[i]*373/maximo)), Scalar(10,200,200),2 );
        line(imagenVaciaE, Point(i*2,373), Point(i*2,373-(histoE[i]*373/maximo)), Scalar(10,10,200),2 );
    }
    
    
    // Mostramos la imagen en pantalla
    imshow("Histograma", imagenVacia);
    imshow("HistogramaE", imagenVaciaE);
    imshow("Gris", gris);
    imshow("Gris Ecualizada", imagenEcualizada);

    waitKey(0);
    
    destroyAllWindows();
    
    delete [] histo;
    delete [] histoE;
    
    
    // Resta de imágenes
    
    Mat img1 = imread("Imagen1.png", IMREAD_GRAYSCALE);
    Mat img2 = imread("Imagen2.png", IMREAD_GRAYSCALE);
    Mat resta;
    
    absdiff(img1, img2, resta);
    
    namedWindow("Resta", WINDOW_AUTOSIZE);
    imshow("Resa", resta);
    
        
    // Cómo manejar video
    //VideoCapture video("/dev/video33");
    VideoCapture video("OneMinute.mkv");
    Mat anterior;
    Mat frameGris;
    
    if(video.isOpened()){
        Mat frame;
        namedWindow("Video", WINDOW_AUTOSIZE);
        namedWindow("Movimiento", WINDOW_AUTOSIZE);
        
        while(3==3){
            video >> frame;
            
            cvtColor(frame, frameGris, COLOR_BGR2GRAY);
            if(anterior.rows==0 || anterior.cols==0)
                anterior = frameGris.clone();
            
            absdiff(frameGris, anterior, resta);
            anterior = frameGris.clone();
            
            
            if(frame.rows == 0 || frame.cols == 0)
                break;
            
            imshow("Video", frame);
            imshow("Movimiento", resta);
            
            if(waitKey(23)==27)
                break;
            
        }
        destroyAllWindows();
    }
    
    return 0;
}


