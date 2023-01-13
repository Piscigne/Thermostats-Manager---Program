#ifndef MY_DIO__HPP
#define MY_DIO__HPP

#include <Arduino.h>

#include "tools/myType.h"
#include "tools/myDefine.h"

class myDio
{
public:
	myDio()  {};
	~myDio() {};
	void loop(void);
	void init(void);
	void updateStatus(void);
	void setDisp(bool state);
	void setLamp(bool state);
	void setLeds(int8_t red, int8_t green, int8_t blue);

private:

protected:
	int8_t StatusActif = STATUS_ERROR;
};

#endif // MY_DIO__HPP
