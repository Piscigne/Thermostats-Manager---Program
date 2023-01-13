#include "tools/myLock/myLock.hpp"

extern TFT_eSPI* pTft;
extern THM		 ThmUnit;

char Keymap[4][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'#', '0', '%'}};

void myLock::init(void)
{
	ThmUnit.Keyboard = true;
	CodeLen	  = strlen(ThmUnit.LockPass);
	CodeIndex = 0;
	Code[CodeIndex] = '\0';
	Mask[CodeIndex] = '\0';
	drawKeys();
}

void myLock::drawKeys(void)
{
	int x, X, y, Y ;

	pTft->setTextFont(KEY_F);
	pTft->setTextDatum(TXT_TOP_CENTER);

	pTft->fillRect(KEYBOARD_X,			  KEYBOARD_Y,			 KEYBOARD_W,			  KEYBOARD_H,			   TFT_DARKGREY);
	pTft->fillRect(KEYBOARD_X+KEYBOARD_B, KEYBOARD_Y+KEYBOARD_B, KEYBOARD_W-KEYBOARD_B*2, KEYBOARD_H-KEYBOARD_B*2, TFT_LIGHTGREY);

	pTft->setTextColor(TFT_WHITE, TFT_BROWN, true);
	for(y=0; y<4; y++)
	{
		for(x=0; x<3; x++)
		{
			X = KEY_L+KEYBOARD_X + (KEY_W+KEY_S)*x;
			Y = KEY_T+KEYBOARD_Y + (KEY_H+KEY_S)*y;
			pTft->fillRoundRect(X, Y, KEY_W, KEY_H, KEY_R, TFT_BROWN);
			pTft->drawChar(Keymap[y][x], X+22, Y+14);
		}
	}
	pTft->setTextColor(TFT_BLACK, TFT_SKYBLUE, true);

	pTft->fillRect(KEYBOARD_X+DISPLAY_X, KEYBOARD_Y+DISPLAY_Y, DISPLAY_W, DISPLAY_H, TFT_SKYBLUE);
	pTft->drawString("?", KEYBOARD_X+DISPLAY_M, KEYBOARD_Y+DISPLAY_Y+4);
}

void myLock::checkCode(void)
{
	int8_t Len = strlen(Code);
	if(Len == CodeLen)
	{
		if(!strcmp(Code, ThmUnit.LockPass))
		{
			ThmUnit.Locked	 = NO;
			ThmUnit.Redraw	 = YES;
			ThmUnit.Keyboard = false;
		}
	}
	else if(Len > CodeLen)
	{
		ThmUnit.Locked	 = YES;
		ThmUnit.Redraw	 = YES;
		ThmUnit.Keyboard = false;
	}
}

void myLock::pushKeys(int8_t IndexX, int8_t IndexY)
{
	Code[CodeIndex] = Keymap[IndexY][IndexX];	Code[CodeIndex+1] = '\0';
	Mask[CodeIndex] = '*';						Mask[CodeIndex+1] = '\0';
	if(CodeIndex < LOCK_CODE_LEN) CodeIndex++;
	pTft->drawString(Mask, KEYBOARD_X+DISPLAY_M, KEYBOARD_Y+DISPLAY_Y*2);
	checkCode();
}

bool myLock::isTouched(uint16_t touchX, uint16_t touchY)
{
	bool	Clicked = false;
	int8_t	IndexX, IndexY;
	
	if(		touchX < KEYBOARD_X+KEY_W)			IndexX=0;
	else if(touchX < KEYBOARD_X+KEY_W*2)		IndexX=1;
	else										IndexX=2;

	if(		touchY < KEYBOARD_Y+KEY_T+KEY_H)	IndexY=0;
	else if(touchY < KEYBOARD_Y+KEY_T+KEY_H*2)	IndexY=1;
	else if(touchY < KEYBOARD_Y+KEY_T+KEY_H*3)	IndexY=2;
	else										IndexY=3;

	pushKeys(IndexX, IndexY);
	return Clicked;
}

void myLock::loop()
{
}
