/*!*
 * \file functions.h
 * \brief TP2 sur la segmentation basée histogramme
 * \author : Phuc Ngo
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

/**
 * \fn Mat seuillage(const Mat& src, int seuil) 
 * \brief Function to threshold a grey image
 * \param src the input image to threshod
 * \param seuil the threshold
 * \return the thresholded image
 */
Mat seuillage(const Mat& image, int seuil) ;

/**
 * \fn Mat seuillageHysteresis(const Mat& src, int seuil_bas, int seuil_haut)
 * \brief Function for hysterisis threshold
 * \param src the input image to threshod
 * \param seuil_bas the low threshold
 * \param seuil_haut the high threshold
 * \return the thresholded image
 */
Mat seuillageHysteresis(const Mat& image, int seuil_bas, int seuil_haut) ;

/**
 * \fn vector<int> vector<int> histogramme(const Mat& image, int intervalle = 1) 
 * \brief Function to compute the histogram of a grey image
 * \param image the input image
 * \param intervalle the histrogram's step, default = 1 
 * \return the vector containing the histogram's values
 */
vector<int> histogramme(const Mat& image, int intervalle = 1) ;

/**
 * \fn double calculeVariance(const vector<int>& histo, int seuil)
 * \brief Function to compute the intra-classe variance of an image (using its histogram) 
 * at a given threshold value
 * \param histo the histogram
 * \param seuil the threshold value at which we compute the variance (see course's slide)
 * \param nbPixels the total number of pixels in the image
 * \return the vector containing the histogram's values
 */
double calculeVariance(const vector<int>& histo, int seuil, int nbPixels) ;

/**
 * \fn int seuillageOtsu(const Mat& image)
 * \brief Ostu's Method : find the optimal threshold with max intra-classe variance
 * using calculeVariance function (see course's slide) 
 * \param image the input image
 * \return the Otsu's threshold value
 */
int seuillageOtsu(const Mat& image) ;

/**
 * \fn Mat kmean(const Mat& image, int k = 2)
 * \brief Method k-mean for a grey image
 * \param histo the histogram
 * \param k the number of classes, default = 2 (2 classes: object + background) 
 * \return the segmented image
 */
Mat kmean(const Mat& image, int k = 2) ;


#endif // FUNCTIONS_H