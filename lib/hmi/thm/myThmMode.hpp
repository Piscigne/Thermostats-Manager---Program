#ifndef MY_THM_MODE__HPP
#define MY_THM_MODE__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "thm/myThmModeBtn.hpp"

class myTHMmode
{
public:
	#define THM_BTN_OFF		0
	#define THM_BTN_HG		48
	#define THM_BTN_ECO		96
	#define THM_BTN_ON		144
	#define THM_BTN_CONF	192
	#define THM_SEP_HIGHT	32

	#define THM_ICO_MODE_X	4
	#define THM_ICO_MODE_Y	15

	myTHMmode(int32_t top);
	~myTHMmode()	{};
	void init(		void);
	void redraw(	void);
	void updateMode(void);
	void dispSep(	void);
	bool isTouched(	uint16_t touchX, uint16_t touchY);

protected:

private:
	int32_t			Top;
	bool			Select = THM_SELECT_OFF;

	myTHMmodeBtn*	pModeCONF;
	myTHMmodeBtn*	pModeON;
	myTHMmodeBtn*	pModeECO;
	myTHMmodeBtn*	pModeHG;
	myTHMmodeBtn*	pModeOFF;
};

#endif // MY_THM_MODE__HPP
