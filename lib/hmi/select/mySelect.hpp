#ifndef MY_SELECT__HPP
#define MY_SELECT__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "tools/myType.h"
#include "tools/myDefine.h"
#include "select/mySelectBtn.hpp"

class mySelect
{
public:
	#define SEL_SEP_TOP		0
	#define SEL_SEP_MID		50
	#define SEL_SEP_BOT		100
	#define SEL_SEP_LEFT	0
	#define SEL_SEP_MID_1	80
	#define SEL_SEP_MID_2	160
	#define SEL_SEP_RIGHT	239
	#define SEL_SEP_WIDTH	240
	#define SEL_SEP_HEIGH	100

	mySelect(int32_t top);
	~mySelect() {};
	void loop();
	void init(void);
	void redraw(void);
	bool isTouched(uint16_t touchX, uint16_t touchY);

private:
	void drawSep(void);

protected:
	int32_t			Top;
	int				iLoopSelect = THERMOSTAT1;
	mySelectBtn*	ThmBtn[THERMOSTAT_NBR];
};

#endif // MY_SELECT__HPP
