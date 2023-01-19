/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myHeader.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include "header/myHeader.hpp"

#include "resources/bitmap/header/lock/LockON.h"										//!< Include the bitmaps of LOCK button
#include "resources/bitmap/header/lock/LockOFF.h"

#include "resources/bitmap/header/wifi/wifi_0.h"										//!< Include the bitmaps of WIFI status
#include "resources/bitmap/header/wifi/wifi_1.h"
#include "resources/bitmap/header/wifi/wifi_2.h"
#include "resources/bitmap/header/wifi/wifi_3.h"
#include "resources/bitmap/header/wifi/wifi_4.h"
#include "resources/bitmap/header/wifi/wifiOFF.h"
#include "resources/bitmap/header/wifi/wifiERR.h"

extern TFT_eSPI* pTft;																	//!< Pointer to the TFT screen class
extern myLock*	 pLock;																	//!< Pointer to the LOCK screen class
extern THM		 ThmUnit;																//!< Pointer to the UNIT data structure

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		myHeader(int32_t top)
 * \brief	Create the class HEADER
 * \note	Create the HEADER class
 * \param	[in] top	as int32_t	- Top offset of Header
 * \return	
 */
myHeader::myHeader(int32_t top)
{
	Top = top;

	icoWifi.Icons[icoWifi.Nbr++] = &wifi_0;
	icoWifi.Icons[icoWifi.Nbr++] = &wifi_1;
	icoWifi.Icons[icoWifi.Nbr++] = &wifi_2;
	icoWifi.Icons[icoWifi.Nbr++] = &wifi_3;
	icoWifi.Icons[icoWifi.Nbr++] = &wifi_4;
	icoWifi.Icons[icoWifi.Nbr++] = &wifiOFF;
	icoWifi.Icons[icoWifi.Nbr++] = &wifiERR;

	icoLock.IconON  = &lockON;
	icoLock.IconOFF = &lockOFF;

	pBmap = new myBitmap();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void init(void)
 * \brief	INIT the HEADER class
 * \note	Initialize the HEADER class
 * \param	void
 * \return	void
 */
void myHeader::init(void)
{
	redraw();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispLock(void)
 * \brief	LOCK icon display
 * \note	Display the LOCK icon
 * \param	void
 * \return	void
 */
void myHeader::dispLock(void)
{
	pBmap->drawARRAYbutton(HEAD_ICO_LOCK_X, Top+HEAD_ICO_LOCK_Y, &icoLock, ThmUnit.Locked);
	LockActif = ThmUnit.Locked;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispExtT(void)
 * \brief	TEMPERATURE display
 * \note	Display the external temperature
 * \param	void
 * \return	void
 */
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

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispMinMax(void)
 * \brief	MINI MAXI display
 * \note	Display the minimal and maximal external temperature
 * \param	void
 * \return	void
 */
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

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispWifi(void)
 * \brief	WIFI icon display
 * \note	Display the WIFI icon
 * \param	void
 * \return	void
 */
void myHeader::dispWifi(void)
{
	pBmap->drawARRAYlist(HEAD_ICO_WIFI_X, Top+HEAD_ICO_WIFI_Y, &icoWifi, ThmUnit.Wifi.State);
	RssiActif = ThmUnit.Wifi.State;
}

/** ---------------------------------------------------------------------------------------------------------------------
* \fn		void redraw(void)
 * \brief	Redraw the HEADER
 * \note	Redraw all the HEADER parts
 * \param	void
 * \return	void
 */
void myHeader::redraw(void)
{
	pTft->fillRect(HEAD_BACKGROUND_X, Top+HEAD_BACKGROUND_Y, HEAD_BACKGROUND_W, HEAD_BACKGROUND_H, TFT_BLACK);
	dispLock();
	dispWifi();
	dispExtT();
	dispMinMax();
//	pTft->drawFastHLine(HEAD_BACKGROUND_X, Top+HEAD_BACKGROUND_H, HEAD_BACKGROUND_W, HEAD_SEP_LINE_C);
	pTft->drawFastHLine(HEAD_BACKGROUND_X, Top+HEAD_BACKGROUND_H, HEAD_BACKGROUND_W, ThmUnit.EdfECOMode ? TFT_DARKGREEN : TFT_BROWN);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void redrawIf(void)
 * \brief	REDRAW IF updated
 * \note	Redraw all the HEADER parts if an item is upgraded
 * \param	void
 * \return	void
 */
void myHeader::redrawIf(void)
{
	if((ThmUnit.Locked		!= LockActif |
		ThmUnit.Wifi.State	!= RssiActif |
		ThmUnit.TempExtern	!= TempActif |
		ThmUnit.TempExtMin	!= MinActif) | (ThmUnit.TempExtMax != MaxActif))
	{
		redraw();
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void unlock(void)
 * \brief	UNLOCK clicked
 * \note	If unlock is clicked, display the keypad to enter the unlock code of if already unlocked, lock the access
 * \param	void
 * \return	void
 */
void myHeader::unlock(void)
{
	if(ThmUnit.Locked)	pLock->init();
	else				ThmUnit.Locked = ON;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void isTouched(void)
 * \brief	Manage screen touched
 * \note	If screen is touched, analyze the area concerned
 * \param	[in] touchX	as uint16_t	- X coordinate of touched point
 * \param	[in] touchY	as uint16_t	- Y coordinate of touched point
 * \return	bool - TRUE if clicked in the valid area
 */
bool myHeader::isTouched(uint16_t touchX, uint16_t touchY)
{
	bool Clicked = false;
	if(touchX < icoLock.IconON->width)	{ unlock(); Clicked = true; }
	return Clicked;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void loop()
 * \brief	LOOP function
 * \note	Loopback function used for pulling the header redraw
 * \param	
 * \return	void
 */
void myHeader::loop()
{
	if(!ThmUnit.Keyboard) redrawIf();
}
