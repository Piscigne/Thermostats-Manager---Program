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
	void Callback(char* topic, byte* message, unsigned int length);
	void Reconnect(  void);
	void setTempExt( char* msg);
	void setpresence(char* msg);
	void setThm(	 char* msg, int thm);

protected:

private:
	int TopicOff;
};

#endif // MY_MQTT__HPP
