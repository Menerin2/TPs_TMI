/*!*
 * \file functions.cpp
 * \brief TP4 sur la segmentation basée contour
 * \author : Phuc Ngo
 */

#include "functions.h"

Mat elementStruturant(int taille, String type) {
	Mat se;
	//code goes here...
	if(type == "carre"){
		se = Mat(taille*2+1, taille*2+1, CV_8U, Scalar(1));
	}
	else if(type == "disque"){
		se = Mat(taille*2+1, taille*2+1, CV_8U, Scalar(1));
		int radius = (taille*2+1) / 2;
		for(int i=0; i<taille*2+1; i++){
			for(int j=0; j<taille*2+1; j++){
				if( (i - radius)*(i - radius) + (j - radius)*(j - radius) > radius*radius ){
					se.at<uchar>(i,j) = 0;
				}	
			}
		}
	}
	else if(type == "croix"){
		se = Mat(taille*2+1, taille*2+1, CV_8U, Scalar(0));
		for(int i=0; i<taille*2+1; i++){
			se.at<uchar>(taille, i) = 1;
			se.at<uchar>(i, taille) = 1;
		}
	}
	else if(type == "hligne"){
		se = Mat(taille*2+1, taille*2+1, CV_8U, Scalar(0));
		for(int i=0; i<taille*2+1; i++){
			se.at<uchar>(taille, i) = 1;
		}
	}
	else if(type == "vligne"){
		se = Mat(taille*2+1, taille*2+1, CV_8U, Scalar(0));
		for(int i=0; i<taille*2+1; i++){
			se.at<uchar>(i, taille) = 1;
		}
	}
	return se;
}

Mat dilatation(const Mat& src, const Mat& se)  {
	Mat dst = Mat(src.size(), src.type(), Scalar(0));
	//code goes here...
	for(int i=0; i<src.rows; i++){
		for(int j=0; j<src.cols; j++){
			uchar max = src.at<uchar>(i,j);
			for(int m=0; m<se.rows; m++){
				for(int n=0; n<se.cols; n++){
					if(se.at<uchar>(m,n) == 1){
						int x = i+m-int(se.rows/2);
						int y = j+n-int(se.cols/2);
						if(x >= 0 && x < src.rows && y >= 0 && y < src.cols){
							if(src.at<uchar>(x,y) > max){
								max = src.at<uchar>(x,y);
							}
						}
					}
				}
			}
			dst.at<uchar>(i,j) = max;
		}
	}

	return dst;
}

Mat erosion(const Mat& src, const Mat& se)  {
	Mat dst = Mat(src.size(), src.type(), Scalar(0));
	//code goes here...
	for(int i=0; i<src.rows; i++){
		for(int j=0; j<src.cols; j++){
			uchar min = src.at<uchar>(i,j);
			for(int m=0; m<se.rows; m++){
				for(int n=0; n<se.cols; n++){
					if(se.at<uchar>(m,n) == 1){
						int x = i+m-int(se.rows/2);
						int y = j+n-int(se.cols/2);
						if(x >= 0 && x < src.rows && y >= 0 && y < src.cols){
							if(src.at<uchar>(x,y) < min){
								min = src.at<uchar>(x,y);
							}
						}
					}
				}
			}
			dst.at<uchar>(i,j) = min;
		}
	}
	return dst;
}

Mat fermeture(const Mat& src, const Mat& se)  {
	//code goes here...
	Mat dst;
	dst = dilatation(src, se);
	dst = erosion(dst, se);
	return dst;
}

Mat ouverture(const Mat& src, const Mat& se)  {
	//code goes here...
	Mat dst;
	dst = erosion(src, se);
	dst = dilatation(dst, se);
	return dst;
}

Mat debruitage(const Mat& src, const Mat& se)  {
	//code goes here...
	Mat dst;
	dst = ouverture(src, se);
	dst = fermeture(dst, se);
	return dst;
}

Mat gradientInterne(const Mat& src, const Mat& se)  {
	//code goes here...
	Mat dst;
	dst = erosion(src, se);
	dst = src - dst;
	return dst;
}

Mat gradientExterne(const Mat& src, const Mat& se)  {
	//code goes here...
	Mat dst;
	dst = dilatation(src, se);
	dst = dst - src;
	return dst;
}

Mat gradientMorphologique(const Mat& src, const Mat& se)  {
	//code goes here...
	Mat dil = dilatation(src, se);
	Mat ero = erosion(src, se);
	Mat dst = dil - ero;
	return dst;
}


Mat reconstructionInferieure(const Mat& src, const Mat& mrk, const Mat& se, int maxIter) {
	//code goes here...
	Mat dil = mrk.clone();
	Mat newDil;
	Mat diff;
	while (maxIter--){
		newDil = dilatation(dil, se);
		newDil = min(newDil, src);
		compare(newDil, dil, diff, CMP_NE);
		if (countNonZero(diff) == 0){
			break;
		}
		dil = newDil;
	}
	return dil;
}

Mat reconstructionSuperieure(const Mat& src, const Mat& mrk, const Mat& se, int maxIter) {
	//code goes here...
	Mat dil = mrk.clone();
	Mat newDil;
	Mat diff;
	while (maxIter--){
		newDil = erosion(dil, se);
		newDil = max(newDil, src);
		compare(newDil, dil, diff, CMP_NE);
		if (countNonZero(diff) == 0){
			break;
		}
		dil = newDil;
	}
	return dil;
}

Mat maximaRegionaux(const Mat& src, const Mat& se, int h) {
	//code goes here...
	Mat dst;
	dst = src - h;
	dst = reconstructionInferieure(src, dst, se);
	dst = src - dst;
	return dst;
}

Mat minimaRegionaux(const Mat& src, const Mat& se, int h) {
	//code goes here...
	Mat dst;
	dst = src + h;
	dst = reconstructionSuperieure(src, dst, se);
	dst = dst - src;
	return dst;
}

Mat marqueurs(const Mat& src, const Mat& src_gray, const Mat& se, int gSize, int h) {
	Mat marqueurImage = Mat(src_gray.size(), CV_32S, Scalar(0,0,0));
	//code goes here...
	Mat dst;
	Mat gradientMorph;
	Mat bassinsGrad;
	GaussianBlur(src_gray, dst, Size(se.rows, se.cols), 0, 0);
	gradientMorph = gradientMorphologique(dst, se);
	bassinsGrad = minimaRegionaux(gradientMorph, se, h);
	std::vector<std::vector<Point>> contours;
	findContours(bassinsGrad, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for(int i=0; i<contours.size(); i++){
		drawContours(marqueurImage, contours, i, Scalar(255));
	}
	return marqueurImage;
}

Mat ligneDePartageDesEaux(const Mat& src, const Mat& marqueurImage) {
	Mat dst = Mat::zeros(src.size(), CV_8UC3);
	//code goes here...
	// Manque la conversion de marqueurImage en CV_8UC3
	cv::watershed(src, marqueurImage);
	for(int i=0; i<src.rows; i++){
		for(int j=0; j<src.cols; j++){
			if(marqueurImage.at<int>(i,j) == -1){
				dst.at<Vec3b>(i,j) = Vec3b(0,0,255);
			}
			else if(marqueurImage.at<int>(i,j) > 0){
				dst.at<Vec3b>(i,j) = src.at<Vec3b>(i,j);
			}
		}	
	}
	return dst;
}
