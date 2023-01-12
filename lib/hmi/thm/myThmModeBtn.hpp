#ifndef MY_THM_MODE_BTN__HPP
#define MY_THM_MODE_BTN__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "tools/myType.h"
#include "tools/myDefine.h"
#include "tools/myBitmap/myBitmap.hpp"

#define THM_SELECT_ON		true
#define THM_SELECT_OFF		false

class myTHMmodeBtn
{
public:
	#define BTN_BGND_WIDTH	48
	#define BTN_BGND_STEP	2
	#define BTN_ICO_MODE_X	14
	#define BTN_ICO_MODE_Y	6

	myTHMmodeBtn(int32_t x, int32_t y, int8_t mode);
	~myTHMmodeBtn()	{};
	void init(		void);
	void redraw(	void);
	void setMode(	int8_t mode);
	void setSelect(	bool select);
	void dispMode(	void);
	void dispBgnd(	void);
	void dispSelect(void);

protected:

private:
	int32_t		X;
	int32_t		Y;
	myBitmap*	pBmap;
	ICON_LIST	IconMode;
	ICON_BOOL	IconOnOff;
	ICON_BOOL	IconBG;
	
	int8_t		Mode	 = THM_MODE_HG;
	bool		Select	 = THM_SELECT_OFF;
};

#endif // MY_THM_MODE_BTN__HPP
