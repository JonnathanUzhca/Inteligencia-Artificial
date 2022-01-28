
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

double distancia(Point p1, Point p2){
    double d = sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
    return d;
}

int main(int argc, char *argv[]){

    Mat original = imread("Figura1.png", IMREAD_GRAYSCALE);
    Mat cuadrado = imread("Cuadrado.png", IMREAD_GRAYSCALE);
    Mat canny;
    Mat imgContornos = Mat(Size(original.cols, original.rows), CV_8UC3, Scalar(0,200,200));
    Mat imgContornosC = Mat(Size(cuadrado.cols, cuadrado.rows), CV_8UC3, Scalar(0,200,200));
    Mat firma = Mat::zeros(Size(800,600), CV_8UC3);
    Mat bordesLaplace;
    Mat bordesLaplaceAbs;
    Mat cuadradoCanny;

    float ratio = 2.f;
    float cThreshold = 180.f;
    
    Canny(original,canny,cThreshold,cThreshold*ratio,3);
    Canny(cuadrado,cuadradoCanny,cThreshold,cThreshold*ratio,3);
    
    Laplacian(original, bordesLaplace, CV_16S, 3);
    convertScaleAbs(bordesLaplace, bordesLaplaceAbs);
    
    // Detección de contornos
    vector<vector<Point> > puntosContorno; // Puntos que conforman cada uno de los contornos de la imagen
    vector<Vec4i> jerarquia; // Indica cómo se conectan los diferentes puntos de los contornos
    
    vector<vector<Point> > puntosContornoC;
    vector<Vec4i> jerarquiaC;
    
    findContours(bordesLaplaceAbs,puntosContorno,jerarquia,RETR_TREE,CHAIN_APPROX_SIMPLE);
    
    findContours(cuadradoCanny,puntosContornoC,jerarquiaC,RETR_EXTERNAL,CHAIN_APPROX_NONE);
    
    cout << "# de Contornos Detectados Figura1: " << puntosContorno.size() << endl;
    cout << "# de Contornos Detectados Cuadrado: " << puntosContornoC.size() << endl;
    
    drawContours(imgContornos,puntosContorno,0,Scalar(10,10,233),2,LINE_8, jerarquia,0);
    drawContours(imgContornos,puntosContorno,3,Scalar(10,233,10),2,LINE_8, jerarquia,0);
    
    drawContours(imgContornosC,puntosContornoC,2,Scalar(10,233,10),2,LINE_8, jerarquia,0);
    
    // Representación gráfica de la firma
    double dx = 10.d;
    line(firma,Point(10,10),Point(10,firma.rows-3),Scalar(0,0,200),2);
    line(firma,Point(3,firma.rows/2),Point(firma.cols-3,firma.rows/2),Scalar(0,0,200),2);
    
    cout << "Tamaño: pos [0] = " << puntosContorno[0].size() << endl; 
    
    Moments momentos = moments(cuadradoCanny,true);
    double cx = momentos.m10/momentos.m00;
    double cy = momentos.m01/momentos.m00;
    Point centroide(cx,cy);
    
    circle(cuadrado,centroide,3,Scalar(0),3);
    
    
    vector<double> distancias;
    for(int i=0;i<puntosContornoC[2].size();i++){
        distancias.push_back(distancia(centroide,puntosContornoC[2][i]));
        cout << distancias[distancias.size()-1] << endl;
        circle(firma,Point(dx,(firma.rows/2)-distancias[distancias.size()-1]),3,Scalar(10,200,200),3);
        dx+=0.7d;
    }
    

    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Canny", WINDOW_AUTOSIZE);
    namedWindow("Laplace", WINDOW_AUTOSIZE);
    namedWindow("Contornos", WINDOW_AUTOSIZE);
    
    namedWindow("ContornosCuadrado", WINDOW_AUTOSIZE);
    namedWindow("Cuadrado", WINDOW_AUTOSIZE);
    namedWindow("CuadradoCanny", WINDOW_AUTOSIZE);
    namedWindow("Firma", WINDOW_AUTOSIZE);
    
    imshow("Original", original);
    imshow("Cuadrado", cuadrado);
    imshow("Canny", canny);
    imshow("Laplace", bordesLaplaceAbs);
    imshow("Contornos",imgContornos);
    imshow("ContornosCuadrado",imgContornosC);
    imshow("CuadradoCanny",cuadradoCanny);
    imshow("Firma",firma);
    
    waitKey(0);
    destroyAllWindows();      

    return 0;
}

// findContours
// Convex Hull

