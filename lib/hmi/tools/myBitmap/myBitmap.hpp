#ifndef MY_BITMAP__HPP
#define MY_BITMAP__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <PNGdec.h>
#include <Print.h>
#include <SPI.h>

#include "tools/myType.h"
#include "tools/myDefine.h"

class myBitmap
{
public:
	myBitmap()  {};
	~myBitmap() {};
	void drawARRAY(		 int32_t x, int32_t y, const BITMAP* img);
	void drawARRAYbutton(int32_t x, int32_t y, ICON_BOOL*	 img, bool   state);
	void drawARRAYlist(	 int32_t x, int32_t y, ICON_LIST*	 img, int8_t index);

protected:

private:

};

#endif // MY_BITMAP__HPP
