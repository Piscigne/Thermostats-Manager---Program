#ifndef MY_TYPE__H
#define MY_TYPE__H

#include <Arduino.h>
#include "tools/myDefine.h"

typedef struct tftTouched
{
	bool				Touched		= NO;
	uint16_t			X;
	uint16_t			Y;
} TFT_TOUCHED;

typedef struct thmData
{
	char				Label[24];
	int8_t				Mode		= THM_MODE_OFF;
	float				Temp		= 88.8;
	float				Target		= 88.8;
	bool				State		= ON;
	float				Targets[THM_TARGET_NBR]	= { 5.5, 7.5, 19.5, 20.5, 21.5 };
} THM_DATA;

typedef struct my_Wifi
{
	char				Ssid[16];
	char				Pass[24];
} MY_WIFI;

typedef struct my_NetWork
{
	bool				Static		= false;
	char				Adress[20];
	char				Mask[20];
	char				Gateway[20];
	char				Dns1[20];
	char				Dns2[20];
} MY_NETWORK;

typedef struct my_Mqtt
{
	char				Server[20];
	int					Port		= MQTT_PORT;
	char				ID[16];
	char				Pass[16];
	char				Path[48];
} My_MQTT;

typedef struct my_Ntp
{
	char				Server[32];
	char				Zone[48];
} MY_NTP;

typedef struct THm
{
	bool				Locked		= YES;
	int8_t				Status		= STATUS_ERROR;
	bool				Lampe		= THM_LAMP_OFF;
	bool				Presence	= THM_ABSENCE;
	bool				Redraw		= YES;
	int8_t				WifiRssi	= WIFI_STOP;
	int					Selected	= THERMOSTAT1;
	float				TempExtern	= 88.8;
	float				TempExtMax	= 88.8;
	float				TempExtMin	= 88.8;
	MY_WIFI				Wifi;
	MY_NETWORK			Net;
	My_MQTT				Mqtt;
	MY_NTP				Ntp;
} THM;

typedef struct bitMap
{
	const uint16_t*		data;
	uint8_t				width;
	uint8_t				height;
	uint8_t				dataSize;
} BITMAP;

typedef struct iconBool
{
	const BITMAP*		IconON;
	const BITMAP*		IconOFF;
} ICON_BOOL;

typedef struct iconList
{
	int8_t				Nbr			= 0;
	const BITMAP*		Icons[ICON_LIST_MAX];
} ICON_LIST;

#endif // MY_TYPE__H
