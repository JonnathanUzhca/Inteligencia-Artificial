#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*Universidad Politecnica Salesiana
Proyecto final de INteligencia Artificial
Jonnathan Uzhca
*/

int main( int argc, const char** argv)
{

//Captura de la camara para reproduccion de video
    VideoCapture cam(0);
//Declaramos de una matriz en un archivo de imagen
    Mat img;
//Declaracion de una matriz de threshold
    Mat img_threshold;
//Declaracion de  una matriz de imagen en gris
    Mat img_gray;
//Declaracion de una matriz para el recorte de un espacion de la imagen original
    Mat img_roi;
/*La función namedWindow crea una ventana que se puede utilizar como marcador de posición para imágenes y barras de seguimiento. Las ventanas creadas sedenominan por sus nombres.*/
    namedWindow("Imagen Orige",WINDOW_AUTOSIZE);
    namedWindow("Imagen Digris",WINDOW_AUTOSIZE);
    namedWindow("Umbral",WINDOW_AUTOSIZE);
    namedWindow("ROI",WINDOW_AUTOSIZE);
    char a[40];
    int count =0;
//Deteccion de la camara para verificar si esta esta encensida o no
    while(true){
        bool b=cam.read(img);
        if(!b){
            cout<<"ERROR : cannot read"<<endl;
            return -1;
        }
//Declaracion de un rectangolo en 2D
        Rect roi(340,100,280,280);
        img_roi=img(roi);
//permite cambiar el espacio de color de una imagen
        cvtColor(img_roi,img_gray,COLOR_RGB2GRAY);
//desenfoque / suavizado gaussiano es la técnica de suavizado más utilizada para eliminar ruidos en imágenes y videos
        GaussianBlur(img_gray,img_gray,Size(19,19),0.0,0);
/*utiliza para aplicar el umbral. El primer argumento es la imagen de origen, que debería ser una imagen en escala de grises . El segundo argumento es el valor umbral que se utiliza para clasificar los valores de los píxeles. El tercer argumento es el valor máximo que se asigna a los valores de píxeles que superan el umbral. OpenCV proporciona diferentes tipos de umbral que viene dado por el cuarto parámetro de la función.*/
        threshold(img_gray,img_threshold,0,255,THRESH_BINARY_INV+THRESH_OTSU);
//Declaramos vectores que nos ayuden a calculamos los contornos
        vector<vector<Point> >contours;
        vector<Vec4i>hierarchy;
//es una función que permite encontrar los n contornos externos e internos de una imagen binaria (blanco y negro).  
        findContours(img_threshold,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point());

        if(contours.size()>0){
                size_t indexOfBiggestContour = -1;
	            size_t sizeOfBiggestContour = 0;
//Recorremos los contornos de la imagen que vamso a dectectar
	            for (size_t i = 0; i < contours.size(); i++){
		           if(contours[i].size() > sizeOfBiggestContour){
			       sizeOfBiggestContour = contours[i].size();
			       indexOfBiggestContour = i;
		          }
                }
/* Los vectores se conocen como matrices dinámicas con la capacidad de cambiar su tamaño automáticamente cuando se inserta o elimina un elemento, y su almacenamiento es manejado automáticamente por el contenedor.*/
                vector<vector<int> >hull(contours.size());
                vector<vector<Point> >hullPoint(contours.size());
                vector<vector<Vec4i> >defects(contours.size());
                vector<vector<Point> >defectPoint(contours.size());
                vector<vector<Point> >contours_poly(contours.size());
                Point2f rect_point[4];
                vector<RotatedRect>minRect(contours.size());
                vector<Rect> boundRect(contours.size());
//Vamos a recorrer los datos de los contornos
                for(size_t i=0;i<contours.size();i++){
                    if(contourArea(contours[i])>5000){
                        convexHull(contours[i],hull[i],true);
                        convexityDefects(contours[i],hull[i],defects[i]);
                        if(indexOfBiggestContour==i){
                            minRect[i]=minAreaRect(contours[i]);
                            for(size_t k=0;k<hull[i].size();k++){
                                int ind=hull[i][k];
                                hullPoint[i].push_back(contours[i][ind]);
                            }
                            count =0;

                            for(size_t k=0;k<defects[i].size();k++){
                                if(defects[i][k][3]>13*256){
                                 /*   int p_start=defects[i][k][0];   */
                                    int p_end=defects[i][k][1];
                                    int p_far=defects[i][k][2];
                                    defectPoint[i].push_back(contours[i][p_far]);
                                    circle(img_roi,contours[i][p_end],3,Scalar(0,255,0),2);
                                    count++;
                                }

                            }

                            if(count==1)
                                strcpy(a,"1");
                            else if(count==2)
                                strcpy(a,"2 ");
                            else if(count==3)
                                strcpy(a,"3 ");
                            else if(count==4)
                                strcpy(a,"4");
                            else if(count==5)
                                strcpy(a,"5");
                            else if(count==0)
                                strcpy(a,"Ningun Gesto en la Mano");
                           

                            putText(img,a,Point(20,70),FONT_HERSHEY_SIMPLEX,3,Scalar(255,0,0),2,8,false);
                            drawContours(img_threshold, contours, i,Scalar(255,255,0),2, 8, vector<Vec4i>(), 0, Point() );
                            drawContours(img_threshold, hullPoint, i, Scalar(255,255,0),1, 8, vector<Vec4i>(),0, Point());
                            drawContours(img_roi, hullPoint, i, Scalar(0,0,255),2, 8, vector<Vec4i>(),0, Point() );
                            approxPolyDP(contours[i],contours_poly[i],3,false);
                            boundRect[i]=boundingRect(contours_poly[i]);
                            rectangle(img_roi,boundRect[i].tl(),boundRect[i].br(),Scalar(255,0,0),2,8,0);
                            minRect[i].points(rect_point);
                            for(size_t k=0;k<4;k++){
                                line(img_roi,rect_point[k],rect_point[(k+1)%4],Scalar(0,255,0),2,8);
                            }

                        }
                    }

                }
            imshow("Imagen Orige",img);
            imshow("Imagen Digris",img_gray);
            imshow("Umbral",img_threshold);
            imshow("ROI",img_roi);
            if(waitKey(30)==27){
                  return -1;
             }

        }

    }

     return 0;
}

