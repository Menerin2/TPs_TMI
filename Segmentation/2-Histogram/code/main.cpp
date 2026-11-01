/*!*
 * \file main.cpp
 * \brief TP2 sur la segmentation basée histogramme
 * \author : Phuc Ngo
 */

#include "functions.h"

string window1_name = "Image originale";
string window2_name = "Image convertie";
string window_res = "Image resultante";
int exercise = 1;

static void help(int argc, char** argv)
{
    cout<<"Usage: "<<argv[0]<<" [input.png] [numExo]\n";
}

int main( int argc, char** argv )
{
    help(argc, argv);
    string imageName("images/coins.png"); // by default
    if( argc > 1)
        imageName = argv[1];
    if( argc > 2)
        exercise = atoi(argv[2]);
    
    Mat image, gray, dst;
    image = imread(imageName.c_str(), IMREAD_COLOR); // Read the file
    if( image.empty() )                      // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    namedWindow( window1_name, WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( window1_name, image );                // Show our image inside it.
    
    cvtColor( image, gray, COLOR_BGR2GRAY );
    namedWindow( window2_name, WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( window2_name, gray );

    // Exercise 1 : theshold
    if(exercise == 1) {
        vector<int> thresh = {50, 100, 150};
        namedWindow( window_res, WINDOW_AUTOSIZE ); // Create a window for display.
        
        for(auto t : thresh) {
            dst = seuillage(gray, t);
            imshow( window_res, dst );
            waitKey(0); // Wait for a keystroke in the window
        }
    }
    // Exercise 2 : Hysteresis theshold
    if(exercise == 2) {
        int threshold_bas = 60;
        int threshold_haut = 98;
        dst = seuillageHysteresis(gray, threshold_bas, threshold_haut);
        imshow( window_res, dst );
        waitKey(0); // Wait for a keystroke in the window
    }
    // Exercise 3 : histogram 
    if(exercise == 3) {
        vector<int> intervalle = {1, 10, 20};
        for(auto itv : intervalle) {
            vector<int> h = histogramme(gray, itv);
            printf("Histogramme de %s avec un intervalle de %d est :\n", imageName.c_str(), itv); 
            printf("Valeur :");
            for(int i=0; i<h.size()-2; i++)
                printf("%d--%d \t", i*itv, (i+1)*itv-1);
            printf("%d--255 \n", ((int)h.size()-1)*itv);
            printf("Quantité :");
            for(int i=0; i<h.size(); i++)
                printf("%d \t", h.at(i));
            printf("\n");
        }
    }
    // Exercise 4: Otsu's method 
    if(exercise == 4) {
        int threshold = seuillageOtsu(gray) ;
        printf("Seuil de Otsu obtenue : %d\n", threshold);
        dst = seuillage(gray, threshold);
        imshow( window_res, dst );
        waitKey(0); // Wait for a keystroke in the window
    }
    // Exercise 5: kmean method 
    if(exercise == 5) {
        int k = 2;
        dst = kmean(gray, k);
        imshow( window_res, dst );
        waitKey(0); // Wait for a keystroke in the window
    }
   
    return 0;
}
