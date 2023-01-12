#ifndef MY_THM__HPP
#define MY_THM__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "tools/myType.h"
#include "tools/myDefine.h"
#include "tools/myBitmap/myBitmap.hpp"
#include "thm/myThmMode.hpp"

class myThm
{
public:
	#define THM_MODE_SWITCH	100

	#define THM_TXT_LABEL_X	30
	#define THM_TXT_LABEL_C	120
	#define THM_TXT_LABEL_Y	4
	#define THM_TXT_LABEL_W	180
	#define THM_TXT_LABEL_H	30
	#define THM_TXT_LABEL_F	4	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

	#define THM_TXT_TEMP_X	50
	#define THM_TXT_TEMP_C	185
	#define THM_TXT_TEMP_Y	30
	#define THM_TXT_TEMP_W	100
	#define THM_TXT_TEMP_H	50
	#define THM_TXT_TEMP_F	7	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
	#define THM_TXT_TEMP_UF	4	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
	#define THM_TXT_TEMP_B	16	// text buffer size

	#define THM_TXT_MODE_X	1
	#define THM_TXT_MODE_C	34
	#define THM_TXT_MODE_Y	80
	#define THM_TXT_MODE_W	50
	#define THM_TXT_MODE_H	20
	#define THM_TXT_MODE_F	2	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

	#define THM_TXT_TARG_X	100
	#define THM_TXT_TARG_L	235
	#define THM_TXT_TARG_Y	80
	#define THM_TXT_TARG_W	135
	#define THM_TXT_TARG_H	20
	#define THM_TXT_TARG_F	2	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
	#define THM_TXT_TARG_B	24	// text buffer size

	#define THM_ICO_STATE_X	8
	#define THM_ICO_STATE_Y	30
	#define THM_ICO_STATE_W	50
	#define THM_ICO_STATE_H	46

	myThm(int32_t top);
	~myThm() {};
	void loop();
	void init(		void);
	void redraw(	void);
	void dispLabel(	void);
	void dispTemp(	void);
	void dispTarget(void);
	void dispMode(	void);
	void dispState(	void);
	void setActif(	void);
	bool isTouched( uint16_t touchX, uint16_t touchY);

protected:

private:
	int32_t		Top;
	myBitmap*	pBmap;
	myTHMmode*	pMode;
	ICON_BOOL	IconState;

	THM_DATA	ThmActif;
	int8_t		ThmSelected;

	int iLoopThm		= 0;
	const char*	TempTxt	= "%4.1f";
	const char*	TargTxt	= "Consigne : %4.1f`C";
};

#endif // MY_THM__HPP
