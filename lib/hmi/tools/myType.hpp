/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myType.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_TYPE__H
#define MY_TYPE__H

#include <Arduino.h>
#include "tools/myDefine.hpp"
#include "tools/myEnum.hpp"

/// \brief TYPE definition for storing the THERMOSTAT data and parameters
typedef struct thmData
{
	char				Label[24];						//!< THERMOSTAT label name
	THM_MODES			Mode		= MODE_OFF;			//!< THERMOSTAT mode (OFF, HG, ECO, CONF, CONF+)
	float				Temp		= 88.8;				//!< THERMOSTAT temperature - measured
	float				Target		= 88.8;				//!< THERMOSTAT temperature - target
	bool				State		= ON;				//!< THERMOSTAT heater command (ON, OFF)
	float				Targets[THM_TARGET_NBR]	= { 5.5, 7.5, 19.5, 20.5, 21.5 };
} THM_DATA;

/// \brief TYPE definition for storing the WIFI data and parameters
typedef struct my_Wifi
{
	char				Ssid[16];						//!< WIFI ssid
	char				Pass[24];						//!< WIFI password
	int8_t				Rssi;							//!< WIFI RSSI value
	THM_WIFI			State		= WIFI_STATE_STOP;	//!< WIFI state value (rssi level, off or error)
} MY_WIFI;

/// \brief TYPE definition for storing the NETWORK parameters
typedef struct my_NetWork
{
	bool				Static		= NO;				//!< YES (true) for using a static address
	char				Address[20];					//!< Static IP address
	char				Mask[20];						//!< Static IP mask
	char				Gateway[20];					//!< Static IP gateway
	char				Dns1[20];						//!< Static IP domain name server 1st
	char				Dns2[20];						//!< Static IP domain name server 2nd
} MY_NETWORK;

/// \brief TYPE definition for storing the MQTT parameters
typedef struct my_Mqtt
{
	char				Server[20];						//!< MQTT server IP
	int					Port		= MQTT_PORT;		//!< MQTT server PORT
	char				ID[16];							//!< MQTT server IDENTIFIER
	char				Pass[16];						//!< MQTT server PASSWORD
	char				Path[48];						//!< MQTT main topic path
} My_MQTT;

/// \brief TYPE definition for storing the NTP parameters
typedef struct my_Ntp
{
	char				Server[32];						//!< NTP time server
	char				Zone[48];						//!< NTP time zone server
} MY_NTP;

/// \brief TYPE definition for storing the PROGRAM data and parameters
typedef struct THm
{
	char				LockPass[LOCK_CODE_LEN];		//!< To store the unlock password
	char				RebootAt[REBOOT_TIME_LEN];		//!< To store the unlock password
	THM_STATUS			Status		= STATUS_ERR;		//!< Program status used to light LED1 (rgb)
	bool				LedEscalier	= THM_LAMP_OFF; 	//!< State of LED relais
	bool				Presence	= THM_ABSENCE;		//!< State of Presence
	bool				Locked		= YES;				//!< TRUE if the select mode buttons are locked
	bool				Keyboard	= false;			//!< TRUE if the unlock keyboard is displayed 
	bool				Present		= YES;				//!< Use Presence to manage the TFT backlight
	bool				Redraw		= YES;				//!< TRUE for full display redraw
	THM_INDEX			Selected	= THM_1;			//!< Selected thermostat on top of display
	float				TempExtern	= 88.8;				//!< External temperature - curent
	float				TempExtMax	= 88.8;				//!< External temperature - maximal
	float				TempExtMin	= 88.8;				//!< External temperature - minimal
	MY_WIFI				Wifi;							//!< Data structure for settings the WIFI
	MY_NETWORK			Net;							//!< Data structure for settings the NETWORK
	My_MQTT				Mqtt;							//!< Data structure for settings the MQTT
	MY_NTP				Ntp;							//!< Data structure for settings the NTP
} THM;

/// \brief TYPE definition for storing the BITMAP data and parameters
typedef struct bitMap
{
	const uint16_t*		data;							//!< Pointer to the bitmap array
	uint8_t				width;							//!< Bitmap width
	uint8_t				height;							//!< Bitmap hight
	uint8_t				dataSize;						//!< Pixel size information
} BITMAP;

/// \brief TYPE definition for storing the BOLEAN ICON (like button) bitmap links
typedef struct iconBool
{
	const BITMAP*		IconON;							//!< Pointer to the BITMAP structure for the ON  (true)  state
	const BITMAP*		IconOFF;						//!< Pointer to the BITMAP structure for the OFF (false) state
} ICON_BOOL;

/// \brief TYPE definition for storing the LIST ICON (like wifi info) bitmap links
typedef struct iconList
{
	int8_t				Nbr			= 0;				//!< Number of bitmap into the list
	const BITMAP*		Icons[ICON_LIST_MAX];			//!< Array of pointer to the bitmaps
} ICON_LIST;

#endif // MY_TYPE__H
