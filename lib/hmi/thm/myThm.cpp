/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myThm.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include <thm/myThm.hpp>

#include "resources/bitmap/thm/heaterON.h"
#include "resources/bitmap/thm/heaterOFF.h"

extern TFT_eSPI* pTft;																	//!< Pointer to the TFT screen class
extern THM		 ThmUnit;																//!< Pointer to the UNIT data structure
extern THM_DATA	 ThmData[THM_NBR];														//!< Pointer to the THERMOSTATS data array

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		myThm(int32_t top)
 * \brief	Create the class THM
 * \note	Create the THM (Thermostat) class
 * \param	[in] top	as int32_t	- Top offset of Thermostat
 * \return	
 */
myThm::myThm(int32_t top)
{
	Top = top;
	pBmap = new myBitmap();
	pMode = new myTHMmode(Top+THM_MODE_SWITCH);

	IconState.IconON  = &heaterON;
	IconState.IconOFF = &heaterOFF;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void init(void)
 * \brief	INIT the THM class
 * \note	Initialize the THM (Thermostat) class
 * \param	void
 * \return	void
 */
void myThm::init()
{
	strcpy(ThmActif.Label, "Void");
	ThmActif.Temp	= -88.8;
	ThmActif.Target = -88.8;
	ThmActif.State	= THM_STATE_OFF;	pBmap->drawARRAYbutton(THM_ICO_STATE_X, Top+THM_ICO_STATE_Y, &IconState, THM_STATE_OFF);
	ThmActif.Mode	= THM_MODES::MODE_VOID;
	ThmSelected		= THM_VOID;
	redraw();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispLabel(void)
 * \brief	LABEL text display
 * \note	Display the text LABEL of thermostat
 * \param	void
 * \return	void
 */
void myThm::dispLabel(void)
{
	pTft->setTextDatum(TXT_TOP_CENTER);
	pTft->setTextColor(TFT_WHITE, TFT_BLACK, true);
	pTft->drawString(ThmData[ThmUnit.Selected].Label, THM_TXT_LABEL_C, Top+THM_TXT_LABEL_Y, THM_TXT_LABEL_F);
	strcpy(ThmActif.Label, ThmData[ThmUnit.Selected].Label);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispTemp(void)
 * \brief	TEMPERATURE value display
 * \note	Display the value of Temperature Button
 * \param	void
 * \return	void
 */
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

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispTarget(void)
 * \brief	TARGET value display
 * \note	Display the value of Target Temp.
 * \param	void
 * \return	void
 */
void myThm::dispTarget(void)
{
	char TxtBuff[THM_TXT_TARG_B];
	sprintf(TxtBuff, TargTxt, ThmData[ThmUnit.Selected].Target);
	pTft->setTextDatum(TXT_TOP_RIGHT);
	pTft->setTextColor(TFT_LIGHTGREY, TFT_BLACK, true);
	pTft->drawString(TxtBuff, THM_TXT_TARG_L, Top+THM_TXT_TARG_Y, THM_TXT_TARG_F);
	ThmActif.Target = ThmData[ThmUnit.Selected].Target;
}

/** ---------------------------------------------------------------------------------------------------------------------
* \fn		void dispEdf(void)
 * \brief	EDF Mode
 * \note	Display the EDF tarification mode
 * \param	void
 * \return	void
 */
void myThm::dispEdf(void)
{
	pTft->setTextDatum(TXT_TOP_LEFT);
	pTft->setTextColor(ThmUnit.EdfECOMode ? TFT_DARKGREEN : TFT_BROWN, TFT_BLACK, true);
	pTft->drawString(  ThmUnit.EdfECOMode ? F("H.C.") : F("H.P."), THM_TXT_EDF_X, Top+THM_TXT_EDF_Y, THM_TXT_EDF_F);
	EdfActif = ThmUnit.EdfECOMode;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispState(void)
 * \brief	STATE icon display
 * \note	Display the heater Status icon
 * \param	void
 * \return	void
 */
void myThm::dispState(void)
{
		pBmap->drawARRAYbutton(THM_ICO_STATE_X, Top+THM_ICO_STATE_Y, &IconState, ThmData[ThmUnit.Selected].State);
		ThmActif.State = ThmData[ThmUnit.Selected].State;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispMode(void)
 * \brief	MODE text display
 * \note	Display the text of thermostat Mode and the Mode Select Buttons
 * \param	void
 * \return	void
 */
void myThm::dispMode(void)
{
	pMode->updateMode();
	const char*	TxtMode;
	switch(ThmData[ThmUnit.Selected].Mode)
	{
		case MODE_CONF:	TxtMode = "CONF+";	break;
		case MODE_ON:	TxtMode = "CONF";	break;
		case MODE_ECO:	TxtMode = "ECO.";	break;
		case MODE_HG:	TxtMode = "H.G.";	break;
		default:		TxtMode = "ARRET";	break;
	}
	pTft->setTextDatum(TXT_TOP_CENTER);
	pTft->setTextColor(TFT_LIGHTGREY, TFT_BLACK, true);
	pTft->drawString(TxtMode, THM_TXT_MODE_C, Top+THM_TXT_MODE_Y, THM_TXT_MODE_F);
	ThmActif.Mode = ThmData[ThmUnit.Selected].Mode;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispModeIf(void)
 * \brief	REDRAW IF updated
 * \note	Redraw all the Mode Thermostat and the Mode Select Buttons if upgraded
 * \param	void
 * \return	void
 */
void myThm::dispModeIf(void)
{
	if(ThmData[ThmUnit.Selected].Mode != ThmActif.Mode)
	{
		dispMode();
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void setActif(void)
 * \brief	ACTIVATE a selected Thermostat
 * \note	Associate data of the new selected thermostat
 * \param	void
 * \return	void
 */
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

/** ---------------------------------------------------------------------------------------------------------------------
* \fn		void redraw(void)
 * \brief	Redraw the Thermostat
 * \note	Redraw all the Thermostat parts
 * \param	void
 * \return	void
 */
void myThm::redraw(void)
{
	pTft->fillRect(0, Top, 240, THM_MODE_SWITCH, TFT_BLACK);
	dispLabel();
	dispEdf();
	dispTemp();
	dispTarget();
	dispState();
	dispMode();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void redrawIf(void)
 * \brief	REDRAW IF updated
 * \note	Redraw all the Thermostat parts if an item is upgraded
 * \param	void
 * \return	void
 */
void myThm::redrawIf(void)
{
	if( strcmp(ThmData[ThmUnit.Selected].Label, ThmActif.Label)	|
		ThmData[ThmUnit.Selected].Temp	 != ThmActif.Temp		|
		ThmData[ThmUnit.Selected].Target != ThmActif.Target		|
		ThmData[ThmUnit.Selected].State	 != ThmActif.State		|
		ThmUnit.EdfECOMode				 != EdfActif)
	{
		redraw();
	}
	dispModeIf();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void isTouched(void)
 * \brief	Manage screen touched
 * \note	If screen is touched, analyze the area concerned
 * \param	[in] touchX	as uint16_t	- X coordinate of touched point
 * \param	[in] touchY	as uint16_t	- Y coordinate of touched point
 * \return	bool - TRUE if clicked in the valid area
 */
bool myThm::isTouched(uint16_t touchX, uint16_t touchY)
{
	bool Clicked = false;
	if(touchY > THM_MODE_SWITCH)	Clicked = pMode->isTouched(touchX, touchY);
	return Clicked;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void loop()
 * \brief	LOOP function
 * \note	Loopback function used for pulling the Thermostat redraw and check if selected thermostat is changed
 * \param	
 * \return	void
 */
void myThm::loop()
{
	if(ThmUnit.Selected != ThmSelected) setActif();
	redrawIf();
}
