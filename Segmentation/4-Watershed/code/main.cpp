/*!*
 * \file main.cpp
 * \brief TP4 sur la segmentation basée contour
 * \author : Phuc Ngo
 */

#include "functions.h"

Mat src, src_gray, dst, markers;
vector<Point> germes;

string window_org = "Original image";
int exercise = 1;
string typeSE = "croix"; //carree, disque, diamant, croix, hligne, vlinge
int taille = 1;

static void onMouse( int , int , int , int , void* ) ;

static void help(int argc, char** argv)
{
    cout<<"Usage: "<<argv[0]<<" [input.png] [numExo] [typeSE] [taille]\n";
    cout<<"typeSE: carree, disque, croix, hligne, vlinge\n";
}

int main( int argc, char** argv )
{
    help(argc, argv);
    string imageName("images/tree.png"); // by default
    if( argc > 1)
        imageName = argv[1];
    if( argc > 2)
        exercise = atoi(argv[2]);
    if( argc > 4) {
        typeSE = argv[3];
        taille = atoi(argv[4]);
    }

    Mat element = elementStruturant(taille, typeSE);
    
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

    // Exercise 2 : morphological operators
    if(exercise == 2) {
        namedWindow( "Dilatation", WINDOW_AUTOSIZE );
        namedWindow( "Erosion", WINDOW_AUTOSIZE );
        namedWindow( "Ouverture", WINDOW_AUTOSIZE );
        namedWindow( "Fermeture", WINDOW_AUTOSIZE );

        Mat d = dilatation (src_gray, element);
        Mat e = erosion (src_gray, element);
        Mat o = ouverture (src_gray, element);
        Mat f = fermeture (src_gray, element);

        imshow( "Dilatation", d );
        imshow( "Erosion", e );
        imshow( "Ouverture", o );
        imshow( "Fermeture", f);
        waitKey(0);
    }
    // Exercise 3 : denoising
    if(exercise == 3) {
        Mat res = debruitage(src_gray, element);
        imshow( "Debruitage", res );
        waitKey(0);
    }
    // Exercise 4 : morphological gradients
    if(exercise == 4) {
        namedWindow( "Gradient interne", WINDOW_AUTOSIZE );
        namedWindow( "Gradient externe", WINDOW_AUTOSIZE );
        namedWindow( "Gradient morphologique", WINDOW_AUTOSIZE );
        
        Mat gi = gradientInterne (src_gray, element);
        Mat ge = gradientExterne (src_gray, element);
        Mat gm = gradientMorphologique (src_gray, element);

        imshow( "Gradient interne", gi );
        imshow( "Gradient externe", ge );
        imshow( "Gradient morphologique", gm );
        waitKey(0);
    }
    // Exercise 5 : morphologcial reconstruction
    if(exercise == 5) {
        printf("Sélectionnez les marqueurs en cliquant sur l'image originale, puis appuyez sur une touche\n");
        waitKey(0);
        Mat marqueursD = Mat(src.size(), CV_8U, Scalar(0));
        for (auto p : germes)
            circle(marqueursD,Point(p.x,p.y),3,Scalar(255),-1);
        Mat ri = reconstructionInferieure(src_gray, marqueursD, element);
        imshow( "Reconstruction Inferieure", ri );

        Mat marqueursE = src_gray.clone();
        int marge = 5;
        Rect roi(marge, marge, src_gray.cols - 2*marge, src_gray.rows - 2*marge);
        marqueursE(roi) = Scalar(255);
        Mat rs = reconstructionSuperieure(src_gray, marqueursE, element);
        imshow( "Reconstruction Superieure", rs );
        waitKey(0);
    }

    // Exercise 6: h-extrema
    if(exercise == 6) {
        Mat minR = minimaRegionaux(src_gray, element, 50);
        Mat srcCopy = src.clone();
        Mat redImg(srcCopy.size(), srcCopy.type(), Scalar(0,0,255));
        redImg.copyTo(srcCopy, minR);
        imshow( "Minima regionaux", srcCopy );

        Mat maxR = maximaRegionaux(src_gray, element, 50);
        srcCopy = src.clone();
        redImg.copyTo(srcCopy, maxR);
        imshow( "Maxima Regionaux", srcCopy );
        waitKey(0);
    }
   
    // Exercise 7: makers + watershed
    if(exercise == 7) {
        markers = marqueurs(src, src_gray, element, 5, 20);
        Mat markers_t;
        cv::normalize(markers, markers_t, 0, 255, cv::NORM_MINMAX);
        markers_t.convertTo(markers_t, CV_8U);
        imshow("Markers' image", markers_t);

        dst = ligneDePartageDesEaux(src, markers);
        imshow("Watershed Segmentation", dst);
        waitKey(0);
    }
    return 0;
}

static void onMouse(int event, int x, int y, int flags, void* data)  {
    if  ( event == EVENT_LBUTTONDOWN ) {
        germes.push_back(Point(x,y));
        circle(src,Point(x,y),3,Scalar(255,0,0),-1);
        imshow(window_org, src);
    }
}
