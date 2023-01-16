/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myDio.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_DIO__HPP
#define MY_DIO__HPP

#include <Arduino.h>

#include "tools/myType.hpp"
#include "tools/myEnum.hpp"
#include "tools/myDefine.hpp"

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
	THM_STATUS StatusActif = STATUS_ERR;								//!< Memory of THERMOSTAT Status
};

#endif // MY_DIO__HPP
