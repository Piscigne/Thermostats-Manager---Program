/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myBitmap.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_BITMAP__HPP
#define MY_BITMAP__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <PNGdec.h>
#include <Print.h>
#include <SPI.h>

#include "tools/myType.hpp"
#include "tools/myDefine.hpp"

unsigned short int myRGB(uint8_t r, uint8_t g, uint8_t b);

class myBitmap
{
public:
	myBitmap()  {};
	~myBitmap() {};
	void drawARRAY(		 int32_t x, int32_t y, const BITMAP* img);
	void drawARRAYbutton(int32_t x, int32_t y, ICON_BOOL*	 img, bool   state);
	void drawARRAYlist(	 int32_t x, int32_t y, ICON_LIST*	 img, int8_t index);

private:

protected:

};

#endif // MY_BITMAP__HPP
