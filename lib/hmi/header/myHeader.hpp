/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myHeader.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_HEADER__HPP
#define MY_HEADER__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "tools/myType.hpp"
#include "tools/myDefine.hpp"
#include "tools/myLock/myLock.hpp"
#include "tools/myBitmap/myBitmap.hpp"

#define HEAD_SEP_LINE_C		0x3186							//!< Line separator color definition

#define HEAD_BACKGROUND_X	0								//!< Background coordinate definition
#define HEAD_BACKGROUND_Y	0
#define HEAD_BACKGROUND_W	240
#define HEAD_BACKGROUND_H	36

#define HEAD_ICO_LOCK_X		2								//!< LOCK Icon coordinate definition
#define HEAD_ICO_LOCK_Y		2

#define HEAD_ICO_WIFI_X		208								//!< WIFI Icon coordinate definition
#define HEAD_ICO_WIFI_Y		2

#define HEAD_TXT_CENTER		1								//!< TEMPERATURE text coordinate and font definition
#define HEAD_TXT_TEMP_C		120
#define HEAD_TXT_TEMP_X		30
#define HEAD_TXT_TEMP_Y		2
#define HEAD_TXT_TEMP_W		180
#define HEAD_TXT_TEMP_H		26
#define HEAD_TXT_TEMP_F		4								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
#define HEAD_TXT_TEMP_B		16								//!< Text buffer size

#define HEAD_TXT_MINMAX_C	120								//!< MIN MAX text coordinate and font definition
#define HEAD_TXT_MINMAX_X	30
#define HEAD_TXT_MINMAX_Y	26
#define HEAD_TXT_MINMAX_W	180
#define HEAD_TXT_MINMAX_H	8
#define HEAD_TXT_MINMAX_F	1								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
#define HEAD_TXT_MINMAX_B	32								//!< Text buffer size

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
	ICON_BOOL	icoLock;									//!< To store the BITMAPs ON & OFF of icon LOCK
	ICON_LIST	icoWifi;									//!< To store the BITMAPs list of icon WIFI
	int32_t		Top;										//!< To store the offset of Header
	bool		LockActif	= THM_UNLOCKED;					//!< Memory of LOCK state
	THM_WIFI	RssiActif	= WIFI_VOID;					//!< Memory of WIFI status
	float		TempActif	= -88.8;						//!< Memory of TEMPERATURE value
	float		MaxActif	= -88.8;						//!< Memory of TEMP. MAXI value
	float		MinActif	= -88.8;						//!< Memory of TEMP. MINI value
	const char*	TempTxt		= "Ext. %4.1f`C";				//!< String format to display TEMPERATURE
	const char*	TempMinMax	= "Mini %3.1f - Maxi %3.1f";	//!< String format to display TEMP MINI and MAXI
};

#endif // MY_HEADER__HPP
