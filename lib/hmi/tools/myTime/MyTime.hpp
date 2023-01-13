#ifndef MY_TIME__HPP
#define MY_TIME__HPP

#include <Arduino.h>
#include <time.h>

#include "tools/myType.h"
#include "tools/myDefine.h"

class myTime
{
public:
	#define TXT_TIME_BUFFER	16
	#define TXT_DATE_BUFFER	32

	myTime()  {};
	~myTime() {};
	void		getNtpTime( void);
	void		setDateTime(void);
	const char*	getDate(void);
	const char*	getTime(void);

private:

protected:
	const char*	TimeTxt	= "%H : %M : %S";
	const char*	DateTxt	= "%s %i %s %i";
};

#endif // MY_TIME__HPP
