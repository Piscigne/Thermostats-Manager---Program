/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : mySDcard.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include "tools/mySDcard/mySDcard.hpp"

extern THM ThmUnit;																//!< Pointer to the UNIT data structure

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void init(void)
 * \brief	INIT the SD CARD class
 * \note	Initialize the SD CARD class and mount file system
 * \param	void
 * \return	void
 */
void mySDcard::init(void)
{
	if(!SD.begin(SD_CS))	  { Serial.println(F("SD CARD failed!")); while (1) delay(0);			}
	else					  { Serial.println(F("SD CARD OK.")); 									}
	uint8_t cardType = SD.cardType();
	if(cardType == CARD_NONE) { Serial.println(F("SD CARD not attached!")); while (1) delay(0);		}
	else				 	  { Serial.println(F("SD CARD attached.")); 							}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void getSettings(void)
 * \brief	GET SETTINGS
 * \note	Gest the unit and thermostat settings from the SD Card
 * \param	void
 * \return	void
 */
void mySDcard::getSettings(void)
{
	File File = SD.open(SD_SETTING_FILE, FILE_READ);
    if(!File)				  { Serial.printf("Failed to open file %s\n", SD_SETTING_FILE); return; }

	StaticJsonDocument<1024> Doc;
	DeserializationError Err = deserializeJson(Doc, File);	if(Err) Serial.println(F("Failed to read file, using default configuration"));

	ThmUnit.Present = bool(Doc[F("presence")]);												Serial.printf("PRES: %s\n", ThmUnit.Present ? "true" : "false");
	strlcpy(ThmUnit.LockPass,	 Doc[F("lock")],			  sizeof(ThmUnit.LockPass));	Serial.printf("LOCK: %s\n", ThmUnit.LockPass);
	strlcpy(ThmUnit.RebootAt,	 Doc[F("rebootAt")],		  sizeof(ThmUnit.RebootAt));	Serial.printf("BOOT: %s\n", ThmUnit.RebootAt);

	strlcpy(ThmUnit.Wifi.Ssid,	 Doc[F("wifi")][F("ssid")],	  sizeof(ThmUnit.Wifi.Ssid));	Serial.printf("SSID: %s\n", ThmUnit.Wifi.Ssid);
	strlcpy(ThmUnit.Wifi.Pass,	 Doc[F("wifi")][F("pass")],	  sizeof(ThmUnit.Wifi.Pass));	Serial.printf("PASS: %s\n", ThmUnit.Wifi.Pass);
	
	ThmUnit.Net.Static = bool(Doc[F("net")][F("static")]);									Serial.printf("STAT: %s\n", ThmUnit.Net.Static ? "true" : "false");
	strlcpy(ThmUnit.Net.Address, Doc[F("net")][F("ip")],	  sizeof(ThmUnit.Net.Address));	Serial.printf("IP  : %s\n", ThmUnit.Net.Address);
	strlcpy(ThmUnit.Net.Mask,	 Doc[F("net")][F("mask")],	  sizeof(ThmUnit.Net.Mask));	Serial.printf("MASK: %s\n", ThmUnit.Net.Mask);
	strlcpy(ThmUnit.Net.Gateway, Doc[F("net")][F("gate")],	  sizeof(ThmUnit.Net.Gateway));	Serial.printf("GATE: %s\n", ThmUnit.Net.Gateway);
	strlcpy(ThmUnit.Net.Dns1,	 Doc[F("net")][F("dns1")],	  sizeof(ThmUnit.Net.Dns1));	Serial.printf("DNS1: %s\n", ThmUnit.Net.Dns1);
	strlcpy(ThmUnit.Net.Dns2,	 Doc[F("net")][F("dns2")],	  sizeof(ThmUnit.Net.Dns2));	Serial.printf("DNS2: %s\n", ThmUnit.Net.Dns2);

	strlcpy(ThmUnit.Mqtt.Server, Doc[F("mqtt")][F("server")], sizeof(ThmUnit.Mqtt.Server));	Serial.printf("MQTT: %s\n", ThmUnit.Mqtt.Server);
	strlcpy(ThmUnit.Mqtt.ID,	 Doc[F("mqtt")][F("id")],	  sizeof(ThmUnit.Mqtt.ID));		Serial.printf("ID  : %s\n", ThmUnit.Mqtt.ID);
	strlcpy(ThmUnit.Mqtt.Pass,	 Doc[F("mqtt")][F("pass")],	  sizeof(ThmUnit.Mqtt.Pass));	Serial.printf("PASS: %s\n", ThmUnit.Mqtt.Pass);
	strlcpy(ThmUnit.Mqtt.Path,	 Doc[F("mqtt")][F("path")],	  sizeof(ThmUnit.Mqtt.Path));	Serial.printf("PATH: %s\n", ThmUnit.Mqtt.Path);

	strlcpy(ThmUnit.Ntp.Server,	 Doc[F("ntp")][F("server")],  sizeof(ThmUnit.Ntp.Server));	Serial.printf("NTP : %s\n", ThmUnit.Ntp.Server);
	strlcpy(ThmUnit.Ntp.Zone,	 Doc[F("ntp")][F("zone")],	  sizeof(ThmUnit.Ntp.Zone));	Serial.printf("ZONE: %s\n", ThmUnit.Ntp.Zone);

	File.close();
}
