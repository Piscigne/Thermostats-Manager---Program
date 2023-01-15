/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : mySelectBtn.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_SELECT_BTN__HPP
#define MY_SELECT_BTN__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "tools/myType.hpp"
#include "tools/myEnum.hpp"
#include "tools/myDefine.hpp"
#include "tools/myBitmap/myBitmap.hpp"

#define BTN_STATE_ON	true
#define BTN_STATE_OFF	false

#define BTN_FILL_BG_X	0								//!< Button background coordinate definition
#define BTN_FILL_BG_Y	0
#define BTN_FILL_BG_W	80
#define BTN_FILL_BG_H	50

#define BTN_TXT_LABEL_X	40								//!< LABEL coordinate and font definition
#define BTN_TXT_LABEL_Y	1
#define BTN_TXT_LABEL_F	2								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

#define BTN_TXT_TEMP_X	50								//!< TEMP text coordinate and font definition
#define BTN_TXT_TEMP_Y	17
#define BTN_TXT_TEMP_F	4								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
#define BTN_TXT_TEMP_B	8								//!< Text buffer size

#define BTN_TXT_TARG_X	75								//!< TARGET text coordinate and font definition
#define BTN_TXT_TARG_Y	40
#define BTN_TXT_TARG_F	1								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg
#define BTN_TXT_TARG_B	8								//!< Text buffer size

#define BTN_TXT_MODE_X	5								//!< MODE text coordinate and font definition
#define BTN_TXT_MODE_Y	40
#define BTN_TXT_MODE_F	1								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

#define BTN_ICO_STATE_X	4								//!< STATE Icon coordinate definition
#define BTN_ICO_STATE_Y	24

class mySelectBtn
{
public:
	mySelectBtn(int32_t x, int32_t y, int8_t index);
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
	ICON_BOOL	IconState;								//!< To store the BITMAPs ON & OFF of icon HEATER STATE
	THM_DATA	ThmActif;								//!< Memory of HOME status
	const char*	TempTxt	 = "%4.1f";						//!< String format to display TEMP
	int			Index	 = 0;							//!< Initialize the LOOP index
};

#endif // MY_SELECT_BTN__HPP
