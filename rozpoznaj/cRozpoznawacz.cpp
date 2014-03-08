#include "cRozpoznawacz.h"

cRozpoznawacz::cRozpoznawacz()
{

}

cRozpoznawacz::~cRozpoznawacz()
{

}

cRozpoznawacz::cRozpoznawacz(string adresZdjecia)
{
	wczytany = imread(adresZdjecia);
	bilateralFilter(wczytany, obraz, 6, 20, 5);
	
	cHistogram histCzerwonego(imread(_CZERWONY));
	czerwony = OkreslKolor(histCzerwonego.Tablica());

	cHistogram histNiebieskiego(imread(_NIEBIESKI));
	niebieski = OkreslKolor(histNiebieskiego.Tablica());

	cHistogram histZoltego(imread(_ZOLTY));
	zolty = OkreslKolor(histZoltego.Tablica());

	cHistogram histCzarnego(imread(_CZARNY));
	czarny = OkreslKolor(histCzarnego.Tablica());


	Rozdziel();
	imshow("1", red);
	imshow("2", blue);
	imshow("3", yellow);
	imshow("4", black);
	imshow("0", obraz);
}

KOLOR cRozpoznawacz::OkreslKolor(int** tab)
{
	int maxR=0;
	int maxB=0;
	int maxG=0;
	KOLOR kolor;

	for (int i=0; i<256; i++)
	{
		if (maxR < tab[2][i]) maxR=tab[2][i];		
		if (maxG < tab[1][i]) maxG=tab[1][i];		
		if (maxB < tab[0][i]) maxB=tab[0][i];		
	}

	maxR *= _PROG_KOLORU / 100.0;
	maxG *= _PROG_KOLORU / 100.0;
	maxB *= _PROG_KOLORU / 100.0;

	int sumaR = 0, iloscR = 0, sumaG = 0, iloscG = 0, sumaB = 0, iloscB = 0;
	for (int i = 0; i < 255; i++)
	{
		if (maxR <= tab[2][i]) 
		{
			sumaR += i;
			iloscR++;
		}
		if (maxG <= tab[1][i])
		{
			sumaG += i;
			iloscG++;
		}
		if (maxB <= tab[0][i])
		{
			sumaB += i;
			iloscB++;
		}
	}

	kolor.sredniaB = sumaR / iloscR;
	kolor.rB = iloscR/2;

	kolor.sredniaG = sumaG / iloscG;
	kolor.rG = iloscG/2;

	kolor.sredniaR = sumaB / iloscB;
	kolor.rR = iloscB/2;
	std::cout << kolor.sredniaR << "+-" << kolor.rR << "  " << kolor.sredniaG << " +- " << kolor.rG << "  " << kolor.sredniaB << " +- " << kolor.rB << std::endl;
	kolor.promien2 = pow(kolor.rR, 2.0) + pow(kolor.rG, 2.0) + pow(kolor.rB, 2.0);

	return kolor;
}


void cRozpoznawacz::Rozdziel()
{
	red = Mat (obraz.rows, obraz.cols, CV_8UC3, Scalar(255,255,255) );
	blue = Mat (obraz.rows, obraz.cols, CV_8UC3, Scalar(255,255,255) );
	black = Mat (obraz.rows, obraz.cols, CV_8UC3, Scalar(255,255,255) );
	yellow = Mat (obraz.rows, obraz.cols, CV_8UC3, Scalar(255,255,255) );

	for (int w = 0; w < obraz.rows; w++)
	{
		for (int k = 0; k < obraz.cols; k++)
		{
			Vec3b piksel = obraz.at<Vec3b>(w, k);


			float odlCzer = pow(piksel.val[2] - czerwony.sredniaR, 2.0) + pow(piksel.val[1] - czerwony.sredniaG, 2.0) + pow(piksel.val[0] - czerwony.sredniaB, 2.0);
			float odlNieb = pow(piksel.val[2] - niebieski.sredniaR, 2.0) + pow(piksel.val[1] - niebieski.sredniaG, 2.0) + pow(piksel.val[0] - niebieski.sredniaB, 2.0);
			float odlZolt = pow(piksel.val[2] - zolty.sredniaR, 2.0) + pow(piksel.val[1] - zolty.sredniaG, 2.0) + pow(piksel.val[0] - zolty.sredniaB, 2.0);
			float odlCzar = pow(piksel.val[2] - czarny.sredniaR, 2.0) + pow(piksel.val[1] - czarny.sredniaG, 2.0) + pow(piksel.val[0] - czarny.sredniaB, 2.0);
			
			
			if (odlCzer < odlNieb && odlCzer < odlZolt && odlCzer < odlCzar && odlCzer < czerwony.promien2) 
			{
				red.at<Vec3b>(w, k) = piksel;
			}

			else if (odlNieb < odlZolt && odlNieb < odlCzar && odlNieb < niebieski.promien2) 
			{
				blue.at<Vec3b>(w, k) = piksel;
			}

			else if (odlZolt < odlCzar && odlZolt < zolty.promien2) 
			{
				yellow.at<Vec3b>(w, k) = piksel;
			}
		
			else if (odlCzar < czarny.promien2) 
			{
				black.at<Vec3b>(w, k) = piksel;
			}

		}
	}
}