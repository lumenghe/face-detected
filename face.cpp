//! [includes]
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <string>



// GLOBAL PARAMS
#define CAP_WIDTH_PARAM 3
#define CAP_HEIGHT_PARAM 4
#define CAP_WIDTH 640
#define CAP_HEIGHT 480

int main( int argc, char** argv )
{


    cv::VideoCapture cap(0);
    if(!cap.isOpened())
        return -1;
        
    cap.set(CAP_WIDTH_PARAM, CAP_WIDTH);
    cap.set(CAP_HEIGHT_PARAM, CAP_HEIGHT);
    
    cv::CascadeClassifier faceCascade;
    if (faceCascade.load("haarcascade_frontalface_default.xml") == false)
        return -1;
    
    cv::Mat frame, gray;
    
    while(true){
        // Capture frame-by-frame
        cap >> frame;
        cv::flip(frame, gray, 1);
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(frame, gray, cv::Size(21, 21), 0, 0);
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.3, 5, 0, cv::Size(50, 50));
        
        std::vector<cv::Rect>::const_iterator i;
        for (i = faces.begin(); i != faces.end(); ++i){
            cv::rectangle(
                    frame, 
                    cv::Point(i->x, i->y), 
                    cv::Point(i->x+i->width, i->y+i->height), 
                    CV_RGB(0, 255, 0),
                    2);
        
        }
        
        cv::imshow("frame", frame);
        int c = cv::waitKey(1);
        if (c==27)
            break;
    }

    cap.release();
    cv::destroyAllWindows();
    
   
    
    return 0;
}


