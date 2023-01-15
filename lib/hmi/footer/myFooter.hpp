/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myFooter.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_FOOTER__HPP
#define MY_FOOTER__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <time.h>

#include "tools/myType.hpp"
#include "tools/myDefine.hpp"
#include "tools/myWifi/myWifi.hpp"
#include "tools/myTime/MyTime.hpp"
#include "Tools/myMqtt/myMqtt.hpp"
#include "tools/myBitmap/myBitmap.hpp"

#define FOOT_ICO_HOME_X		8								//!< HOME Icon coordinate definition
#define FOOT_ICO_HOME_Y		5
#define FOOT_ICO_HOME_W		40

#define FOOT_ICO_LAMP_X		208								//!< LAMP Icon coordinate definition
#define FOOT_ICO_LAMP_Y		5

#define FOOT_BTN_HOME_XMAX	50								//!< Define the min and max of touch zones
#define FOOT_BTN_LAMP_XMIN	180

#define FOOT_TXT_TIME_C		122								//!< TIME text coordinate and font definition
#define FOOT_TXT_TIME_X		50
#define FOOT_TXT_TIME_Y		2
#define FOOT_TXT_TIME_W		150
#define FOOT_TXT_TIME_H		26
#define FOOT_TXT_TIME_F		4								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

#define FOOT_TXT_DATE_C		122								//!< DATE text coordinate and font definition
#define FOOT_TXT_DATE_X		30
#define FOOT_TXT_DATE_Y		28
#define FOOT_TXT_DATE_W		170
#define FOOT_TXT_DATE_H		15
#define FOOT_TXT_DATE_F		1								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

#define LOOP_FOOT			0								//!< LOOP index definition
#define LOOP_FOOT_TIME		1
#define LOOP_FOOT_DATE		2

class myFooter
{
public:
	myFooter(int32_t top);
	~myFooter() {};
	void loop();
	void init(void);
	void redraw(void);
	bool isTouched(uint16_t touchX, uint16_t touchY);

private:
	void redrawIf(void);
	void dispHome(void);
	void dispLamp(void);
	void dispTime(void);
	void dispDate(void);
	void homeTouch(void);
	void lampTouch(void);
	void rebootAt(const char* now);

protected:
	myBitmap*	pBmap;
	ICON_BOOL	icoHome;									//!< To store the BITMAPs ON & OFF of icon HOME
	ICON_BOOL	icoLamp;									//!< To store the BITMAPs ON & OFF of icon LAMP
	int32_t		Top;										//!< To store the offset of Footer
	bool		HomeActif	= THM_PRESENCE;					//!< Memory of HOME status
	bool		LampActif	= THM_LAMP_ON;					//!< Memory of LAMP status
	const char*	TimeTxt		= "%H : %M : %S";				//!< String format to display TIME
	int8_t		iLoopFoot	= 0;							//!< Initialize the LOOP index
};

#endif // MY_FOOTER__HPP
