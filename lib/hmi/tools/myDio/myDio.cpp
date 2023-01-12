#include "tools/myDio/myDio.hpp"

extern THM ThmUnit;

void myDio::init(void)
{
	pinMode(DIO_IO1_TFT,	OUTPUT);	digitalWrite(DIO_IO1_TFT,	THM_LAMP_ON);
	pinMode(DIO_IO2_LAMP,	OUTPUT);	digitalWrite(DIO_IO2_LAMP,	THM_LAMP_OFF);
	pinMode(DIO_LED_RED,	OUTPUT);	digitalWrite(DIO_LED_RED,	THM_LED_OFF);
	pinMode(DIO_LED_BLUE,	OUTPUT);	digitalWrite(DIO_LED_BLUE,	THM_LED_OFF);
	pinMode(DIO_LED_GREEN,	OUTPUT);	digitalWrite(DIO_LED_GREEN,	THM_LED_OFF);
}

void myDio::setDisp(bool state)
{
	digitalWrite(DIO_IO1_TFT, state);
}

void myDio::setLamp(bool state)
{
	digitalWrite(DIO_IO2_LAMP, state);
}

void myDio::setLeds(int8_t red, int8_t green, int8_t blue)
{
	digitalWrite(DIO_LED_RED,	 red);
	digitalWrite(DIO_LED_BLUE,	 blue);
	digitalWrite(DIO_LED_GREEN,	 green);
}

void myDio::updateStatus(void)
{
	if(ThmUnit.Status != StatusActif)
	{
		switch(ThmUnit.Status)
		{	//								Red	  Green	Blue
			case STATUS_INIT:		setLeds(LOW,  HIGH, HIGH);	break;	// Yellow
			case STATUS_NORMAL:		setLeds(LOW,  HIGH, LOW);	break;	// Green
			case STATUS_MQTT_OK:	setLeds(HIGH, LOW,  HIGH);	break;	// Purple
			case STATUS_WIFI_OK:	setLeds(LOW,  LOW,  HIGH);	break;	// Blue
			case STATUS_TOUCH_OK:	setLeds(HIGH, HIGH,  LOW);	break;	// Brown
			default:				setLeds(HIGH, LOW,  LOW);	break;	// Red
		}
		StatusActif = ThmUnit.Status;
	}
}

void myDio::loop(void)
{
	updateStatus();
}
