#include "cHistogram.h"



cHistogram::cHistogram()
{
	wczytany = false;
}

cHistogram::cHistogram(Mat img, bool czyBiale)
{
	
	int* tabR = new int[256];
	int* tabG = new int[256];
	int* tabB = new int[256];

	for (int i = 0; i < 256; i++)
	{
		tabR[i] = 0;
		tabG[i] = 0;
		tabB[i] = 0;
	}
	
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			Vec3b piksel = img.at<Vec3b>(i, j);
			if (czyBiale || piksel.val[0] != 255 || piksel.val[1] != 255 || piksel.val[2] != 255)
			{
				tabR[piksel.val[2]] += 1;
				tabG[piksel.val[1]] += 1;
				tabB[piksel.val[0]] += 1;
			}
		}
	}

	tab = new int*[3];
	tab[0] = tabR;
	tab[1] = tabG;
	tab[2] = tabB;

	wczytany = true;

}

cHistogram::~cHistogram()
{
	if (wczytany)
	{
		delete[] tab[0];
		delete[] tab[1];
		delete[] tab[2];
		delete[] tab;
	}
}

void cHistogram::Wywietl(string tytul)
{
	int wys = 560, szer = 800;
		Mat wykres (wys, szer, CV_8UC3, Scalar( 0,0,0) );
		int maxR=0;
		int maxB=0;
		int maxG=0;
		for (int i=0; i<256; i++)
		{
			if (maxR<tab[2][i]) maxR=tab[2][i];		
			if (maxG<tab[1][i]) maxG=tab[1][i];		
			if (maxB<tab[0][i]) maxB=tab[0][i];		
		}
		float wspolczynnikR = wys * (float) 0.95 /maxR;
		float wspolczynnikG = wys * (float) 0.95 /maxG;
		float wspolczynnikB = wys * (float) 0.95 /maxB;
		

		for (int i=0; i<256; i++)
		{
			tab[2][i] = (int) (tab[2][i] * wspolczynnikR);
			tab[1][i] = (int) (tab[1][i] * wspolczynnikG);
			tab[0][i] = (int) (tab[0][i] * wspolczynnikB);
		}

		float wspSzer = szer/ (float) 256;

		for (int i = 0; i < 255; i++)
		{
			Scalar kolorR = Scalar(0,0,255);
			Scalar kolorG = Scalar(0,255,0);
			Scalar kolorB = Scalar(255,0,0);

			int y1r = tab[2][i] + 5;
			int y2r = tab[2][i + 1] + 5;
			int y1g = tab[1][i] + 5;
			int y2g = tab[1][i + 1] + 5;
			int y1b = tab[0][i] + 5;
			int y2b = tab[0][i + 1] + 5;

			
			if (y1r==y1b) 
			{
				kolorR += kolorB;
				kolorB = Scalar ( 255, 0, 255);
			}

			if (y1r==y1g) 
			{
				kolorR += kolorG;
				kolorG = Scalar(0, 255, 255);
			}	
			if (y1g==y1b) 
			{
				kolorG += kolorB;
				kolorB = Scalar (255, 255, 0);
			}

			if (y1r==y1b && y1b == y1g) kolorB = Scalar (255, 255, 255);

			line (wykres, Point (int (i*wspSzer), wys - y1r), Point (int ((i + 1)*wspSzer), wys - y2r), kolorR,1);
			line (wykres, Point (int (i*wspSzer), wys - y1g), Point (int ((i + 1)*wspSzer), wys - y2g), kolorG, 1);
			line (wykres, Point (int (i*wspSzer), wys - y1b), Point (int ((i + 1)*wspSzer), wys - y2b), kolorB, 1);
		}
		imshow(tytul, wykres);
}

int** cHistogram::Tablica()
{
	return tab;
}