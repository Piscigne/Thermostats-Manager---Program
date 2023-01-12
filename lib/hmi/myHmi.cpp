#include "myHmi.hpp"

extern TFT_eSPI*	pTft;
extern TFT_Touch*	pTouch;

extern bool			Locked;	
extern int8_t		Wifi;

//myPng* pPng = new myPng();

myHmi::myHmi()
{
	pHead = new myHeader(TOP_HEAD);
	pThm  = new myThm(	 TOP_THM);
	pThms = new mySelect(TOP_THMS);
	pFoot = new myFooter(TOP_FOOT);
}

void myHmi::init(void)
{
	pTft->setTextColor(TFT_WHITE, TFT_BLACK);
	pTft->fillScreen(  TFT_BLACK);

	pHead->init();
	pThm->init();
	pThms->init();
	pFoot->init();

//	Login.initialize();
}

void myHmi::redraw(void)
{
	pTft->setTextColor(TFT_WHITE, TFT_BLACK);
	pTft->fillScreen(  TFT_BLACK);
	pHead->redraw();
	pThm->redraw();
	pThms->redraw();
	pFoot->redraw();
}

void myHmi::isTouched()
{
	if(pTouch->Pressed())
	{
		uint16_t TouchX, TouchY;
		TouchX = pTouch->X();
		TouchY = pTouch->Y();
		bool Status = false;
		if(		TouchY < TOP_THM)	Status = pHead->isTouched(TouchX, TouchY);
		else if(TouchY < TOP_THMS)	Status = pThm->isTouched( TouchX, TouchY-TOP_THM);
		else if(TouchY < TOP_FOOT)	Status = pThms->isTouched(TouchX, TouchY-TOP_THMS);
		else						Status = pFoot->isTouched(TouchX, TouchY-TOP_FOOT);
		pFoot->infoTouch(Status);
		Serial.printf("X = %i, Y = %i, Clicked: %s\n", TouchX, TouchY, Status ? "ON" : "OFF");
		delay(TOUCH_DEBOUNCE);
	}
}

void myHmi::loop()
{
	switch(iLoopHmi++)
	{
		case LOOP_HMI_TOUCH:	isTouched();	break;
		case LOOP_HMI_HEADER:	pHead->loop();	break;
		case LOOP_HMI_THM:		pThm->loop();	break;
		case LOOP_HMI_SELECT:	pThms->loop();	break;
		case LOOP_HMI_FOOTER:	pFoot->loop();	break;
		default:				iLoopHmi = 0;
	}
}
