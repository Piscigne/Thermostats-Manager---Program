#ifndef MY_LOCK__HPP
#define MY_LOCK__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "tools/MyType.h"
#include "tools/myDefine.h"

#define KEYBOARD_X	20
#define KEYBOARD_Y	50
#define KEYBOARD_W	200
#define KEYBOARD_H	255
#define KEYBOARD_B	2

#define DISPLAY_X	10
#define DISPLAY_Y	5
#define DISPLAY_M	100
#define DISPLAY_W	180
#define DISPLAY_H	26

#define KEY_T		36
#define KEY_L		5
#define KEY_S		4
#define KEY_W		60
#define KEY_H		50
#define KEY_R		8
#define KEY_F		4	// Font size 1=8p, 2=16p, 4=26p, 7=48p 7seg

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
	char	Code[LOCK_CODE_LEN];
	char	Mask[LOCK_CODE_LEN];
	int8_t	CodeIndex;
	int8_t	CodeLen;
};

#endif // MY_LOCK__HPP