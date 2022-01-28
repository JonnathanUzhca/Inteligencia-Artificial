
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
    Mat catedral = imread("Catedral-San-Basilio.png", IMREAD_GRAYSCALE);
    resize(catedral, catedral, Size(), 0.7,0.7);
    
    Mat gX;
    Mat gY;
    Mat gXAbs;
    Mat gYAbs;
    Mat sobelBordes;
    Mat sobelBordes2;
    Mat sobelBordes2Abs;
    Mat grisBlur;
    Mat bordesLaplace;
    Mat bordesLaplaceAbs;
    
    Mat imagenRuidoSal = catedral.clone();
    
    GaussianBlur(catedral, grisBlur, Size(3,3),0,0);
    
    
    Sobel(catedral, gX, CV_16S, 1, 0, 3);
    Sobel(catedral, gY, CV_16S, 0, 1, 3);
    Sobel(catedral, sobelBordes2, CV_16S, 1, 1, 3);
    
    convertScaleAbs(gX, gXAbs);
    convertScaleAbs(gY, gYAbs);
    convertScaleAbs(sobelBordes2, sobelBordes2Abs);
    
    Laplacian(grisBlur, bordesLaplace, CV_16S, 3);
    convertScaleAbs(bordesLaplace, bordesLaplaceAbs);
    // Suma ponderada de 2 imágenes
    addWeighted(gXAbs, 0.5, gYAbs, 0.5, 0, sobelBordes);
    
    
    // Generamos ruido de sal:
    int total = (int)(0.2*catedral.rows*catedral.cols);
    cout << "Total: " << total << endl;
    int cont = 0;
    int fila = 0;
    int col = 0;
    
    srand(time(0));
    while(cont<total){
        fila = rand() % catedral.rows;
        col = rand() % catedral.cols;
        
        cont++;
        imagenRuidoSal.at<uchar>(fila,col) = 255;
    }
    
    
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("GX", WINDOW_AUTOSIZE);
    namedWindow("GY", WINDOW_AUTOSIZE);
    namedWindow("GX + GY", WINDOW_AUTOSIZE);
    namedWindow("SobelBordes2", WINDOW_AUTOSIZE);
    namedWindow("Laplacian", WINDOW_AUTOSIZE);
    namedWindow("Ruido Sal", WINDOW_AUTOSIZE);

    imshow("Original", catedral);
    imshow("GX", gXAbs);
    imshow("GY", gYAbs);
    imshow("GX + GY", sobelBordes);
    imshow("SobelBordes2", sobelBordes2Abs);
    imshow("Laplacian", bordesLaplaceAbs);
    imshow("Ruido Sal", imagenRuidoSal);

    waitKey(0);
    
    destroyAllWindows();  
    
    
    VideoCapture video("OneMinute.mkv");
    
    if(video.isOpened()){
        Mat frame;
        Mat canny;
        int umbral = 70;
        double ratio = 3.;
        
        
        namedWindow("Frame", WINDOW_AUTOSIZE);
        namedWindow("Laplacian", WINDOW_AUTOSIZE);
        namedWindow("Canny", WINDOW_AUTOSIZE);
        
        while(3==3){
            video >> frame;
            resize(frame, frame, Size(), 0.5, 0.5);
            cvtColor(frame, grisBlur, COLOR_BGR2GRAY);
            GaussianBlur(grisBlur, grisBlur, Size(3,3),0,0);
            Laplacian(grisBlur, bordesLaplace, CV_16S, 3);
            convertScaleAbs(bordesLaplace, bordesLaplaceAbs);
            
            bitwise_not(bordesLaplaceAbs, bordesLaplaceAbs);

            Canny(grisBlur, canny, umbral, umbral*ratio, 3);
            
            imshow("Frame", frame);
            imshow("Laplacian", bordesLaplaceAbs);
            imshow("Canny", canny);
            
            if(waitKey(23)==27)
                break;
        }
        
        destroyAllWindows();  
    }
    
    
    
    
    return 0;
}


