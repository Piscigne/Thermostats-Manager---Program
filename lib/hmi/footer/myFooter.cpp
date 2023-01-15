/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myFooter.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include <footer/myFooter.hpp>

#include "resources/bitmap/footer/home/homeON.h"										//!< Include the bitmaps of HOME button
#include "resources/bitmap/footer/home/homeOFF.h"

#include "resources/bitmap/footer/lamp/lampeON.h"										//!< Include the bitmaps of LAMP button
#include "resources/bitmap/footer/lamp/lampeOFF.h"

extern TFT_eSPI* pTft;																	//!< Pointer to the TFT screen class
extern THM		 ThmUnit;																//!< Pointer to the UNIT data structure
extern myDio*	 pDio;																	//!< Pointer to the DIO screen class
extern myWifi*	 pWifi;																	//!< Pointer to the WIFI class
extern myTime*	 pTime;																	//!< Pointer to the TIME class
extern myMqtt*	 pMqtt;																	//!< Pointer to the MQTT screen class

hw_timer_t*		pTimerTime	= NULL;														//!< Timer 1 tic each 1S
hw_timer_t*		pTimerDate	= NULL;														//!< Timer 2 tic each 1mn
bool			UpdateTime	= true;														//!< Flag to update TIME when equal at true
bool			UpdateDate	= true;														//!< Flag to update DATE when equal at true

void IRAM_ATTR onTimeTime()		{ UpdateTime = true; }									//!< Timer 1 callback function (called each 1S)
void IRAM_ATTR onTimeDate()		{ UpdateDate = true; }									//!< Timer 2 callback function (called each 1mn)

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		myFooter(int32_t top)
 * \brief	Create the class FOOTER
 * \note	Create the FOOTER class
 * \param	[in] top	as int32_t	- Top offset of Footer
 * \return	
 */
myFooter::myFooter(int32_t top)
{
	Top = top;

	icoLamp.IconON	= &lampeON;		icoLamp.IconOFF	= &lampeOFF;
	icoHome.IconON  = &homeON;		icoHome.IconOFF = &homeOFF;

	pTimerTime = timerBegin(1, 80, true);	timerAttachInterrupt(pTimerTime, &onTimeTime, true);	timerAlarmWrite(pTimerTime,  1000000, true);
	pTimerDate = timerBegin(2, 80, true);	timerAttachInterrupt(pTimerDate, &onTimeDate, true);	timerAlarmWrite(pTimerDate, 60000000, true);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void init(void)
 * \brief	INIT the FOOTER class
 * \note	Initialize the FOOTER class
 * \param	void
 * \return	void
 */
void myFooter::init(void)
{
	redraw();
	timerAlarmEnable(pTimerTime);														//!< Start the Timer 1 (Tic each 1S)
	timerAlarmEnable(pTimerDate);														//!< Start the Timer 2 (Tic each 1mn)
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispHome(void)
 * \brief	HOME icon display
 * \note	Display the HOME (presence) icon
 * \param	void
 * \return	void
 */
void myFooter::dispHome(void)
{
	pTft->fillRect(		   FOOT_ICO_HOME_X, Top+FOOT_ICO_HOME_Y, icoHome.IconON->width, icoHome.IconON->height, TFT_BLACK);
	pBmap->drawARRAYbutton(FOOT_ICO_HOME_X, Top+FOOT_ICO_HOME_Y, &icoHome, ThmUnit.Presence);
	HomeActif = ThmUnit.Presence;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispLamp(void)
 * \brief	LAMP icon display
 * \note	Display the LAMP icon
 * \param	void
 * \return	void
 */
void myFooter::dispLamp(void)
{
	pTft->fillRect(		   FOOT_ICO_LAMP_X, Top+FOOT_ICO_LAMP_Y, icoLamp.IconON->width, icoLamp.IconON->height, TFT_BLACK);
	pBmap->drawARRAYbutton(FOOT_ICO_LAMP_X, Top+FOOT_ICO_LAMP_Y, &icoLamp, ThmUnit.LedEscalier);
	pDio->setLamp(ThmUnit.LedEscalier);
	LampActif = ThmUnit.LedEscalier;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispTime(void)
 * \brief	TIME display
 * \note	Display the Time (each 1S)
 * \param	void
 * \return	void
 */
void myFooter::dispTime(void)
{
	if(UpdateTime)
	{
		UpdateTime		= false;
		const char* Now	= pTime->getTime();
		pTft->setTextDatum(TXT_TOP_CENTER);
		pTft->setTextColor(TFT_LIGHTGREY, TFT_BLACK, true);
		pTft->fillRect(FOOT_TXT_TIME_X, Top+FOOT_TXT_TIME_Y, FOOT_TXT_TIME_W, FOOT_TXT_TIME_H, TFT_BLACK);
		pTft->drawString(Now, FOOT_TXT_TIME_C, Top+FOOT_TXT_TIME_Y, FOOT_TXT_TIME_F);
		rebootAt(Now);																	//!< Call the dayly reboot function
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispDate(void)
 * \brief	DATE display
 * \note	Display the Date (each 1mn)
 * \param	void
 * \return	void
 */
void myFooter::dispDate(void)
{
	if(UpdateDate)
	{
		UpdateDate = false;
		pTft->setTextDatum(TXT_TOP_CENTER);
		pTft->setTextColor(TFT_LIGHTGREY, TFT_BLACK, true);
		pTft->fillRect(FOOT_TXT_DATE_X, Top+FOOT_TXT_DATE_Y, FOOT_TXT_DATE_W, FOOT_TXT_DATE_H, TFT_BLACK);
		pTft->drawString(pTime->getDate(), FOOT_TXT_DATE_C, Top+FOOT_TXT_DATE_Y, FOOT_TXT_DATE_F);
		ThmUnit.Wifi.Rssi = pWifi->getRssi();											//!< Update the RSSI value each minutes
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void rebootAt(void)
 * \brief	REBOOT dayly
 * \note	reboot the unit at specified time
 * \param	void
 * \return	void
 */
void myFooter::rebootAt(const char* now)
{
	if(!strcmp(now, ThmUnit.RebootAt))													//!< Reboot dayly at the specified time
	{
		Serial.printf("It's %s, time to REBOOT...", now);
		ESP.restart();
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
* \fn		void redraw(void)
 * \brief	Redraw the FOOTER
 * \note	Redraw all the FOOTER parts
 * \param	void
 * \return	void
 */
void myFooter::redraw(void)
{
	dispTime();
	dispDate();
	dispHome();
	dispLamp();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void redrawIf(void)
 * \brief	REDRAW IF updated
 * \note	Redraw all the FOOTER parts if an item is upgraded
 * \param	void
 * \return	void
 */
void myFooter::redrawIf(void)
{
	if(	ThmUnit.Presence	!= HomeActif |
		ThmUnit.LedEscalier	!= LampActif)
	{
		redraw();
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void homeTouch(void)
 * \brief	HOME clicked
 * \note	If Home is clicked, switch the presence
 * \param	void
 * \return	void
 */
void myFooter::homeTouch(void)
{
	ThmUnit.Presence = !ThmUnit.Presence;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void lampTouch(void)
 * \brief	LAMP clicked
 * \note	If Lamp is clicked, switch the LED relay state
 * \param	void
 * \return	void
 */
void myFooter::lampTouch(void)
{
	ThmUnit.LedEscalier = !ThmUnit.LedEscalier;
	pMqtt->sendBool("Piscigne/THMS/LEDS", ThmUnit.LedEscalier ? true : false);
	delay(500);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void isTouched(void)
 * \brief	Manage screen touched
 * \note	If screen is touched, analyze the area concerned
 * \param	[in] touchX	as uint16_t	- X coordinate of touched point
 * \param	[in] touchY	as uint16_t	- Y coordinate of touched point
 * \return	bool - TRUE if clicked in the valid area
 */
bool myFooter::isTouched(uint16_t touchX, uint16_t touchY)
{
	bool Clicked = false;
	if(		touchX < FOOT_BTN_HOME_XMAX)	{ homeTouch(); Clicked = true; }
	else if(touchX > FOOT_BTN_LAMP_XMIN)	{ lampTouch(); Clicked = true; }
	return Clicked;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void loop()
 * \brief	LOOP function
 * \note	Loopback function used for pulling the Footer redraw, TIME display and DATE display
 * \param	
 * \return	void
 */
void myFooter::loop()
{
	if(!ThmUnit.Keyboard)
	{
		redrawIf();
		switch(iLoopFoot++)
		{
			case LOOP_FOOT:			redrawIf();		break;
			case LOOP_FOOT_TIME:	dispTime();		break;
			case LOOP_FOOT_DATE:	dispDate();		break;
			default:				iLoopFoot = 0;
		}
	}
}
