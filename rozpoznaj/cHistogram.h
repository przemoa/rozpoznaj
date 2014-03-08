#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>


using namespace cv;


class cHistogram
{
private:
	bool wczytany;
	int** tab;


public:
	cHistogram();
	cHistogram(Mat img, bool czyBiale = true);				// tworzy histogram z Mat, czy Zliczac biale piksele
	~cHistogram();
	void Wywietl(string tytul);			// wyswietla histogram w oknie o nazwie tytul
	int** Tablica();
};




#endif