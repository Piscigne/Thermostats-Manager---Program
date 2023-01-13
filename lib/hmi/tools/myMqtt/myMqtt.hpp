#ifndef MY_MQTT__HPP
#define MY_MQTT__HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "tools/myType.h"
#include "tools/myDefine.h"

class myMqtt
{
public:
	myMqtt()  {};
	~myMqtt() {};
	void loop(void);
	void init(void);
	void sendStr(	 const char* topic, const char* str);
	void sendInt(	 const char* topic, int  value);
	void sendBool(	 const char* topic, bool state);
	void Callback(char* topic, byte* message, unsigned int length);

private:
	void setThm(	 char* msg, int thm);
	void setLeds(	 char* msg);
	void setTempExt( char* msg);
	void setPresence(char* msg);
	void Reconnect(void);

protected:
	int TopicOff;
};

#endif // MY_MQTT__HPP
