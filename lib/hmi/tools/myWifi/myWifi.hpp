#ifndef MY_WIFI__HPP
#define MY_WIFI__HPP

#include <Arduino.h>
#include <WiFi.h>

#include "tools/myType.hpp"
#include "tools/myDefine.hpp"
#include "tools/myDio/myDio.hpp"

class myWifi
{
public:
	myWifi();
	~myWifi() {};
	void loop(void);
	void init(void);
	void Reconnect(void);
	const char*	getIp(void);
	const char*	getSsid(void);
	int8_t		getRssi(void);

private:

protected:
	const char* SSID;
	const char* PASS;
};

#endif // MY_WIFI__HPP
