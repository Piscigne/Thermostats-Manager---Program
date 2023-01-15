/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myDio.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include "tools/myDio/myDio.hpp"

extern THM ThmUnit;																//!< Pointer to the UNIT data structure

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void init(void)
 * \brief	INIT the DIO class
 * \note	Initialize the Digital Inputs Outputs class
 * \param	void
 * \return	void
 */
void myDio::init(void)
{
	pinMode(DIO_IO1_TFT,	OUTPUT);	digitalWrite(DIO_IO1_TFT,	THM_LAMP_ON);		//!< Outpout to control the TFT backlight
	pinMode(DIO_IO2_LAMP,	OUTPUT);	digitalWrite(DIO_IO2_LAMP,	THM_LAMP_OFF);		//!< Outpout to control the LED Relay Lamp
	pinMode(DIO_LED_RED,	OUTPUT);	digitalWrite(DIO_LED_RED,	THM_LED_OFF);		//!< Outpout to control the LED1 RED
	pinMode(DIO_LED_BLUE,	OUTPUT);	digitalWrite(DIO_LED_BLUE,	THM_LED_OFF);		//!< Outpout to control the LED1 BLUE
	pinMode(DIO_LED_GREEN,	OUTPUT);	digitalWrite(DIO_LED_GREEN,	THM_LED_OFF);		//!< Outpout to control the LED1 GREEN
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void setDisp(bool state)
 * \brief	TFT BACKLIGHT control
 * \note	Controle the TFT BACKLIGHT
 * \param	[in] state	as bool	- State of TFT Backlight
 * \return	void
 */
void myDio::setDisp(bool state)
{
	digitalWrite(DIO_IO1_TFT, state);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void setLamp(bool state)
 * \brief	LED LAMP control
 * \note	Controle the LED LAMP Relay
 * \param	[in] state	as bool	- State of LED Lamp
 * \return	void
 */
void myDio::setLamp(bool state)
{
	digitalWrite(DIO_IO2_LAMP, state);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void setLeds(int8_t red, int8_t green, int8_t blue)
 * \brief	LED1 RVB control
 * \note	Controle the on board RVB LED1
 * \param	[in] red	as bool	- State of LED Lamp
 * \return	void
 */
void myDio::setLeds(bool red, bool green, bool blue)
{
	digitalWrite(DIO_LED_RED,	 red);
	digitalWrite(DIO_LED_BLUE,	 blue);
	digitalWrite(DIO_LED_GREEN,	 green);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void updateStatus(void)
 * \brief	LED1 RVB Status
 * \note	Update the on board RVB LED1 Status
 * \param	void
 * \return	void
 */
void myDio::updateStatus(void)
{
	if(ThmUnit.Status != StatusActif)
	{
		switch(ThmUnit.Status)
		{	//								Red	  Green	Blue
			case STATUS_INIT:		setLeds(LOW,  HIGH, HIGH);	break;	// Yellow
			case STATUS_OK:			setLeds(LOW,  HIGH, LOW);	break;	// Green
			case STATUS_MQTT_OK:	setLeds(HIGH, LOW,  HIGH);	break;	// Purple
			case STATUS_WIFI_OK:	setLeds(LOW,  LOW,  HIGH);	break;	// Blue
			case STATUS_TOUCH_OK:	setLeds(HIGH, HIGH, LOW);	break;	// Brown
			default:				setLeds(HIGH, LOW,  LOW);	break;	// Red
		}
		StatusActif = ThmUnit.Status;
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void loop()
 * \brief	LOOP function
 * \note	Loopback function used for updating the on board RVB LED1
 * \param	
 * \return	void
 */
void myDio::loop(void)
{
	updateStatus();
}
