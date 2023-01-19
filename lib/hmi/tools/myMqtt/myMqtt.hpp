/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myMqtt.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_MQTT__HPP
#define MY_MQTT__HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "tools/myType.hpp"
#include "tools/myEnum.hpp"
#include "tools/myDefine.hpp"
#include "tools/myDio/myDio.hpp"

class myMqtt
{
public:
	myMqtt()  {};
	~myMqtt() {};
	void loop(void);
	void init(void);
	void sendStr( const char* topic, const char* str);
	void sendInt( const char* topic, int  value);
	void sendBool(const char* topic, bool state);
	void Callback(char* topic, byte* message, unsigned int length);

private:
	void setThm(	 char* msg, int thm);
	void setEdf(	 char* msg);
	void setLeds(	 char* msg);
	void setTempExt( char* msg);
	void setPresence(char* msg);
	void Reconnect(void);

protected:
	int TopicOff;								//!< TOPIC offset used to separate the main Topic and the order
};

#endif // MY_MQTT__HPP
