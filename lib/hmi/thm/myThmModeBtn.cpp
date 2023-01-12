#include <thm/myThmModeBtn.hpp>

#include "resources/bitmap/thm/mode/bgnd/bgBtnON.h"
#include "resources/bitmap/thm/mode/bgnd/bgBtnOFF.h"

#include "resources/bitmap/thm/mode/icon/tempCONF.h"
#include "resources/bitmap/thm/mode/icon/tempON.h"
#include "resources/bitmap/thm/mode/icon/tempECO.h"
#include "resources/bitmap/thm/mode/icon/tempHG.h"
#include "resources/bitmap/thm/mode/icon/tempOFFon.h"
#include "resources/bitmap/thm/mode/icon/tempOFFoff.h"

extern TFT_eSPI* pTft;

myTHMmodeBtn::myTHMmodeBtn(int32_t x, int32_t y, int8_t mode)
{
	X = x;	Y = y; Mode = mode;
	pBmap = new myBitmap();

	int8_t Nbr = 0;

	IconMode.Icons[Nbr++] = &tempOFFoff;
	IconMode.Icons[Nbr++] = &tempHG;
	IconMode.Icons[Nbr++] = &tempECO;
	IconMode.Icons[Nbr++] = &tempON;
	IconMode.Icons[Nbr++] = &tempCONF;
	IconMode.Nbr = Nbr;

	IconOnOff.IconON	  = &tempOFFon;
	IconOnOff.IconOFF	  = &tempOFFoff;

	IconBG.IconON	 	  = &bgBtnON;
	IconBG.IconOFF	 	  = &bgBtnOFF;
}

void myTHMmodeBtn::init()
{
	redraw();
}

void myTHMmodeBtn::setMode(  int8_t mode)	{ Mode	  = mode;	dispMode();		}
void myTHMmodeBtn::setSelect(bool	select) { Select = select;	dispSelect();	}

void myTHMmodeBtn::redraw(void)
{
	dispSelect();
}

void myTHMmodeBtn::dispSelect(void)
{
	dispBgnd();
	dispMode();
}

void myTHMmodeBtn::dispBgnd(void)
{
	for(int8_t i = 0; i < BTN_BGND_WIDTH; i += BTN_BGND_STEP)	pBmap->drawARRAYbutton(X+i, Y, &IconBG, Select);
}

void myTHMmodeBtn::dispMode(void)
{
	if(Mode == THM_MODE_OFF)	pBmap->drawARRAYbutton(X+BTN_ICO_MODE_X, Y+BTN_ICO_MODE_Y, &IconOnOff, Select ? false : true);
	else						pBmap->drawARRAYlist(  X+BTN_ICO_MODE_X, Y+BTN_ICO_MODE_Y, &IconMode,  Mode);
}
