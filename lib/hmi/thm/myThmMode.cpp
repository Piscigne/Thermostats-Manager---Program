/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myTHMmode.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include <thm/myThmMode.hpp>

extern TFT_eSPI* pTft;																	//!< Pointer to the TFT screen class
extern myMqtt*	 pMqtt;																	//!< Pointer to the MQTT class
extern THM		 ThmUnit;																//!< Pointer to the UNIT data structure
extern THM_DATA	 ThmData[THM_NBR];														//!< Pointer to the THERMOSTATS data array

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		myTHMmode(int32_t top)
 * \brief	Create the class THM MODE
 * \note	Create the Thermostat MODE class
 * \param	[in] top	as int32_t	- Top offset of Thermostat
 * \return	
 */
myTHMmode::myTHMmode(int32_t top)
{
	Top = top;
	pModeCONF = new myTHMmodeBtn(THM_BTN_CONF, Top, MODE_CONF);
	pModeON	  = new myTHMmodeBtn(THM_BTN_ON,   Top, MODE_ON);
	pModeECO  = new myTHMmodeBtn(THM_BTN_ECO,  Top, MODE_ECO);
	pModeHG	  = new myTHMmodeBtn(THM_BTN_HG,   Top, MODE_HG);
	pModeOFF  = new myTHMmodeBtn(THM_BTN_OFF,  Top, MODE_OFF);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void init(void)
 * \brief	INIT the THM class
 * \note	Initialize the THM (Thermostat) class
 * \param	void
 * \return	void
 */
void myTHMmode::init()
{
	redraw();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void updateMode(void)
 * \brief	UPDATE a selected Mode
 * \note	Select Button mode Actif
 * \param	void
 * \return	void
 */
void myTHMmode::updateMode(void)
{
	ThmData[ThmUnit.Selected].Target = ThmData[ThmUnit.Selected].Targets[(int8_t)(ThmData[ThmUnit.Selected].Mode)];
	pModeCONF->setSelect(ThmData[ThmUnit.Selected].Mode == MODE_CONF);
	pModeON->setSelect(	 ThmData[ThmUnit.Selected].Mode == MODE_ON);
	pModeECO->setSelect( ThmData[ThmUnit.Selected].Mode == MODE_ECO);
	pModeHG->setSelect(	 ThmData[ThmUnit.Selected].Mode == MODE_HG);
	pModeOFF->setSelect( ThmData[ThmUnit.Selected].Mode == MODE_OFF);
	sendMqtt();
	redraw();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void sendMqtt(void)
 * \brief	MQTT send MODE
 * \note	Send by MQTT the new selected MODE
 * \param	void
 * \return	void
 */
void myTHMmode::sendMqtt(void)
{
	if(ThmData[ThmUnit.Selected].Mode != MODE_VOID)						// Check and don't emit mode during the boot initialization
	{
		char Topic[32];
		sprintf(Topic, "Piscigne/THMS/MODE/THM%i", ThmUnit.Selected+1);

		const char*	TxtMode;
		switch(ThmData[ThmUnit.Selected].Mode)
		{
			case MODE_CONF:	TxtMode = "CONF+";	break;
			case MODE_ON:	TxtMode = "CONF";	break;
			case MODE_ECO:	TxtMode = "ECO.";	break;
			case MODE_HG:	TxtMode = "H.G.";	break;
			default:		TxtMode = "ARRET";	break;
		}
		pMqtt->sendStr(Topic, TxtMode);
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispSep(void)
 * \brief	SEPARATOR display
 * \note	Display the Buttons Separators
 * \param	void
 * \return	void
 */
void myTHMmode::dispSep(void)
{
	pTft->drawFastVLine(THM_BTN_CONF, Top, THM_SEP_HIGHT, TFT_DARKGREY);
	pTft->drawFastVLine(THM_BTN_ON,   Top, THM_SEP_HIGHT, TFT_DARKGREY);
	pTft->drawFastVLine(THM_BTN_ECO,  Top, THM_SEP_HIGHT, TFT_DARKGREY);
	pTft->drawFastVLine(THM_BTN_HG,   Top, THM_SEP_HIGHT, TFT_DARKGREY);
}

/** ---------------------------------------------------------------------------------------------------------------------
* \fn		void redraw(void)
 * \brief	Redraw the Thermostat Mode
 * \note	Redraw all the Thermostat Mode buttons
 * \param	void
 * \return	void
 */
void myTHMmode::redraw(void)
{
	pModeCONF->redraw();
	pModeON->redraw();
	pModeECO->redraw();
	pModeHG->redraw();
	pModeOFF->redraw();
	dispSep();
}


/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void isTouched(void)
 * \brief	Manage screen touched
 * \note	If screen is touched, analyze the area concerned
 * \param	[in] touchX	as uint16_t	- X coordinate of touched point
 * \param	[in] touchY	as uint16_t	- Y coordinate of touched point
 * \return	bool - TRUE if clicked in the valid area
 */
bool myTHMmode::isTouched(uint16_t touchX, uint16_t touchY)
{
	bool Clicked = false;
	if(!ThmUnit.Locked)
	{
		if(		touchX > THM_BTN_CONF)	ThmData[ThmUnit.Selected].Mode = MODE_CONF;		//!< If button CONF touched
		else if(touchX > THM_BTN_ON)	ThmData[ThmUnit.Selected].Mode = MODE_ON;		//!< If button ON   touched
		else if(touchX > THM_BTN_ECO)	ThmData[ThmUnit.Selected].Mode = MODE_ECO;		//!< If button ECO  touched
		else if(touchX > THM_BTN_HG)	ThmData[ThmUnit.Selected].Mode = MODE_HG;		//!< If button HG   touched
		else							ThmData[ThmUnit.Selected].Mode = MODE_OFF;		//!< If button OFF  touched
		updateMode();
		Clicked = true;
	}
	return Clicked;
}