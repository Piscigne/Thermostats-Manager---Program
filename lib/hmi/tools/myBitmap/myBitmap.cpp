#include "tools/myBitmap/myBitmap.hpp"

extern TFT_eSPI* pTft;

void myBitmap::drawARRAY(int32_t x, int32_t y, const BITMAP* img)
{
	pTft->pushImage(x, y, img->width, img->height, img->data, TFT_BLACK);
}

void myBitmap::drawARRAYbutton(int32_t x, int32_t y, ICON_BOOL* img, bool state)
{
	if(state)	pTft->pushImage(x, y, img->IconON->width,  img->IconON->height,  img->IconON->data,  TFT_BLACK);
	else		pTft->pushImage(x, y, img->IconOFF->width, img->IconOFF->height, img->IconOFF->data, TFT_BLACK);
}

void myBitmap::drawARRAYlist(int32_t x, int32_t y, ICON_LIST* img, int8_t index)
{
	if(index < img->Nbr)
	{
		pTft->pushImage(x, y, img->Icons[index]->width, img->Icons[index]->height, img->Icons[index]->data, TFT_BLACK);
	}
}
