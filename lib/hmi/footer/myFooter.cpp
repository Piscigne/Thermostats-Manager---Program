#include <footer/myFooter.hpp>

#include "resources/bitmap/footer/home/homeON.h"
#include "resources/bitmap/footer/home/homeOFF.h"
#include "resources/bitmap/footer/lamp/lampeON.h"
#include "resources/bitmap/footer/lamp/lampeOFF.h"

extern TFT_eSPI* pTft;
extern myDio*	 pDio;
extern myWifi*	 pWifi;
extern bool		 Locked;
extern myTime*	 MYtime;
extern THM		 ThmUnit;

hw_timer_t*		pTimerTime	= NULL;
hw_timer_t*		pTimerDate	= NULL;
bool			UpdateTime	= true;
bool			UpdateDate	= true;

void IRAM_ATTR onTimeTime()		{ UpdateTime = true; }
void IRAM_ATTR onTimeDate()		{ UpdateDate = true; }

myFooter::myFooter(int32_t top)
{
	Top = top;

	icoLamp.IconON	= &lampeON;
	icoLamp.IconOFF	= &lampeOFF;

	icoHome.IconON  = &homeON;
	icoHome.IconOFF = &homeOFF;

	pTimerTime	 = timerBegin(1, 80, true);	timerAttachInterrupt(pTimerTime,   &onTimeTime,	  true); timerAlarmWrite(pTimerTime,   1000000, true);
	pTimerDate	 = timerBegin(2, 80, true);	timerAttachInterrupt(pTimerDate,   &onTimeDate,	  true); timerAlarmWrite(pTimerDate,  60000000, true);
}

void myFooter::init(void)
{
	redraw();
	timerAlarmEnable(pTimerTime);
	timerAlarmEnable(pTimerDate);
}

void myFooter::dispHome(void)
{
	if(ThmUnit.Presence != HomeActif)
	{
		pTft->fillRect(		   FOOT_ICO_HOME_X, Top+FOOT_ICO_HOME_Y, icoHome.IconON->width, icoHome.IconON->height, TFT_BLACK);
		pBmap->drawARRAYbutton(FOOT_ICO_HOME_X, Top+FOOT_ICO_HOME_Y, &icoHome, ThmUnit.Presence);
		HomeActif = ThmUnit.Presence;
	}
}

void myFooter::dispLamp(void)
{
	if(ThmUnit.Lampe != LampActif)
	{
		pTft->fillRect(		   FOOT_ICO_LAMP_X, Top+FOOT_ICO_LAMP_Y, icoLamp.IconON->width, icoLamp.IconON->height, TFT_BLACK);
		pBmap->drawARRAYbutton(FOOT_ICO_LAMP_X, Top+FOOT_ICO_LAMP_Y, &icoLamp, ThmUnit.Lampe);
		LampActif = ThmUnit.Lampe;
	}
}

void myFooter::dispTime(void)
{
	if(UpdateTime)
	{
		UpdateTime = false;
		pTft->setTextDatum(TXT_TOP_CENTER);
		pTft->setTextColor(TFT_LIGHTGREY, TFT_BLACK, true);
		pTft->fillRect(FOOT_TXT_TIME_X, Top+FOOT_TXT_TIME_Y, FOOT_TXT_TIME_W, FOOT_TXT_TIME_H, TFT_BLACK);
		pTft->drawString(MYtime->getTime(), FOOT_TXT_TIME_C, Top+FOOT_TXT_TIME_Y, FOOT_TXT_TIME_F);
	}
}

void myFooter::dispDate(void)
{
	if(UpdateDate)
	{
		UpdateDate = false;
		pTft->setTextDatum(TXT_TOP_CENTER);
		pTft->setTextColor(TFT_LIGHTGREY, TFT_BLACK, true);
		pTft->fillRect(FOOT_TXT_DATE_X, Top+FOOT_TXT_DATE_Y, FOOT_TXT_DATE_W, FOOT_TXT_DATE_H, TFT_BLACK);
		pTft->drawString(MYtime->getDate(), FOOT_TXT_DATE_C, Top+FOOT_TXT_DATE_Y, FOOT_TXT_DATE_F);
		ThmUnit.WifiRssi = pWifi->getRssi();
	}
}

void myFooter::redraw(void)
{
	dispTime();
	dispHome();
	dispLamp();
}

void myFooter::infoTouch(bool status)
{
}

void myFooter::presence(void)
{
	ThmUnit.Presence = true;
}

bool myFooter::isTouched(uint16_t touchX, uint16_t touchY)
{
	bool Clicked = false;
//	if(touchX >= FOOT_ICO_HOME_X) {	presence(); Clicked = true; }
	return Clicked;
}

void myFooter::loop()
{
	switch(iLoopFoot++)
	{
		case LOOP_FOOT_HOME:	dispHome();		break;
		case LOOP_FOOT_LAMP:	dispLamp();		break;
		case LOOP_FOOT_TIME:	dispTime();		break;
		case LOOP_FOOT_DATE:	dispDate();		break;
		default:				iLoopFoot = 0;
	}
}
