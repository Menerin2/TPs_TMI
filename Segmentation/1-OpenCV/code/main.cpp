/*!*
 * \file main.cpp
 * \brief TP1 sur l"utilisation d"OpenCV
 * \author : Phuc Ngo
 */

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;
string window_name = "Image originale";
string second_window_name = "Image convertie";

static void help(int argc, char** argv)
{
    cout<<"Usage: "<<argv[0]<<" [input.png]\n";
}

int main( int argc, char** argv )
{
    help(argc, argv);
    string imageName("images/daisy.png");                  // Image by default
    if( argc > 1)
        imageName = "images/"+string(argv[1])+".png";
    
    Mat image;
    image = imread(imageName.c_str(), IMREAD_COLOR); // Read the file
    if( image.empty() )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow( window_name, WINDOW_AUTOSIZE );    // Create a window for display.
    imshow( window_name, image );                   // Show our image inside it.

    //waitKey(0);                                     // Wait for a keystroke in the window

    //code goes here...

    Mat image_convertie;
    cvtColor(image, image_convertie, COLOR_BGR2GRAY, 0);
    namedWindow( second_window_name, WINDOW_AUTOSIZE);
    imshow( second_window_name, image_convertie);

    Mat red = Mat(image.size(), CV_8UC3, Scalar(0,0,0));
    Mat blue = Mat(image.size(), CV_8UC3, Scalar(0,0,0));
    Mat green = Mat(image.size(), CV_8UC3, Scalar(0,0,0));

    for(int x=0; x<image.cols; x++){
        for(int y=0; y<image.rows; y++){
            Vec3b intensity = image.at<Vec3b>(y, x);
            red.at<Vec3b>(y,x).val[2] = intensity.val[2];
            blue.at<Vec3b>(y,x).val[0] = intensity.val[0];
            green.at<Vec3b>(y,x).val[1] = intensity.val[1];
        }
    }

    while (true){
        int c = waitKey(20);
        if(c=='r'){
            imshow( second_window_name, red);
        }else if(c=='b'){
            imshow( second_window_name, blue);
        }else if(c=='g'){
            imshow( second_window_name, green);
        }else if(c=='y'){
            imshow( second_window_name, image_convertie);
        }else if(c!=-1){
            break;
        }
    }
    
    return 0;
}

