/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : mySelectBtn.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include <select/mySelectBtn.hpp>

#include "resources/bitmap/select/Heat_ON.h"
#include "resources/bitmap/select/Heat_OFF.h"

extern TFT_eSPI* pTft;																	//!< Pointer to the TFT screen class
extern THM		 ThmUnit;																//!< Pointer to the UNIT data structure
extern THM_DATA	 ThmData[THM_NBR];														//!< THERMOSTATS data array

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		mySelectBtn(int32_t x, int32_t y, int8_t index)
 * \brief	Create the class SELECT BUTTON
 * \note	Create the SELECT BUTTON class
 * \param	[in] x		as int32_t	- X offset of Button
 * \param	[in] y		as int32_t	- Y offset of Button
 * \param	[in] index	as int8_t	- index value of Button
 * \return	
 */
mySelectBtn::mySelectBtn(int32_t x, int32_t y, int8_t index)
{
	X = x;	Y = y; Index = index;
	pBmap = new myBitmap();

	IconState.IconON  = &Heat_ON;
	IconState.IconOFF = &Heat_OFF;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void init(void)
 * \brief	INIT the SELECT BUTTON class
 * \note	Initialize the SELECT BUTTON class
 * \param	void
 * \return	void
 */
void mySelectBtn::init()
{
	strcpy(ThmActif.Label, "Void");
	ThmActif.Temp	= -88.8;
	ThmActif.Target	= -88.8;
	ThmActif.Mode	= MODE_VOID;
	ThmActif.State	= BTN_STATE_OFF;
	redraw();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispLabel(void)
 * \brief	LABEL text display
 * \note	Display the text LABEL of thermostat Button
 * \param	void
 * \return	void
 */
void mySelectBtn::dispLabel(void)
{
	pTft->setTextDatum(TXT_TOP_CENTER);
	pTft->setTextColor(TFT_WHITE, TFT_BLACK, true);
	pTft->drawString(ThmData[Index].Label, X+BTN_TXT_LABEL_X, Y+BTN_TXT_LABEL_Y, BTN_TXT_LABEL_F);
	strcpy(ThmActif.Label, ThmData[Index].Label);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispTemp(void)
 * \brief	TEMPERATURE value display
 * \note	Display the value of Temperature Button
 * \param	void
 * \return	void
 */
void mySelectBtn::dispTemp(void)
{
	char TxtBuff[BTN_TXT_TEMP_B];
	sprintf(TxtBuff, TempTxt, ThmData[Index].Temp);
	pTft->setTextDatum(TXT_TOP_CENTER);
	pTft->setTextColor(TFT_GREEN, TFT_BLACK, true);
	pTft->drawString(TxtBuff, X+BTN_TXT_TEMP_X, Y+BTN_TXT_TEMP_Y, BTN_TXT_TEMP_F);
	ThmActif.Temp = ThmData[Index].Temp;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispTarget(void)
 * \brief	TARGET value display
 * \note	Display the value of Target Temp.
 * \param	void
 * \return	void
 */
void mySelectBtn::dispTarget(void)
{
	char TxtBuff[BTN_TXT_TARG_B];
	sprintf(TxtBuff, TempTxt, ThmData[Index].Target);
	pTft->setTextDatum(TXT_TOP_RIGHT);
	pTft->setTextColor(TFT_LIGHTGREY, TFT_BLACK, true);
	pTft->drawString(TxtBuff, X+BTN_TXT_TARG_X, Y+BTN_TXT_TARG_Y, BTN_TXT_TARG_F);
	ThmActif.Target = ThmData[Index].Target;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispState(void)
 * \brief	STATE icon display
 * \note	Display the heater Status icon
 * \param	void
 * \return	void
 */
void mySelectBtn::dispState(void)
{
	pBmap->drawARRAYbutton(X+BTN_ICO_STATE_X, Y+BTN_ICO_STATE_Y, &IconState, ThmData[Index].State);
	ThmActif.State = ThmData[Index].State;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispMode(void)
 * \brief	MODE text display
 * \note	Display the text of thermostat Mode
 * \param	void
 * \return	void
 */
void mySelectBtn::dispMode(void)
{
	const char*	TxtMode;
	switch(ThmData[Index].Mode)
	{
		case THM_MODES::MODE_CONF:	TxtMode = "PLUS";	break;
		case THM_MODES::MODE_ON :	TxtMode = "CONF";	break;
		case THM_MODES::MODE_ECO:	TxtMode = "ECO.";	break;
		case THM_MODES::MODE_HG:	TxtMode = "H.G.";	break;
		default:					TxtMode = "STOP";	break;
	}
	pTft->setTextDatum(TXT_TOP_LEFT);
	pTft->setTextColor(TFT_LIGHTGREY, TFT_BLACK, true);
	pTft->drawString(TxtMode, X+BTN_TXT_MODE_X, Y+BTN_TXT_MODE_Y, BTN_TXT_MODE_F);
	ThmActif.Mode = ThmData[Index].Mode;
}

/** ---------------------------------------------------------------------------------------------------------------------
* \fn		void redraw(void)
 * \brief	Redraw the Thermostat Button
 * \note	Redraw all the Thermostat Button parts
 * \param	void
 * \return	void
 */
void mySelectBtn::redraw(void)
{
	pTft->fillRect(X+BTN_FILL_BG_X, Y+BTN_FILL_BG_Y, BTN_FILL_BG_W, BTN_FILL_BG_H, TFT_BLACK);
	dispLabel();
	dispTemp();
	dispState();
	dispTarget();
	dispMode();
	ThmUnit.Redraw = true;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void redrawIf(void)
 * \brief	REDRAW IF updated
 * \note	Redraw all the Thermostat Button parts if an item is upgraded
 * \param	void
 * \return	void
 */
void mySelectBtn::redrawIf(void)
{
	if( strcmp(ThmData[Index].Label, ThmActif.Label) |
		ThmData[Index].Temp	  != ThmActif.Temp		 |
		ThmData[Index].Target != ThmActif.Target	 |
		ThmData[Index].Mode	  != ThmActif.Mode		 |
		ThmData[Index].State  != ThmActif.State)
	{
		redraw();
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void loop()
 * \brief	LOOP function
 * \note	Loopback function used for pulling the Thermostat Button redraw
 * \param	
 * \return	void
 */
void mySelectBtn::loop()
{
	redrawIf();
}
