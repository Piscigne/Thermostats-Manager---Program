/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myThm.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_THM__HPP
#define MY_THM__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "tools/myType.hpp"
#include "tools/myDefine.hpp"
#include "tools/myBitmap/myBitmap.hpp"
#include "thm/myThmMode.hpp"

#define THM_MODE_SWITCH	100								//!< Y position of MODE buttons

#define THM_TXT_LABEL_X	30								//!< LABEL text coordinate and font definition
#define THM_TXT_LABEL_C	120
#define THM_TXT_LABEL_Y	4
#define THM_TXT_LABEL_W	180
#define THM_TXT_LABEL_H	30
#define THM_TXT_LABEL_F	4								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

#define THM_TXT_TEMP_X	50								//!< TEMPERATURE text coordinate and font definition
#define THM_TXT_TEMP_C	185
#define THM_TXT_TEMP_Y	30
#define THM_TXT_TEMP_W	100
#define THM_TXT_TEMP_H	50
#define THM_TXT_TEMP_F	7								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
#define THM_TXT_TEMP_UF	4								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
#define THM_TXT_TEMP_B	16								//!< Text buffer size

#define THM_TXT_MODE_X	1								//!< MODE text coordinate and font definition
#define THM_TXT_MODE_C	34
#define THM_TXT_MODE_Y	80
#define THM_TXT_MODE_W	50
#define THM_TXT_MODE_H	20
#define THM_TXT_MODE_F	2								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

#define THM_TXT_TARG_X	100								//!< TARGET text coordinate and font definition
#define THM_TXT_TARG_L	235
#define THM_TXT_TARG_Y	80
#define THM_TXT_TARG_W	135
#define THM_TXT_TARG_H	20
#define THM_TXT_TARG_F	2								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
#define THM_TXT_TARG_B	24								//!< Text buffer size

#define THM_ICO_STATE_X	8								//!< STATE Icon coordinate definition
#define THM_ICO_STATE_Y	30
#define THM_ICO_STATE_W	50
#define THM_ICO_STATE_H	46

class myThm
{
public:
	myThm(int32_t top);
	~myThm() {};
	void loop();
	void init(		void);
	void redraw(	void);
	bool isTouched( uint16_t touchX, uint16_t touchY);

private:
	void redrawIf(	void);
	void dispLabel(	void);
	void dispTemp(	void);
	void dispTarget(void);
	void dispMode(	void);
	void dispModeIf(void);
	void dispState(	void);
	void setActif(	void);

protected:
	myBitmap*	pBmap;
	myTHMmode*	pMode;
	ICON_BOOL	IconState;								//!< To store the BITMAPs ON & OFF of icon HEATER STATE
	int32_t		Top;									//!< To store the offset of Footer
	THM_DATA	ThmActif;								//!< Memory of THERMOSTAT BUTTON data
	int8_t		ThmSelected;							//!< Index of selected Button
	const char*	TempTxt	= "%4.1f";						//!< String format to display TEMPERATURE
	const char*	TargTxt	= "Consigne : %4.1f`C";			//!< String format to display TARGET TMP
	int iLoopThm		= 0;							//!< Initialize the LOOP index
};

#endif // MY_THM__HPP
