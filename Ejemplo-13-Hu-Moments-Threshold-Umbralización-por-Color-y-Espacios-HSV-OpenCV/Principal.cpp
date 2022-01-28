
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


int umbral = 255;

int minH = 19, minS = 30, minV = 183;
int maxH = 44, maxS = 255, maxV = 255;



void trackBarEventHSV(int v, void *p){
}

double distancia(double m1[7], double m2[7]){
    double suma = 0.0;
    for(int i=0;i<7;i++){
        suma+=(m1[i]-m2[i])*(m1[i]-m2[i]);
    }
    suma = sqrt(suma);
    return suma;
}


int main(int argc, char *argv[]){

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
        
        double huMoments[7]; // Momentos invariantes a rotación, traslación y escala que se van a calcular
        Moments momentos; // Momentos generales
        double baseDatos[7] = {0.189952,0.0082864,3.78489e-05,7.83997e-07,4.21973e-12,7.12184e-08,6.5779e-13};
        double cx = 0;
        double cy = 0;
        
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
            
            momentos = moments(roi, true);
            HuMoments(momentos, huMoments);
            /*
            for(int i=0;i<7;i++)
                cout << huMoments[i] << ",";
            
            cout << endl;
            */
            cout << " Distancia: momentos vs baseDatos: " << distancia(huMoments,baseDatos) << endl;
            
            if (distancia(huMoments, baseDatos)<0.03){
                cx = momentos.m10/momentos.m00;
                cy = momentos.m01/momentos.m00;
                
                circle(frame, Point(cx,cy),7,Scalar(10,10,203),3);
                putText(frame,"Reconocido",Point(cx,cy-30),FONT_HERSHEY_SIMPLEX,0.5,Scalar(203,10,10));
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
