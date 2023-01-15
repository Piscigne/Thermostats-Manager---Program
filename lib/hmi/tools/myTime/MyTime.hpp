/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myTime.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_TIME__HPP
#define MY_TIME__HPP

#include <Arduino.h>
#include <time.h>

#include "tools/myType.hpp"
#include "tools/myDefine.hpp"

class myTime
{
public:
	#define TXT_TIME_BUFFER	16
	#define TXT_DATE_BUFFER	32

	myTime()  {};
	~myTime() {};
	void		getNtpTime( void);
	const char*	getDate(void);
	const char*	getTime(void);

private:

protected:
	const char*	TimeTxt	= "%H : %M : %S";
	const char*	DateTxt	= "%s %i %s %i";
};

#endif // MY_TIME__HPP
