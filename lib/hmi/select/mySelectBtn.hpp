#ifndef MY_SELECT_BTN__HPP
#define MY_SELECT_BTN__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "tools/myType.h"
#include "tools/myDefine.h"
#include "tools/myBitmap/myBitmap.hpp"

#define BTN_STATE_ON	true
#define BTN_STATE_OFF	false

class mySelectBtn
{
public:
	#define BTN_FILL_BG_X	0
	#define BTN_FILL_BG_Y	0
	#define BTN_FILL_BG_W	80
	#define BTN_FILL_BG_H	50

	#define BTN_TXT_LABEL_X	40
	#define BTN_TXT_LABEL_Y	1
	#define BTN_TXT_LABEL_F	2

	#define BTN_TXT_TEMP_X	50
	#define BTN_TXT_TEMP_Y	17
	#define BTN_TXT_TEMP_F	4	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
	#define BTN_TXT_TEMP_B	8	// text buffer size

	#define BTN_TXT_TARG_X	75
	#define BTN_TXT_TARG_Y	40
	#define BTN_TXT_TARG_F	1	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
	#define BTN_TXT_TARG_B	8	// text buffer size

	#define BTN_TXT_MODE_X	5
	#define BTN_TXT_MODE_Y	40
	#define BTN_TXT_MODE_F	1	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

	#define BTN_ICO_STATE_X	4
	#define BTN_ICO_STATE_Y	24

	mySelectBtn(int32_t x, int32_t y, int index);
	~mySelectBtn()	{};
	void loop();
	void init(		void);
	void redraw(	void);

private:
	void redrawIf(	void);
	void dispLabel(	void);
	void dispTemp(	void);
	void dispTarget(void);
	void dispMode(	void);
	void dispState(	void);

protected:
	int32_t		X;
	int32_t		Y;
	myBitmap*	pBmap;
	ICON_BOOL	IconState;
	
	int			Index;
	THM_DATA	ThmActif;

	const char*	TempTxt	 = "%4.1f";
};

#endif // MY_SELECT_BTN__HPP
