/*!*
 * \file functions.h
 * \brief TP4 sur la segmentation basée contour
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
 * \fn Mat elementStruturant(String name)
 * \brief Function to define diffferent structuring element
 * \param taille the size structuring element : 1 -> 3x3, 2 -> 5x5, ...
 * \param nom the name of the structuring element : carree, disque, croix, hligne, vlinge
 * \param (adj4 = croix et adj8 = carre)
 * \return the structuring element
 */
Mat elementStruturant(int taille, String type) ;

/**
 * \fn Mat dilatation(const Mat& src, const Mat& se)
 * \brief Dilation function
 * \param src the input image
 * \param se the structuring element
 * \return the resulting image
 */
Mat dilatation(const Mat& src, const Mat& se) ;

/**
 * \fn Mat erosion(const Mat& src, const Mat& se)
 * \brief Erosion function
 * \param src the input image
 * \param se the structuring element
 * \return the resulting image
 */
Mat erosion(const Mat& src, const Mat& se) ;

/**
 * \fn Mat ouverture(const Mat& src, const Mat& se)
 * \brief Openning function
 * \param src the input image
 * \param se the structuring element
 * \return the resulting image
 */
Mat ouverture(const Mat& src, const Mat& se) ;

/**
 * \fn Mat fermeture(const Mat& src, const Mat& se)
 * \brief Closing function
 * \param src the input image
 * \param se the structuring element
 * \return the resulting image
 */
Mat fermeture(const Mat& src, const Mat& se) ;

/**
 * \fn Mat fermeture(const Mat& src, const Mat& se)
 * \brief Denoising function using morphological operators
 * \param src the input image
 * \param se the structuring element
 * \return the resulting image
 */
Mat debruitage(const Mat& src, const Mat& se) ;

/**
 * \fn Mat fermeture(const Mat& src, const Mat& se)
 * \brief Top-hat gradient
 * \param src the input image
 * \param se the structuring element
 * \return the resulting image
 */
Mat gradientInterne(const Mat& src, const Mat& se) ;

/**
 * \fn Mat fermeture(const Mat& src, const Mat& se)
 * \brief Black-hat gradient
 * \param src the input image
 * \param se the structuring element
 * \return the resulting image
 */
Mat gradientExterne(const Mat& src, const Mat& se) ;

/**
 * \fn Mat fermeture(const Mat& src, const Mat& se)
 * \brief Morphological gradient
 * \param src the input image
 * \param se the structuring element
 * \return the resulting image
 */
Mat gradientMorphologique(const Mat& src, const Mat& se) ;

/**
 * \fn Mat reconstructionInferieure(const Mat& src, const Mat& mrk, const Mat& se, int maxIter = 1000) 
 * \brief Morphological reconstruction by dilation
 * \param src the input (mask) image
 * \param mrk the markers image
 * \param se the structuring element
 * \param maxIter the maximal number of iteration or stop when it stablizes
 * \return the resulting image
 */
Mat reconstructionInferieure(const Mat& src, const Mat& mrk, const Mat& se, int maxIter = 1000) ;

/**
 * \fn Mat reconstructionSuperieure(const Mat& src, const Mat& mrk, const Mat& se, int maxIter = 1000) 
 * \brief Morphological reconstruction by erosion
 * \param src the input (mask) image
 * \param mrk the markers image
 * \param se the structuring element
 * \param maxIter the maximal number of iteration or stop when it stablizes
 * \return the resulting image
 */
Mat reconstructionSuperieure(const Mat& src, const Mat& mrk, const Mat& se, int maxIter = 1000) ;

/**
 * \fn Mat maximaRegionaux(const Mat& img, const Mat& se, int h = 1) 
 * \brief h-maxima transform
 * \param src the input (mask) image
 * \param se the structuring element
 * \param h the ampplitude of the maxima
 * \return the resulting image
 */
Mat maximaRegionaux(const Mat& src, const Mat& se, int h = 1) ;

/**
 * \fn Mat minimaRegionaux(const Mat& img, const Mat& se, int h = 1) 
 * \brief h-minima transform
 * \param src the input (mask) image
 * \param se the structuring element
 * \param h the ampplitude of the minima
 * \return the resulting image
 */
Mat minimaRegionaux(const Mat& src, const Mat& se, int h = 1) ;

/**
 * \fn Mat marqueurs(const Mat& src, const Mat& src_gray, const Mat& se, int gSize = 5, int h = 1)
 * \brief marker image for watershed algorithm
 * \param src the input (3 chanels - RGB) image
 * \param src_gray the gray input image
 * \param se the structuring element
 * \param gSize the size of gaussian kernel
 * \param h the ampplitude of the regional minima 
 * \return the resulting maker image
 */
Mat marqueurs(const Mat& src, const Mat& src_gray, const Mat& se, int gSize = 5, int h = 1) ;

/**
 * \fn Mat ligneDePartageDesEaux(const Mat& src, const Mat& marqueurImage)
 * \brief Wathershed algorithm
 * \param src the input (3 chanels - RGB) image
 * \param marqueurImage the marker image
 * \return the resulting image
 */
Mat ligneDePartageDesEaux(const Mat& src, const Mat& marqueurImage) ;

#endif // FUNCTIONS_H