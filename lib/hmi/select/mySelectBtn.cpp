#include <select/mySelectBtn.hpp>

#include "resources/bitmap/select/Heat_ON.h"
#include "resources/bitmap/select/Heat_OFF.h"

extern TFT_eSPI* pTft;
extern THM		 ThmUnit;
extern THM_DATA	 ThmData[THERMOSTAT_NBR];

mySelectBtn::mySelectBtn(int32_t x, int32_t y, int index)
{
	X = x;	Y = y; Index = index;
	pBmap = new myBitmap();

	IconState.IconON  = &Heat_ON;
	IconState.IconOFF = &Heat_OFF;
}

void mySelectBtn::init()
{
	strcpy(ThmActif.Label, "Void");
	ThmActif.Temp	= -88.8;
	ThmActif.Target	= -88.8;
	ThmActif.Mode	= THM_MODE_VOID;
	ThmActif.State	= BTN_STATE_OFF;
	redraw();
}

void mySelectBtn::dispLabel(void)
{
	pTft->setTextDatum(TXT_TOP_CENTER);
	pTft->setTextColor(TFT_WHITE, TFT_BLACK, true);
	pTft->drawString(ThmData[Index].Label, X+BTN_TXT_LABEL_X, Y+BTN_TXT_LABEL_Y, BTN_TXT_LABEL_F);
	strcpy(ThmActif.Label, ThmData[Index].Label);
}

void mySelectBtn::dispTemp(void)
{
		char TxtBuff[BTN_TXT_TEMP_B];
		sprintf(TxtBuff, TempTxt, ThmData[Index].Temp);
		pTft->setTextDatum(TXT_TOP_CENTER);
		pTft->setTextColor(TFT_GREEN, TFT_BLACK, true);
		pTft->drawString(TxtBuff, X+BTN_TXT_TEMP_X, Y+BTN_TXT_TEMP_Y, BTN_TXT_TEMP_F);
		ThmActif.Temp = ThmData[Index].Temp;
}

void mySelectBtn::dispTarget(void)
{
		char TxtBuff[BTN_TXT_TARG_B];
		sprintf(TxtBuff, TempTxt, ThmData[Index].Target);
		pTft->setTextDatum(TXT_TOP_RIGHT);
		pTft->setTextColor(TFT_LIGHTGREY, TFT_BLACK, true);
		pTft->drawString(TxtBuff, X+BTN_TXT_TARG_X, Y+BTN_TXT_TARG_Y, BTN_TXT_TARG_F);
		ThmActif.Target = ThmData[Index].Target;
}

void mySelectBtn::dispMode(void)
{
		const char*	TxtMode;
		switch(ThmData[Index].Mode)
		{
			case THM_MODE_CONF:	TxtMode = "PLUS";	break;
			case THM_MODE_ON:	TxtMode = "CONF";	break;
			case THM_MODE_ECO:	TxtMode = "ECO.";	break;
			case THM_MODE_HG:	TxtMode = "H.G.";	break;
			default:			TxtMode = "STOP";	break;
		}
		pTft->setTextDatum(TXT_TOP_LEFT);
		pTft->setTextColor(TFT_LIGHTGREY, TFT_BLACK, true);
		pTft->drawString(TxtMode, X+BTN_TXT_MODE_X, Y+BTN_TXT_MODE_Y, BTN_TXT_MODE_F);
		ThmActif.Mode = ThmData[Index].Mode;
}

void mySelectBtn::dispState(void)
{
		pBmap->drawARRAYbutton(X+BTN_ICO_STATE_X, Y+BTN_ICO_STATE_Y, &IconState, ThmData[Index].State);
		ThmActif.State = ThmData[Index].State;
}

void mySelectBtn::redraw(void)
{
	if( strcmp(ThmData[Index].Label, ThmActif.Label) |
		ThmData[Index].Temp	  != ThmActif.Temp		 |
		ThmData[Index].Target != ThmActif.Target	 |
		ThmData[Index].Mode	  != ThmActif.Mode		 |
		ThmData[Index].State  != ThmActif.State)
	{
		pTft->fillRect(X+BTN_FILL_BG_X, Y+BTN_FILL_BG_Y, BTN_FILL_BG_W, BTN_FILL_BG_H, TFT_BLACK);
		dispLabel();
		dispTemp();
		dispState();
		dispTarget();
		dispMode();
		ThmUnit.Redraw = true;
	}
}

void mySelectBtn::loop()
{
	redraw();

}
