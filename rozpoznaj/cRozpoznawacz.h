#ifndef ROZPOZNAWACZ_H
#define ROZPOZNAWACZ_H

#define _PROG_KOLORU 0.7



#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include "cHistogram.h"
#include "lokalizacja.h"

using namespace cv;


struct KOLOR
{
	int sredniaR;
	int rR;
	int sredniaG;
	int rG;
	int sredniaB;
	int rB;
	float promien2;
};



class cRozpoznawacz
{
private:
	Mat wczytany;
	Mat obraz;
	Mat red;
	Mat blue;
	Mat yellow;
	Mat black;

	KOLOR czerwony;
	KOLOR niebieski;
	KOLOR czarny;
	KOLOR zolty;

public:
	cRozpoznawacz();
	cRozpoznawacz(string adresZdjecia);
	~cRozpoznawacz();
	KOLOR OkreslKolor(int** tab);
	void Rozdziel();
};




#endif