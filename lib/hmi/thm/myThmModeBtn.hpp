/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myTHMmodeBtn.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_THM_MODE_BTN__HPP
#define MY_THM_MODE_BTN__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "tools/myType.hpp"
#include "tools/myEnum.hpp"
#include "tools/myDefine.hpp"
#include "tools/myBitmap/myBitmap.hpp"

#define THM_SELECT_ON	true
#define THM_SELECT_OFF	false

#define BTN_BGND_WIDTH		48							//!< Background coordinate definition
#define BTN_BGND_STEP		2

#define BTN_TXT_TARGET_X	34							//!< Target coordinate definition
#define BTN_TXT_TARGET_Y	1
#define BTN_TXT_TARGET_F	1							//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

#define BTN_ICO_MODE_X		14							//!< ICON coordinate definition
#define BTN_ICO_MODE_Y		7

class myTHMmodeBtn
{
public:
	myTHMmodeBtn(int32_t x, int32_t y, THM_MODES mode);
	~myTHMmodeBtn()	{};
	void init(		void);
	void redraw(	void);
	void setMode(	THM_MODES mode);
	void setSelect(	bool select);

private:
	void dispMode(	void);
	void dispBgnd(	void);
	void dispTarget(void);
	void dispSelect(void);

protected:
	int32_t		X;
	int32_t		Y;
	myBitmap*	pBmap;
	ICON_LIST	IconMode;								//!< To store the BITMAPs listF of icon MODE
	ICON_BOOL	IconOnOff;								//!< To store the BITMAPs ON & OFF of icon OFF
	ICON_BOOL	IconBG;									//!< To store the BITMAPs ON & OFF of Background
	THM_MODES	Mode	= MODE_VOID;					//!< To store the MODE  assigned of Button
	bool		Select	= THM_SELECT_OFF;				//!< To store the STATE assigned of Button (selected)
};

#endif // MY_THM_MODE_BTN__HPP
