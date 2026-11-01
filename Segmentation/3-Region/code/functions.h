/*!*
 * \file functions.h
 * \brief TP3 sur la segmentation basée région
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
 * \fn vector<Point> voisins(Point g)
 * \brief Function for getting the 4 neighbours of a point
 * \param p the input point
 * \param adjacence the adjacency of the neigoubours (either 4 ou 8)
 * \return a vector of neighbouring points of p
 */
vector<Point> voisins(Point p, int adjacence = 4) ;

/**
 * \fn bool predicat1(const Mat& img, Point g, Point p, int seuil) 
 * \brief Function of predicat (intensity) for the region growing algorithm
 * \brief predicat : |I[p] - I[g]| < seuil
 * \param src the input image
 * \param g the grain (of the region)
 * \param p the current point to compare with g
 * \param seuil the threshold
 * \return a boolean indicating if the result of the predicat
 */
bool predicat1(const Mat& src, Point g, Point p, int seuil) ;

/**
 * \fn bool predicat2(const Mat& img, const vector<Point>& Ri, Point p, int seuil) 
 * \brief Function of predicat (different intensity) for the region growing algorithm
 * \brief predicat : |I[p] - mean(Ri)| < seuil
 * \param src the input image
 * \param Ri vector of points belonging to the region Ri
 * \param p the current point to compare with g
 * \param seuil the threshold
 * \return a boolean indicating if the result of the predicat
 */
bool predicat2(const Mat& src, const vector<Point>& Ri, Point p, int seuil) ;

/**
 * \fn bool predicat2(const Mat& img, const vector<Point>& Ri, Point p, int seuil) 
 * \brief Function of predicat (intra-region variance) for the region growing algorithm
 * \brief predicat : |I[p] - mean(Ri)| < seuil
 * \param src the input image
 * \param Ri vector of points belonging to the region Ri
 * \param p the current point to compare with g
 * \param seuil the threshold
 * \return a boolean indicating if the result of the predicat
 */
bool predicat3(const Mat& src, const vector<Point>& Ri, Point p, int seuil) ;

/**
 * \fn Mat croissanceRegion(const Mat& src, const vector<Point>& germes, int seuil, int methode)
 * \brief The region growing algorithm
 * \param src the input image
 * \param germes the vector of grains for the region growing
 * \param seuil the threshold for the predicat
 * \param predicat the predicat used for the algorithm (1 -> predicat1, 2 -> predicat2 and 3 -> predicat3)
 */
Mat croissanceRegion(const Mat& src, const vector<Point>& germes, int seuil, int predicat=1) ;

#endif // FUNCTIONS_H