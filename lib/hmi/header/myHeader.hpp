#ifndef MY_HEADER__HPP
#define MY_HEADER__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "tools/myType.h"
#include "tools/myDefine.h"
#include "tools/myLock/myLock.hpp"
#include "tools/myBitmap/myBitmap.hpp"

	#define HEAD_SEP_LINE_C		0x3186
	#define HEAD_BACKGROUND_X	0
	#define HEAD_BACKGROUND_Y	0
	#define HEAD_BACKGROUND_W	240
	#define HEAD_BACKGROUND_H	36

	#define HEAD_ICO_LOCK_X		2
	#define HEAD_ICO_LOCK_Y		2

	#define HEAD_ICO_WIFI_X		208
	#define HEAD_ICO_WIFI_Y		2

	#define HEAD_TXT_CENTER		1
	#define HEAD_TXT_TEMP_C		120
	#define HEAD_TXT_TEMP_X		30
	#define HEAD_TXT_TEMP_Y		2
	#define HEAD_TXT_TEMP_W		180
	#define HEAD_TXT_TEMP_H		26
	#define HEAD_TXT_TEMP_F		4	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
	#define HEAD_TXT_TEMP_B		16	// text buffer size

	#define HEAD_TXT_MINMAX_C	120
	#define HEAD_TXT_MINMAX_X	30
	#define HEAD_TXT_MINMAX_Y	26
	#define HEAD_TXT_MINMAX_W	180
	#define HEAD_TXT_MINMAX_H	8
	#define HEAD_TXT_MINMAX_F	1	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
	#define HEAD_TXT_MINMAX_B	32	// text buffer size

class myHeader
{
public:
	myHeader(int32_t top);
	~myHeader() {};
	void loop();
	void init(void);
	void redraw(void);
	bool isTouched(uint16_t touchX, uint16_t touchY);

private:
	void redrawIf(void);
	void dispLock(void);
	void dispExtT(void);
	void dispMinMax(void);
	void dispWifi(void);
	void unlock(void);

protected:
	myBitmap*	pBmap;
	ICON_BOOL	icoLock;
	ICON_LIST	icoWifi;
	int32_t		Top;
	bool		LockActif	= THM_UNLOCKED;
	int8_t		RssiActif	= WIFI_VOID;
	float		TempActif	= -88.8;
	float		MaxActif	= -88.8;
	float		MinActif	= -88.8;
	const char*	TempTxt		= "Ext. %4.1f`C";
	const char*	TempMinMax	= "Mini %3.1f - Maxi %3.1f";
};

#endif // MY_HEADER__HPP
