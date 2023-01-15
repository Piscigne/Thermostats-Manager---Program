/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : mySDcard.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_SD_CARD__HPP
#define MY_SD_CARD__HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include "tools/myType.hpp"
#include "tools/myDefine.hpp"
#include <SPI.h>

#define FS_NO_GLOBALS
#include <SD.h>
#define SD_CS		5

class mySDcard
{
public:
	mySDcard()  {};
	~mySDcard() {};
	void init(void);
	void getSettings(void);

private:

protected:

};

#endif // MY_SD_CARD__HPP
