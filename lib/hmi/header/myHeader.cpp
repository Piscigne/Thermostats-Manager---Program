#include "header/myHeader.hpp"

#include "resources/bitmap/header/lock/LockON.h"
#include "resources/bitmap/header/lock/LockOFF.h"

#include "resources/bitmap/header/wifi/wifi_0.h"
#include "resources/bitmap/header/wifi/wifi_1.h"
#include "resources/bitmap/header/wifi/wifi_2.h"
#include "resources/bitmap/header/wifi/wifi_3.h"
#include "resources/bitmap/header/wifi/wifi_4.h"
#include "resources/bitmap/header/wifi/wifiOFF.h"
#include "resources/bitmap/header/wifi/wifiERR.h"

extern TFT_eSPI* pTft;
extern THM		 ThmUnit;

myHeader::myHeader(int32_t top)
{
	Top = top;
	int8_t Nbr = 0;

	icoWifi.Icons[Nbr++] = &wifi_0;
	icoWifi.Icons[Nbr++] = &wifi_1;
	icoWifi.Icons[Nbr++] = &wifi_2;
	icoWifi.Icons[Nbr++] = &wifi_3;
	icoWifi.Icons[Nbr++] = &wifi_4;
	icoWifi.Icons[Nbr++] = &wifiOFF;
	icoWifi.Icons[Nbr++] = &wifiERR;
	icoWifi.Nbr = Nbr;

	icoLock.IconON  = &lockON;
	icoLock.IconOFF = &lockOFF;

	pBmap = new myBitmap();
}

void myHeader::init(void)
{
	redraw();
}

void myHeader::dispLock(void)
{
		pBmap->drawARRAYbutton(HEAD_ICO_LOCK_X, Top+HEAD_ICO_LOCK_Y, &icoLock, ThmUnit.Locked);
		LockActif = ThmUnit.Locked;
}

void myHeader::dispExtT(void)
{
		char TxtBuff[HEAD_TXT_TEMP_B];
		sprintf(TxtBuff, TempTxt, ThmUnit.TempExtern);
		pTft->setTextDatum(TXT_TOP_CENTER);
		pTft->setTextColor(TFT_GREEN, TFT_BLACK, true);
		pTft->drawString(TxtBuff, HEAD_TXT_TEMP_C, Top+HEAD_TXT_TEMP_Y, HEAD_TXT_TEMP_F);
		TempActif = ThmUnit.TempExtern;
		dispMinMax();
}

void myHeader::dispMinMax(void)
{
		char TxtBuff[HEAD_TXT_MINMAX_B];
		sprintf(TxtBuff, TempMinMax, ThmUnit.TempExtMin, ThmUnit.TempExtMax);
		pTft->setTextDatum(TXT_TOP_CENTER);
		pTft->setTextColor(TFT_DARKGREY, TFT_BLACK, true);
		pTft->drawString(TxtBuff, HEAD_TXT_MINMAX_C, Top+HEAD_TXT_MINMAX_Y, HEAD_TXT_MINMAX_F);
		MaxActif = ThmUnit.TempExtMax;
		MinActif = ThmUnit.TempExtMin;
}

void myHeader::dispWifi(void)
{
	pBmap->drawARRAYlist(HEAD_ICO_WIFI_X, Top+HEAD_ICO_WIFI_Y, &icoWifi, ThmUnit.WifiRssi);
	RssiActif = ThmUnit.WifiRssi;
}

void myHeader::redraw(void)
{
	if((ThmUnit.Locked		!= LockActif |
		ThmUnit.WifiRssi	!= RssiActif |
		ThmUnit.TempExtern	!= TempActif |
		ThmUnit.TempExtMin	!= MinActif) | (ThmUnit.TempExtMax != MaxActif))
	{	
		pTft->fillRect(HEAD_BACKGROUND_X, Top+HEAD_BACKGROUND_Y, HEAD_BACKGROUND_W, HEAD_BACKGROUND_H, TFT_BLACK);
		dispLock();
		dispWifi();
		dispExtT();
		dispMinMax();
		pTft->drawFastHLine(HEAD_BACKGROUND_X, Top+HEAD_BACKGROUND_H, HEAD_BACKGROUND_W, HEAD_SEP_LINE_C);
	}
}

void myHeader::unlock(void)
{
	ThmUnit.Locked = !ThmUnit.Locked;
}

bool myHeader::isTouched(uint16_t touchX, uint16_t touchY)
{
	bool Clicked = false;
	if(touchX < icoLock.IconON->width)	{ unlock(); Clicked = true; }
	return Clicked;
}

void myHeader::loop()
{
	redraw();
}
