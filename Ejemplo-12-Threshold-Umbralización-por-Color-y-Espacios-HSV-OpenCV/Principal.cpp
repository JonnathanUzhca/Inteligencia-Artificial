
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


Mat imgThreshold;
Mat catedral;

int umbral = 255;

int minH = 19, minS = 30, minV = 183;
int maxH = 44, maxS = 255, maxV = 255;



void trackBarEvent(int v, void *p){
    threshold(catedral, imgThreshold, umbral, 255, THRESH_BINARY);
    imshow("Threshold", imgThreshold);
}

void trackBarEventHSV(int v, void *p){
}


int main(int argc, char *argv[]){
    // En OpenCV las imágenes a color se representan como BGR:
    
    // Leemos la imagen y la guardamos en una matriz llamada "imagen"
    catedral = imread("Catedral-San-Basilio.png", IMREAD_GRAYSCALE);
    resize(catedral, catedral, Size(), 0.7,0.7);
    
    threshold(catedral, imgThreshold, umbral, 255, THRESH_BINARY);
    
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Threshold", WINDOW_AUTOSIZE);
    
    createTrackbar("Threshold", "Original", &umbral, 255, trackBarEvent, NULL);
    

    imshow("Original", catedral);
    imshow("Threshold", imgThreshold);

    waitKey(0);
    
    destroyAllWindows();  

        
    VideoCapture video(33);
    
    if(video.isOpened()){
        Mat frame;
        Mat imgHSV;
        Mat roi; // Region of Interes, Zona de Interés
        
        Mat objeto;
        
        namedWindow("Frame", WINDOW_AUTOSIZE);
        namedWindow("HSV", WINDOW_AUTOSIZE);
        namedWindow("ROI", WINDOW_AUTOSIZE);
        
        namedWindow("Objeto", WINDOW_AUTOSIZE);
        
        createTrackbar("H-Min", "Frame", &minH, 180, trackBarEventHSV, NULL);
        createTrackbar("S-Min", "Frame", &minS, 255, trackBarEventHSV, NULL);
        createTrackbar("V-Min", "Frame", &minV, 255, trackBarEventHSV, NULL);
        
        createTrackbar("H-Max", "Frame", &maxH, 180, trackBarEventHSV, NULL);
        createTrackbar("S-Max", "Frame", &maxS, 255, trackBarEventHSV, NULL);
        createTrackbar("V-Max", "Frame", &maxV, 255, trackBarEventHSV, NULL);
        
        int pixel = 0;
        
        while(3==3){
            video >> frame;
            
            cvtColor(frame, imgHSV, COLOR_BGR2HSV);
            
            inRange(imgHSV, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), roi);
            
            //if(objeto.empty())
            {
                objeto = Mat(Size(frame.cols, frame.rows), CV_8UC3, Scalar(255,255,255));
            }
            
            for(int i=0;i<roi.rows;i++){
                for(int j=0;j<roi.cols;j++){
                    pixel = roi.at<uchar>(i,j);
                    if(pixel>0){
                        objeto.at<Vec3b>(i,j) = frame.at<Vec3b>(i,j);
                    }
                }
            }
            
            imshow("Frame", frame);
            imshow("HSV", imgHSV);
            imshow("ROI", roi);
            imshow("Objeto", objeto);
            
            if(waitKey(23)==27)
                break;
        }
        
        destroyAllWindows();  
    }

    return 0;
}

// findContours
// Convex Hull
