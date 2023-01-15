/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myEnum.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_ENUM__H
#define MY_ENUM__H

#include <Arduino.h>
#include "tools/myDefine.hpp"

/// \brief Enum the MODE possibility
enum THM_INDEX
{
	THM_1			= 0,			//!< THERMOSTAT number 1
	THM_2,							//!< THERMOSTAT number 2
	THM_3,							//!< THERMOSTAT number 3
	THM_4,							//!< THERMOSTAT number 4
	THM_5,							//!< THERMOSTAT number 5
	THM_6,							//!< THERMOSTAT number 6
	THM_NBR,						//!< THERMOSTAT number
	THM_VOID		= -1,			//!< THERMOSTAT not selected
};

/// \brief Enum the MODE possibility
enum THM_MODES
{
	MODE_OFF		= 0,			//!< MODE = OFF
	MODE_HG,						//!< MODE = Frost protection
	MODE_ECO,						//!< MODE = Economic
	MODE_ON,						//!< MODE = Comfort
	MODE_CONF,						//!< MODE = Comfort plus
	MODE_NBR,						//!< MODE number
	MODE_VOID		= -1			//!< MODE = Not initialized
};

/// \brief Enum the STATUS possibility
enum THM_STATUS
{
	STATUS_ERR		= 0,			//!< STATUS of execution = OFF
	STATUS_OK,						//!< STATUS of execution = is NORMAL
	STATUS_INIT,					//!< STATUS of execution = on INITIALIZATION
	STATUS_WIFI_OK,					//!< STATUS of execution = WIFI is initialized
	STATUS_MQTT_OK,					//!< STATUS of execution = MQTT is initialized
	STATUS_TOUCH_OK,				//!< STATUS of execution = Screen touched on autorized area
	STATUS_NBR						//!< STATUS number
};

/// \brief Enum the WIFI possibility
enum THM_WIFI
{
	WIFI_RSSI0		= 0,			//!< WIFI = RSSI level 0
	WIFI_RSSI1,						//!< WIFI = RSSI level 1
	WIFI_RSSI2,						//!< WIFI = RSSI level 2
	WIFI_RSSI3,						//!< WIFI = RSSI level 3
	WIFI_RSSI4,						//!< WIFI = RSSI level 4
	WIFI_STATE_OFF,					//!< WIFI = Is OFF
	WIFI_STATE_ERR,					//!< WIFI = Is on ERROR
	WIFI_STATE_STOP,				//!< WIFI = Is OFF
	WIFI_NBR,						//!< WIFI number
	WIFI_VOID		= -1			//!< WIFI = Not initialized
};

#endif // MY_TYPE__H
