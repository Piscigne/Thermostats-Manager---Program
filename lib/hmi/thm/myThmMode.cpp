#include <thm/myThmMode.hpp>

extern TFT_eSPI* pTft;
extern myMqtt*	 pMqtt;
extern THM		 ThmUnit;
extern THM_DATA	 ThmData[THERMOSTAT_NBR];

myTHMmode::myTHMmode(int32_t top)
{
	Top = top;
	pModeCONF = new myTHMmodeBtn(THM_BTN_CONF, Top, THM_MODE_CONF);
	pModeON	  = new myTHMmodeBtn(THM_BTN_ON,   Top, THM_MODE_ON);
	pModeECO  = new myTHMmodeBtn(THM_BTN_ECO,  Top, THM_MODE_ECO);
	pModeHG	  = new myTHMmodeBtn(THM_BTN_HG,   Top, THM_MODE_HG);
	pModeOFF  = new myTHMmodeBtn(THM_BTN_OFF,  Top, THM_MODE_OFF);
}

void myTHMmode::init()
{
	redraw();
}

void myTHMmode::updateMode(void)
{
	ThmData[ThmUnit.Selected].Target = ThmData[ThmUnit.Selected].Targets[ThmData[ThmUnit.Selected].Mode];
	pModeCONF->setSelect(ThmData[ThmUnit.Selected].Mode == THM_MODE_CONF);
	pModeON->setSelect(	 ThmData[ThmUnit.Selected].Mode == THM_MODE_ON);
	pModeECO->setSelect( ThmData[ThmUnit.Selected].Mode == THM_MODE_ECO);
	pModeHG->setSelect(	 ThmData[ThmUnit.Selected].Mode == THM_MODE_HG);
	pModeOFF->setSelect( ThmData[ThmUnit.Selected].Mode == THM_MODE_OFF);
	sendMqtt();
	redraw();
}

void myTHMmode::sendMqtt(void)
{
	char Topic[32];
	sprintf(Topic, "Piscigne/THMS/MODE/THM%i", ThmUnit.Selected+1);

	const char*	TxtMode;
	switch(ThmData[ThmUnit.Selected].Mode)
	{
		case THM_MODE_CONF:	TxtMode = "CONF+";	break;
		case THM_MODE_ON:	TxtMode = "CONF";	break;
		case THM_MODE_ECO:	TxtMode = "ECO.";	break;
		case THM_MODE_HG:	TxtMode = "H.G.";	break;
		default:			TxtMode = "ARRET";	break;
	}
	pMqtt->sendStr(Topic, TxtMode);
}

void myTHMmode::redraw(void)
{
	pModeCONF->redraw();
	pModeON->redraw();
	pModeECO->redraw();
	pModeHG->redraw();
	pModeOFF->redraw();
	dispSep();
}

void myTHMmode::dispSep(void)
{
	pTft->drawFastVLine(THM_BTN_ON,  Top, THM_SEP_HIGHT, TFT_DARKGREY);
	pTft->drawFastVLine(THM_BTN_ECO, Top, THM_SEP_HIGHT, TFT_DARKGREY);
	pTft->drawFastVLine(THM_BTN_HG,  Top, THM_SEP_HIGHT, TFT_DARKGREY);
	pTft->drawFastVLine(THM_BTN_OFF, Top, THM_SEP_HIGHT, TFT_DARKGREY);
}

bool myTHMmode::isTouched(uint16_t touchX, uint16_t touchY)
{
	bool Clicked = false;
	if(!ThmUnit.Locked)
	{
		if(		touchX > THM_BTN_CONF)	ThmData[ThmUnit.Selected].Mode = THM_MODE_CONF;
		else if(touchX > THM_BTN_ON)	ThmData[ThmUnit.Selected].Mode = THM_MODE_ON;
		else if(touchX > THM_BTN_ECO)	ThmData[ThmUnit.Selected].Mode = THM_MODE_ECO;
		else if(touchX > THM_BTN_HG)	ThmData[ThmUnit.Selected].Mode = THM_MODE_HG;
		else							ThmData[ThmUnit.Selected].Mode = THM_MODE_OFF;
		updateMode();
		Clicked = true;
	}
	return Clicked;
}