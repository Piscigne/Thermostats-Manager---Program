#include <select/mySelect.hpp>

extern TFT_eSPI* pTft;
extern THM		 ThmUnit;
extern THM_DATA	 ThmData[THERMOSTAT_NBR];

mySelect::mySelect(int32_t top)
{
	Top = top;
	ThmBtn[THERMOSTAT1] = new mySelectBtn(SEL_SEP_LEFT,   Top+SEL_SEP_TOP, THERMOSTAT1);
	ThmBtn[THERMOSTAT2] = new mySelectBtn(SEL_SEP_MID_1,  Top+SEL_SEP_TOP, THERMOSTAT2);
	ThmBtn[THERMOSTAT3] = new mySelectBtn(SEL_SEP_MID_2,  Top+SEL_SEP_TOP, THERMOSTAT3);
	ThmBtn[THERMOSTAT4] = new mySelectBtn(SEL_SEP_LEFT,   Top+SEL_SEP_MID, THERMOSTAT4);
	ThmBtn[THERMOSTAT5] = new mySelectBtn(SEL_SEP_MID_1,  Top+SEL_SEP_MID, THERMOSTAT5);
	ThmBtn[THERMOSTAT6] = new mySelectBtn(SEL_SEP_MID_2,  Top+SEL_SEP_MID, THERMOSTAT6);
}

void mySelect::init()
{
	for(int i=0; i<THERMOSTAT_NBR; i++) ThmBtn[i]->init();
	drawSep();
}

void mySelect::redraw(void)
{
	for(int i=0; i<THERMOSTAT_NBR; i++) ThmBtn[i]->redraw();
	drawSep();
}

void mySelect::drawSep(void)
{
	if(ThmUnit.Redraw)
	{
		pTft->drawFastHLine(SEL_SEP_LEFT,  Top+SEL_SEP_TOP, SEL_SEP_WIDTH, TFT_LIGHTGREY);
		pTft->drawFastHLine(SEL_SEP_LEFT,  Top+SEL_SEP_MID, SEL_SEP_WIDTH, TFT_LIGHTGREY);
		pTft->drawFastHLine(SEL_SEP_LEFT,  Top+SEL_SEP_BOT, SEL_SEP_WIDTH, TFT_LIGHTGREY);

		pTft->drawFastVLine(SEL_SEP_LEFT,  Top+SEL_SEP_TOP, SEL_SEP_HEIGH, TFT_LIGHTGREY);
		pTft->drawFastVLine(SEL_SEP_MID_1, Top+SEL_SEP_TOP, SEL_SEP_HEIGH, TFT_LIGHTGREY);
		pTft->drawFastVLine(SEL_SEP_MID_2, Top+SEL_SEP_TOP, SEL_SEP_HEIGH, TFT_LIGHTGREY);
		pTft->drawFastVLine(SEL_SEP_RIGHT, Top+SEL_SEP_TOP, SEL_SEP_HEIGH, TFT_LIGHTGREY);
		ThmUnit.Redraw = false;
	}
}

bool mySelect::isTouched(uint16_t touchX, uint16_t touchY)
{
	if(touchY < SEL_SEP_MID)
	{
		if(		touchX < SEL_SEP_MID_1)	ThmUnit.Selected = THERMOSTAT1;
		else if(touchX < SEL_SEP_MID_2)	ThmUnit.Selected = THERMOSTAT2;
		else							ThmUnit.Selected = THERMOSTAT3;
	}
	else
	{
		if(		touchX < SEL_SEP_MID_1)	ThmUnit.Selected = THERMOSTAT4;
		else if(touchX < SEL_SEP_MID_2)	ThmUnit.Selected = THERMOSTAT5;
		else							ThmUnit.Selected = THERMOSTAT6;
	}
	return true;
}

void mySelect::loop()
{
	if(iLoopSelect < THERMOSTAT_NBR) ThmBtn[iLoopSelect++]->loop();
	else							 iLoopSelect = THERMOSTAT1;
	drawSep();
}
