/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myTHMmode.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_THM_MODE__HPP
#define MY_THM_MODE__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "thm/myThmModeBtn.hpp"
#include "Tools/myMqtt/myMqtt.hpp"

#define THM_BTN_OFF		0									//!< Button OFF  left coordinate
#define THM_BTN_HG		48									//!< Button HG   left coordinate
#define THM_BTN_ECO		96									//!< Button ECO  left coordinate
#define THM_BTN_ON		144									//!< Button ON   left coordinate
#define THM_BTN_CONF	192									//!< Button CONF left coordinate

#define THM_SEP_HIGHT	32									//!< HIGHT of separator lignes

#define THM_ICO_MODE_X	4									//!< MODE Icon coordinate definition
#define THM_ICO_MODE_Y	15

class myTHMmode
{
public:
	myTHMmode(int32_t top);
	~myTHMmode()	{};
	void init(		void);
	void redraw(	void);
	void updateMode(void);
	bool isTouched(	uint16_t touchX, uint16_t touchY);

private:
	void dispSep(	void);
	void sendMqtt(	void);

protected:
	int32_t			Top;									//!< To store the offset of Footer
	bool			Select = THM_SELECT_OFF;				//!< State of Button (selected)
	myTHMmodeBtn*	pModeCONF;								//!< Pointer to the Button CONF
	myTHMmodeBtn*	pModeON;								//!< Pointer to the Button ON
	myTHMmodeBtn*	pModeECO;								//!< Pointer to the Button ECO
	myTHMmodeBtn*	pModeHG;								//!< Pointer to the Button HG
	myTHMmodeBtn*	pModeOFF;								//!< Pointer to the Button OFF
};

#endif // MY_THM_MODE__HPP
