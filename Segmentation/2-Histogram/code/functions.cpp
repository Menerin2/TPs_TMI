/*!*
 * \file function.cpp
 * \brief TP2 sur la segmentation basée histogramme
 * \author : Phuc Ngo
 */

#include "functions.h"

Mat seuillage(const Mat& image, int seuil) {
	Mat res = Mat(image.size(), CV_8U, Scalar(0,0,0));
	//code goes here...
	for(int x=0; x<image.cols; x++){
		for(int y=0; y<image.rows; y++){
			int intensity = image.at<uchar>(y,x);
			res.at<uchar>(y,x) = (intensity < seuil) ? 0:255;
		}
	}
	return res;
}

Mat seuillageHysteresis(const Mat& image, int seuil_bas, int seuil_haut) {
	Mat res = Mat(image.size(), CV_8U, Scalar(0,0,0));
	//code goes here...
	int* connexity = new int[4];
	for(int x=0; x<image.cols; x++){
		for(int y=0; y<image.rows; y++){
			int intensity = image.at<uchar>(y,x);
			int newIntensity = 0;
			if(seuil_haut < intensity){
				newIntensity = 255;
			}else{
				if(seuil_bas < intensity){
					connexity[0]=image.at<uchar>(y,x+1);
					connexity[1]=image.at<uchar>(y,x-1);
					connexity[2]=image.at<uchar>(y+1,x);
					connexity[3]=image.at<uchar>(y-1,x);
					if(connexity[0]>seuil_haut ||
						connexity[1]>seuil_haut ||
						connexity[2]>seuil_haut ||
						connexity[3]>seuil_haut){
							newIntensity = 255;
						}
				}
			}
			res.at<uchar>(y,x) = newIntensity;
		}
	}
	return res;
}

vector<int> histogramme(const Mat& image, int intervalle) {
	//code goes here...
	vector<int> histo (255/intervalle + 1, 0);
	for(int x=0; x<image.cols; x++){
		for(int y=0; y<image.rows; y++){
			int intensity = image.at<uchar>(y,x);
			histo[intensity/intervalle] = histo[intensity/intervalle] + 1;
		}
	}
	return histo;
}

double calculeVariance(const vector<int>& histo, int seuil, int nbPixels) {
	//code goes here...
	double weightc1 = 0.0;
	int nbPixelsc1 = 0;
	for (int i =0; i<=seuil; i++){
		weightc1 += (double)histo[i];
		nbPixelsc1 += histo[i];
	}
	weightc1 = weightc1/nbPixels;
	double weightc2 = 1-weightc1;
	int nbPixelsc2 = nbPixels - nbPixelsc1;

	double meanc1 = 0.0;
	double meanc2 = 0.0;
	for (int j=0; j<=seuil; j++){
		meanc1 += j * (double)histo[j];
	}
	meanc1 = meanc1/nbPixelsc1;
	for (int j = seuil+1; j<histo.size(); j++){
		meanc2 += j * (double)histo[j];
	}
	meanc2 = meanc2/nbPixelsc2;

	double varc1 = 0.0;
	double varc2 = 0.0;
	for (int j=0; j<=seuil; j++){
		double temp = j-meanc1;
		varc1 += (temp*temp)*(double)histo[j];
	}
	varc1 = varc1/nbPixelsc1;
	for (int j = seuil+1; j<histo.size(); j++){
		double temp = j-meanc2;
		varc2 += (temp*temp)*(double)histo[j];
	}
	varc2 = varc2/nbPixelsc2;

	return weightc1*varc1 + weightc2*varc2;
}

int seuillageOtsu(const Mat& image) {
	//code goes here...
	vector<int> histo = histogramme(image, 1);
	int nbPixels = image.rows * image.cols;
	double variance = DBL_MAX;
	int bestSeuil = 0;
	double minVariance = variance;
	for (int seuil = 0; seuil<histo.size(); seuil++){
		variance = calculeVariance(histo, seuil, nbPixels);
		if (variance == NAN){
			continue;
		}
		if (variance < minVariance){
			minVariance = variance;
			bestSeuil = seuil;
		}
	}
	return bestSeuil;
}

Mat kmean(const Mat& image, int k) {
	//code goes here...
	vector<int> histo = histogramme(image, 1);
	int* centers = new int[k];
	for (int i=0; i<k; i++){
		centers[i] = (i+1) * (histo.size()/(k+1));
	}
	int* newCenters = new int[k];
	do{
		newCenters = centers;
		for (int i=0; i<k; i++){
			int sum = 0;
			int count = 0;
			int start = (i==0) ? 0:centers[i-1]+(centers[i]-centers[i-1])/2;
			int end = (i==k-1) ? histo.size()-1:centers[i]+(centers[i+1]-centers[i])/2+1;
			for (int j=start; j<=end; j++){
				sum += j*histo[j];
				count += histo[j];
			}
			newCenters[i] = (int)sum/count;
		}
	}while(newCenters != centers);

	for (int i=0; i<k; i++){
		cout << "c" << i << " : " << centers[i] << endl;
	}

	Mat res = Mat(image.size(), CV_8U, Scalar(0, 0, 0));
	for (int x=0; x<image.cols; x++){
		for (int y=0; y<image.rows; y++){
			int intensity = image.at<u_char>(y,x);
			for (int i=0; i<k; i++){
				int thresholdDown = (i==0) ? 0:(centers[i-1]+centers[i]/2);
				int thresholdUp = (i==k-1) ? 255:(centers[i]+centers[i+1]/2);
				if (intensity>=thresholdDown && intensity <= thresholdUp){
					res.at<u_char>(y,x) = (i * (255/k-1));
				}
			}
		}
	}

	return res;
}