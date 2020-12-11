#include <opencv2/opencv.hpp>
#include "cv.h"
#include "highgui.h"

using namespace cv;
using namespace std;

int main ()
{
    char c;
    Mat frame;
    Mat umbral;
    Mat imagenGaussian;
    Mat imagen;
    CvCapture* capture = 0;
    capture = cvCaptureFromCAM(0);

    while(1)
    {
        frame = cvQueryFrame( capture );
        //imagen = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
        cvtColor(frame, imagen, CV_RGB2HSV);
        inRange(imagen, Scalar(7, 220, 170), Scalar(26, 255, 248), umbral);
        GaussianBlur(umbral, imagenGaussian, Size(9, 9), 2, 2);
        vector<Vec3f> circles;
        HoughCircles(imagenGaussian, circles, CV_HOUGH_GRADIENT, 1, imagenGaussian.rows/8, 100, 20, 0, 0);
        if(circles.size() == 0);
        for(size_t i = 0; i < circles.size(); i++ )
        {
           Point center(round(circles[i][0]), round(circles[i][1]));
           double radius = round(circles[i][1.9]);
           // circle center
           //putText(imagenTexto,"steven", Point(0, frame.cols/2), FONT_HERSHEY_SIMPLEX, 2.0, Scalar(0,255,0), 2);
           circle(frame, center, 3, Scalar(0,255,0), -1, 8, 0 );

           // circle outline
           circle(frame, center, radius/4, Scalar(0,255,0), 5);
           //Texto
           Mat imagenTexto = Mat::zeros(frame.rows, frame.cols, frame.type());
           putText(imagenTexto, "Pelota - Amarilla", Point(200, frame.cols/2), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,255,0), 2);
           frame = frame+imagenTexto;
        }


        imshow("Segmentacion", umbral);
        imshow("Camara", frame);
        imshow("Gaussian",imagenGaussian);
        imshow("HSV", imagen);
        c=cvWaitKey(1);
        if( c == 27 ) break;
    }

}
