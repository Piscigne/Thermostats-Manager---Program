/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myLock.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_LOCK__HPP
#define MY_LOCK__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "tools/MyType.hpp"
#include "tools/myDefine.hpp"

#define KEYBOARD_X	20								//!< Background coordinate definition
#define KEYBOARD_Y	50
#define KEYBOARD_W	200
#define KEYBOARD_H	255
#define KEYBOARD_B	2								//!< Border width definition

#define DISPLAY_X	10								//!< Row and Column coordinate definition
#define DISPLAY_Y	5
#define DISPLAY_M	100
#define DISPLAY_W	180
#define DISPLAY_H	26

#define KEY_T		36								//!< Keys coordinate definition
#define KEY_L		5
#define KEY_S		4
#define KEY_W		60
#define KEY_H		50
#define KEY_R		8
#define KEY_F		4								//!< Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

class myLock
{
public:
	myLock()  {};
	~myLock() {};
	void loop();
	void init();
	bool isTouched(uint16_t touchX, uint16_t touchY);

private:
	void drawKeys(void);
	void pushKeys(int8_t IndexX, int8_t IndexY);
	void checkCode(void);

protected:
	char	Code[LOCK_CODE_LEN];					//!< To store the entry code data
	char	Mask[LOCK_CODE_LEN];					//!< To store the entry star characters
	int8_t	CodeIndex;								//!< Index of curent input
	int8_t	CodeLen;
};

#endif // MY_LOCK__HPP