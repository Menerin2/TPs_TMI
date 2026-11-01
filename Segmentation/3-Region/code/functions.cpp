/*!*
 * \file functions.cpp
 * \brief TP3 sur la segmentation basée région
 * \author : Phuc Ngo
 */

#include "functions.h"

vector<Point> voisins(Point p, int adjacence) {
	vector<Point> vp;
	//code goes here...
	for(int i=-1; i<2; i++){
		for(int j=-1; j<2; j++){
			vp.push_back(Point(p.x+i, p.y+j));
		}
	}
	return vp;
}

bool predicat1(const Mat& src, Point g, Point p, int seuil) {
	//code goes here...
	int intensity_g = src.at<uchar>(g.y, g.x);
	int intensity_p = src.at<uchar>(p.y, p.x);

	return abs(intensity_p-intensity_g)<seuil;
}

bool predicat2(const Mat& src, const vector<Point>& Ri, Point p, int seuil) {
	//code goes here...
	int intensity_p = src.at<uchar>(p.y, p.x);
	int intensity_Ri = 0;
	for(int i=0; i<Ri.size(); i++){
		intensity_Ri += src.at<uchar>(Ri[i].y, Ri[i].x);
	}
	intensity_Ri /= Ri.size();

	return abs(intensity_p-intensity_Ri)<seuil;
}

bool predicat3(const Mat& src, const vector<Point>& Ri, Point p, int seuil) {
	//code goes here...

	return true;
}

Mat croissanceRegion(const Mat& src, const vector<Point>& germes, int seuil, int predicat)  {
	Mat dst = Mat(src.size(), CV_8U, Scalar(0,0,0));
	//code goes here...
	int label = 5; //Je commence avec un label de 5 pour mieux distinguer les régions du fond
	int adjacent = 8;
	vector<Point> S;
	vector<Point> Ri;
	Point p;
	bool res_predicat;
	for(Point germe:germes){
		dst.at<uchar>(germe.y, germe.x) = 10*label;
		S = voisins(germe, adjacent);
		Ri.push_back(germe);
		while (!S.empty()){
			p = S[S.size()-1];
			S.pop_back();
			switch (predicat){
			case 1:
				res_predicat = predicat1(src, germe, p, seuil);
				break;
			case 2:
				res_predicat = predicat2(src, Ri, p, seuil);
				break;
			case 3:
				res_predicat = predicat3(src, Ri, p, seuil);
				break;
			default:
				break;
			}
			if(dst.at<uchar>(p.y, p.x)==0 && res_predicat){
				dst.at<uchar>(p.y, p.x) = 10*label;
				for(Point voisin:voisins(p, adjacent)){
					S.push_back(voisin);
				}
				Ri.push_back(p);
			}
		}
		label += 1;
		Ri.clear();
	}
	return dst;
}
