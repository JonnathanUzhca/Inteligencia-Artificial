
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

int minH = 19, minS = 30, minV = 183;
int maxH = 44, maxS = 255, maxV = 255;

void trackBarEventHSV(int v, void *p){
}


int main(int argc, char *argv[]){
        
    VideoCapture video(33);
    Mat elemento = getStructuringElement(MORPH_CROSS, Size(3,3), Point(-1,-1));
    
    if(video.isOpened()){
        Mat frame;
        Mat imgHSV;
        Mat roi; // Region of Interes, Zona de Interés
        
        Mat objeto;
        
        Mat imgApertura;
        Mat imgDilatacion;
        
        
        
        namedWindow("Frame", WINDOW_AUTOSIZE);
        namedWindow("HSV", WINDOW_AUTOSIZE);
        namedWindow("ROI", WINDOW_AUTOSIZE);
        
        namedWindow("Objeto", WINDOW_AUTOSIZE);
        namedWindow("Imagen Apertura", WINDOW_AUTOSIZE);
        namedWindow("Imagen Dilatacion", WINDOW_AUTOSIZE);
        
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
            
            morphologyEx(roi, imgApertura, MORPH_OPEN,elemento);
            morphologyEx(roi, imgDilatacion, MORPH_DILATE,elemento);
            
            imshow("Frame", frame);
            imshow("HSV", imgHSV);
            imshow("ROI", roi);
            imshow("Objeto", objeto);
            imshow("Imagen Apertura", imgApertura);
            imshow("Imagen Dilatacion", imgDilatacion);
            
            if(waitKey(23)==27)
                break;
        }
        
        destroyAllWindows();  
    }
    
    
    /*
    Nombres de las Constantes para Operaciones Morfológicas:
    erosión: MORPH_ERODE
    dilatación: MORPH_DILATE
    apertura: MORPH_OPEN
    cierre: MORPH_CLOSE
    black hat: MORPH_BLACKHAT
    top hat: MORPH_TOPHAT
    
    gradiente: MORPH_GRADIENT
    
    */
    
    Mat chest = imread("chest.jpg");
    resize(chest,chest,Size(),0.5,0.5);
    
    namedWindow("Chest", WINDOW_AUTOSIZE);
    namedWindow("ChestEro", WINDOW_AUTOSIZE);
    namedWindow("ChestDil", WINDOW_AUTOSIZE);
    namedWindow("ChestResta", WINDOW_AUTOSIZE);
    
    
    Mat chestEro;
    Mat chestDil;
    Mat chestResta;
    
    morphologyEx(chest,chestEro,MORPH_ERODE,elemento);
    morphologyEx(chest,chestDil,MORPH_DILATE,elemento);
    
    absdiff(chestEro, chestDil, chestResta);
    
    imshow("Chest", chest);
    imshow("ChestEro", chestEro);
    imshow("ChestDil", chestDil);
    imshow("ChestResta", chestResta);
    
    
    waitKey(0);

    return 0;
}

// findContours
// Convex Hull

