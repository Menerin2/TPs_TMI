/*!*
 * \file main.cpp
 * \brief TP3 sur la segmentation basée région
 * \author : Phuc Ngo
 */

#include "functions.h" 

Mat src, src_gray, dst;
vector<Point> germes;

string window_org = "Original image";
string window_res = "Croissance de region Demo";
string trackbar_value = "Seuil";

int threshold_value = 10;
int threshold_type = 0;
int const max_value = 256;
int predicat = 1;

static void onTrackbar( int, void* ) ;
static void onMouse( int , int , int , int , void* ) ;

static void help(int argc, char** argv)
{
    cout<<"Usage: "<<argv[0]<<" [input.png] [predicat=1, 2, 3]\n";
}


int main( int argc, char** argv )
{
    help(argc, argv);
    string imageName("images/rice.png"); // by default
    if( argc > 1)
        imageName = argv[1];
    if( argc > 2)
        predicat = atoi(argv[2]);
    
    src = imread(imageName.c_str(), IMREAD_COLOR); // Read the file
    if( src.empty() )                      // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    
    namedWindow( window_org, WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( window_org, src );                // Show our image inside it.
    setMouseCallback( window_org, onMouse ) ; //set the callback function for selecting germes with mouse event.
    
    namedWindow( window_res, WINDOW_AUTOSIZE ); // Create a window for display.
    createTrackbar( trackbar_value, window_res, &threshold_value, max_value, onTrackbar ); // Create Trackbar
    onTrackbar( 0, 0 ); // Call the function to initialize
    
    /// Wait until user finishes program with ESC key
    while(true)
    {
        int c;
        c = waitKey( 20 );
        if( (char)c == 27 )
        { break; }
    }
    
    return 0;
}

static void onTrackbar( int, void* )
{
    dst = Mat(src_gray.size(), CV_8U, Scalar(0,0,0));
    dst = croissanceRegion(src_gray, germes, threshold_value, predicat);
    imshow( window_res, dst );
}

static void onMouse(int event, int x, int y, int flags, void* data)  {
    if  ( event == EVENT_LBUTTONDOWN )
    {
        germes.push_back(Point(x,y));
        circle(src,Point(x,y),5,Scalar(255,0,0),-1);
        imshow(window_org, src);
    }
}
