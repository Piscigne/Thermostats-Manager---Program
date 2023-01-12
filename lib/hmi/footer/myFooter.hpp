#ifndef MY_FOOTER__HPP
#define MY_FOOTER__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <time.h>

#include "tools/myType.h"
#include "tools/myDefine.h"
#include "tools/myWifi/myWifi.hpp"
#include "tools/myTime/MyTime.hpp"
#include "tools/myBitmap/myBitmap.hpp"

class myFooter
{
public:
	#define FOOT_ICO_HOME_X		8
	#define FOOT_ICO_HOME_Y		5

	#define FOOT_ICO_LAMP_X		208
	#define FOOT_ICO_LAMP_Y		5

	#define FOOT_TXT_TIME_C		122
	#define FOOT_TXT_TIME_X		50
	#define FOOT_TXT_TIME_Y		2
	#define FOOT_TXT_TIME_W		150
	#define FOOT_TXT_TIME_H		26
	#define FOOT_TXT_TIME_F		4	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

	#define FOOT_TXT_DATE_C		122
	#define FOOT_TXT_DATE_X		30
	#define FOOT_TXT_DATE_Y		28
	#define FOOT_TXT_DATE_W		170
	#define FOOT_TXT_DATE_H		15
	#define FOOT_TXT_DATE_F		1	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

	#define LOOP_FOOT_HOME		0
	#define LOOP_FOOT_TIME		1
	#define LOOP_FOOT_DATE		2
	#define LOOP_FOOT_LAMP		3

	myFooter(int32_t top);
	~myFooter() {};
	void loop();
	void init(void);
	void redraw(void);
	void dispHome(void);
	void dispLamp(void);
	void dispTime(void);
	void dispDate(void);
	void presence(void);
	void infoTouch(bool status);
	bool isTouched(uint16_t touchX, uint16_t touchY);

protected:

private:
	myBitmap*	pBmap;
	ICON_BOOL	icoLamp;
	ICON_BOOL	icoHome;

	int8_t		iLoopFoot	= 0;
	int32_t		Top;
	bool		LampActif	= THM_LAMP_ON;
	bool		HomeActif	= THM_PRESENCE;
	const char*	TimeTxt		= "%H : %M : %S";
};

#endif // MY_FOOTER__HPP
