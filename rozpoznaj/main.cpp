#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "cHistogram.h"
#include "cRozpoznawacz.h"
#include "lokalizacja.h"


using namespace cv;
using namespace std;





int main( int argc, char** argv )
{
	

	/*Mat obrazek = imread(_CZARNY);
	cHistogram histo(obrazek, false);
	histo.Wywietl("podpis");*/

	string adresik = _ZDJECIE;
	cRozpoznawacz nowy(adresik);


	waitKey(0);
	system("pause");
    return 0;
}
