/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myHmi.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include "myHmi.hpp"

extern TFT_eSPI*	pTft;																	//!< Pointer to the TFT screen class
extern myDio*	 	pDio;																	//!< Pointer to the DIO screen class
extern TFT_Touch*	pTouch;																	//!< Pointer to the TOUCH screen class
extern myLock*		pLock;																	//!< Pointer to the LOCK screen class
extern myMqtt*	 	pMqtt;																	//!< Pointer to the MQTT screen class
extern THM			ThmUnit;																//!< Pointer to the UNIT data structure

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		myHmi()
 * \brief	Create the class HMI
 * \note	Create the HMI class
 * \param	
 * \return	
 */
myHmi::myHmi()
{
	pHead = new myHeader(TOP_HEAD);															//!< Create the HEADER class
	pThm  = new myThm(	 TOP_THM);															//!< Create the THERMOSTAT class
	pThms = new mySelect(TOP_THMS);															//!< Create the THM SELECT class
	pFoot = new myFooter(TOP_FOOT);															//!< Create the FOOTER class
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void init(void)
 * \brief	INIT the HMI class
 * \note	Initialize the HMI class
 * \param	void
 * \return	void
 */
void myHmi::init(void)
{
	pTft->setTextColor(TFT_WHITE, TFT_BLACK);
	pTft->fillScreen(  TFT_BLACK);

	pHead->init();																			//!< Initialize the HEADER class
	pThm->init();																			//!< Initialize the THERMOSTAT class
	pThms->init();																			//!< Initialize the THM SELECT class
	pFoot->init();																			//!< Initialize the FOOTER class
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void redraw(void)
 * \brief	Redraw the HMI
 * \note	Redraw all the HMI parts
 * \param	void
 * \return	void
 */
void myHmi::redraw(void)
{
	pTft->setTextColor(TFT_WHITE, TFT_BLACK);
	pTft->fillScreen(  TFT_BLACK);
	pHead->redraw();																		//!< Redraw the HEADER class
	pThm->redraw();																			//!< Redraw the THERMOSTAT class
	pThms->redraw();																		//!< Redraw the THM SELECT class
	pFoot->redraw();																		//!< Redraw the FOOTER class
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void Presence(void)
 * \brief	MQTT send presence
 * \note	Send the presence information with MQTT
 * \param	void
 * \return	void
 */
void myHmi::Presence(void)
{
	ThmUnit.Presence = YES;
	pMqtt->sendBool("Piscigne/THMS/PRESENT", ThmUnit.Presence);
	isPresent();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void isPresent(void)
 * \brief	BACKLIGHT management
 * \note	If presence or touchscree used, set the TFT backlignt ON
 * \param	void
 * \return	void
 */
void myHmi::isPresent(void)
{
	if(ThmUnit.Present) pDio->setDisp(ThmUnit.Presence);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void isTouched(void)
 * \brief	Manage screen touched
 * \note	If screen is touched, analyze the area concerned
 * \param	void
 * \return	void
 */
void myHmi::isTouched(void)
{
	if(pTouch->Pressed())
	{
		Presence();																			//!< Screen is touched, inform on presence
		uint16_t TouchX, TouchY;
		TouchX = pTouch->X();
		TouchY = pTouch->Y();
		bool Status = false;
		if(!ThmUnit.Keyboard)																//!< Check if keyboard is actif
		{
			if(		TouchY < TOP_THM)	Status = pHead->isTouched(TouchX, TouchY);			//!< If HEADER touched 
			else if(TouchY < TOP_THMS)	Status = pThm->isTouched( TouchX, TouchY-TOP_THM);	//!< If THERMOSTAT touched 
			else if(TouchY < TOP_FOOT)	Status = pThms->isTouched(TouchX, TouchY-TOP_THMS);	//!< If THM SELECT touched 
			else						Status = pFoot->isTouched(TouchX, TouchY-TOP_FOOT);	//!< If FOOTER touched 
		}
		else																				//!< The keyboard is actif check if touched
		{
			if((TouchY > LOCK_KEY_TOP) & (TouchY < LOCK_KEY_BOTTOM)) Status = pLock->isTouched(TouchX, TouchY);
		}
		Serial.printf("X = %i, Y = %i, Clicked: %s\n", TouchX, TouchY, Status ? "ON" : "OFF");
		delay(TOUCH_DEBOUNCE);
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void loop()
 * \brief	LOOP function
 * \note	Loopback function used for pulling TOUCH SCREEN, HEADER area, THERMOSTAT area, THM SELECT area, FOOTER area and PRESENCE management
 * \param	
 * \return	void
 */
void myHmi::loop()
{
	if(!ThmUnit.Keyboard)
	{
		switch(iLoopHmi++)
		{
			case LOOP_HMI_TOUCH:	isTouched();	break;
			case LOOP_HMI_HEADER:	pHead->loop();	break;
			case LOOP_HMI_THM:		pThm->loop();	break;
			case LOOP_HMI_SELECT:	pThms->loop();	break;
			case LOOP_HMI_FOOTER:	pFoot->loop();	break;
			case LOOP_HMI_PRESENT:	isPresent();	break;
			default:				iLoopHmi = 0;
		}
	}
	else	isTouched();
	if(ThmUnit.Redraw) { redraw(); ThmUnit.Redraw = NO; }
}
