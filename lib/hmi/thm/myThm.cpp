#include <thm/myThm.hpp>

#include "resources/bitmap/thm/heaterON.h"
#include "resources/bitmap/thm/heaterOFF.h"

extern TFT_eSPI* pTft;
extern THM		 ThmUnit;
extern THM_DATA	 ThmData[THERMOSTAT_NBR];

myThm::myThm(int32_t top)
{
	Top = top;
	pBmap = new myBitmap();
	pMode = new myTHMmode(Top+THM_MODE_SWITCH);

	IconState.IconON  = &heaterON;
	IconState.IconOFF = &heaterOFF;
}

void myThm::init()
{
	strcpy(ThmActif.Label, "Void");
	ThmActif.Temp	= -88.8;
	ThmActif.Target = -88.8;
	ThmActif.State	= THM_STATE_OFF;	pBmap->drawARRAYbutton(THM_ICO_STATE_X, Top+THM_ICO_STATE_Y, &IconState, THM_STATE_OFF);
	ThmActif.Mode	= THM_MODE_VOID;
	ThmSelected		= THERMOSTAT_VOID;
	redraw();
}

void myThm::redraw(void)
{
	pTft->fillRect(0, Top, 240, THM_MODE_SWITCH, TFT_BLACK);
	dispLabel();
	dispTemp();
	dispTarget();
	dispState();
	dispMode();
}

void myThm::redrawIf(void)
{
	if( strcmp(ThmData[ThmUnit.Selected].Label, ThmActif.Label)	|
		ThmData[ThmUnit.Selected].Temp	 != ThmActif.Temp		|
		ThmData[ThmUnit.Selected].Target != ThmActif.Target		|
		ThmData[ThmUnit.Selected].State	 != ThmActif.State)
	{
		redraw();
	}
	dispModeIf();
}

void myThm::dispLabel(void)
{
		pTft->setTextDatum(TXT_TOP_CENTER);
		pTft->setTextColor(TFT_WHITE, TFT_BLACK, true);
		pTft->drawString(ThmData[ThmUnit.Selected].Label, THM_TXT_LABEL_C, Top+THM_TXT_LABEL_Y, THM_TXT_LABEL_F);
		strcpy(ThmActif.Label, ThmData[ThmUnit.Selected].Label);
}

void myThm::dispTemp(void)
{
		char TxtBuff[THM_TXT_TEMP_B];
		sprintf(TxtBuff, TempTxt, ThmData[ThmUnit.Selected].Temp);
		pTft->setTextDatum(TXT_TOP_RIGHT);
		pTft->setTextColor(TFT_GREEN, TFT_BLACK, true);
		pTft->drawString(TxtBuff, THM_TXT_TEMP_C, Top+THM_TXT_TEMP_Y, THM_TXT_TEMP_F);
		pTft->setTextDatum(TXT_TOP_LEFT);
		pTft->drawString("`C", THM_TXT_TEMP_C+4, Top+THM_TXT_TEMP_Y, THM_TXT_TEMP_UF);
		ThmActif.Temp = ThmData[ThmUnit.Selected].Temp;
}

void myThm::dispTarget(void)
{
		char TxtBuff[THM_TXT_TARG_B];
		sprintf(TxtBuff, TargTxt, ThmData[ThmUnit.Selected].Target);
		pTft->setTextDatum(TXT_TOP_RIGHT);
		pTft->setTextColor(TFT_LIGHTGREY, TFT_BLACK, true);
		pTft->drawString(TxtBuff, THM_TXT_TARG_L, Top+THM_TXT_TARG_Y, THM_TXT_TARG_F);
		ThmActif.Target = ThmData[ThmUnit.Selected].Target;
}

void myThm::dispState(void)
{
		pBmap->drawARRAYbutton(THM_ICO_STATE_X, Top+THM_ICO_STATE_Y, &IconState, ThmData[ThmUnit.Selected].State);
		ThmActif.State = ThmData[ThmUnit.Selected].State;
}

void myThm::dispMode(void)
{
	pMode->updateMode();
	const char*	TxtMode;
	switch(ThmData[ThmUnit.Selected].Mode)
	{
		case THM_MODE_CONF:	TxtMode = "CONF+";	break;
		case THM_MODE_ON:	TxtMode = "CONF";	break;
		case THM_MODE_ECO:	TxtMode = "ECO.";	break;
		case THM_MODE_HG:	TxtMode = "H.G.";	break;
		default:			TxtMode = "ARRET";	break;
	}
	pTft->setTextDatum(TXT_TOP_CENTER);
	pTft->setTextColor(TFT_LIGHTGREY, TFT_BLACK, true);
	pTft->drawString(TxtMode, THM_TXT_MODE_C, Top+THM_TXT_MODE_Y, THM_TXT_MODE_F);
	ThmActif.Mode = ThmData[ThmUnit.Selected].Mode;
}

void myThm::dispModeIf(void)
{
	if(ThmData[ThmUnit.Selected].Mode != ThmActif.Mode)
	{
		dispMode();
	}
}

void myThm::setActif(void)
{
	strcpy(ThmActif.Label, ThmData[ThmUnit.Selected].Label);
	ThmActif.Temp	= ThmData[ThmUnit.Selected].Temp;
	ThmActif.Mode	= ThmData[ThmUnit.Selected].Mode;
	ThmActif.State	= ThmData[ThmUnit.Selected].State;
	ThmActif.Target	= ThmData[ThmUnit.Selected].Target;
	ThmSelected		= ThmUnit.Selected;

	redraw();
}

bool myThm::isTouched(uint16_t touchX, uint16_t touchY)
{
	bool Clicked = false;
	if(touchY > THM_MODE_SWITCH)	Clicked = pMode->isTouched(touchX, touchY);
	return Clicked;
}

void myThm::loop()
{
	if(ThmUnit.Selected != ThmSelected) setActif();
	redrawIf();
}
