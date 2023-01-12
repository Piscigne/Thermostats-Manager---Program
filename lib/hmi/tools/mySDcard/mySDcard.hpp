#ifndef MY_SD_CARD__HPP
#define MY_SD_CARD__HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include "tools/myType.h"
#include "tools/myDefine.h"
#include <SPI.h>
#define FS_NO_GLOBALS
#include <SD.h>
//#include <FS.h>
#define SD_CS		5

class mySDcard
{
public:
	mySDcard()  {};
	~mySDcard() {};
	void init(void);
	void getSettings(void);

protected:

private:

};

#endif // MY_SD_CARD__HPP
