/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myWifi.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include "tools/myWifi/myWifi.hpp"

extern myDio* pDio;																	//!< Pointer to the DIO class
extern THM	  ThmUnit;																//!< Pointer to the UNIT data structure

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void init(void)
 * \brief	INIT the WIFI class
 * \note	Initialize the WIFI connection (static or atribued IP)
 * \param	void
 * \return	void
 */
void myWifi::init()
{
	if(ThmUnit.Net.Static)
	{
		IPAddress IP;	IP.fromString(  ThmUnit.Net.Address);
		IPAddress MASK;	MASK.fromString(ThmUnit.Net.Mask);
		IPAddress GATE;	GATE.fromString(ThmUnit.Net.Gateway);
		IPAddress DNS1;	DNS1.fromString(ThmUnit.Net.Dns1);
		IPAddress DNS2;	DNS2.fromString(ThmUnit.Net.Dns2);
		WiFi.config(IP, GATE, MASK, DNS1, DNS2);
	}
	WiFi.begin(ThmUnit.Wifi.Ssid, ThmUnit.Wifi.Pass);
	Serial.printf("\nConnecting to %s (%s)\n", ThmUnit.Wifi.Ssid, ThmUnit.Wifi.Pass);
	while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(100); } Serial.println("");
	Serial.printf("WIFI Connected to %s IP: %s\n", getSsid(), getIp());
	ThmUnit.Status = STATUS_WIFI_OK; pDio->updateStatus();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void getIp(void)
 * \brief	Get IP
 * \note	Get the IP address
 * \param	void
 * \return	const char*
 */
const char* myWifi::getIp(void)
{
	return WiFi.localIP().toString().c_str();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void getSsid(void)
 * \brief	Get SSID
 * \note	Get the SSID
 * \param	void
 * \return	const char*
 */
const char* myWifi::getSsid(void)
{
	return ThmUnit.Wifi.Ssid;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void getRssi(void)
 * \brief	Get RSSI
 * \note	Get the RRSI and define the communication state
 * \param	void
 * \return	int8_t
 */
int8_t myWifi::getRssi(void)
{
	int Rssi = WiFi.RSSI();
	if(		Rssi == WIFI_RSSI_NULL)	ThmUnit.Wifi.State = WIFI_STATE_STOP;
	else if(Rssi <= WIFI_RSSI_NULL)	ThmUnit.Wifi.State = WIFI_RSSI4;
	else if(Rssi <= WIFI_RSSI_4)	ThmUnit.Wifi.State = WIFI_RSSI4;
	else if(Rssi <= WIFI_RSSI_3)	ThmUnit.Wifi.State = WIFI_RSSI3;
	else if(Rssi <= WIFI_RSSI_2)	ThmUnit.Wifi.State = WIFI_RSSI2;
	else if(Rssi <= WIFI_RSSI_1)	ThmUnit.Wifi.State = WIFI_RSSI1;
	else if(Rssi <= WIFI_RSSI_0)	ThmUnit.Wifi.State = WIFI_RSSI0;
	else							ThmUnit.Wifi.State = WIFI_STATE_ERR;
	return ThmUnit.Wifi.Rssi;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void Reconnect(void)
 * \brief	RECONNECT WIFI
 * \note	Check WIFI connection and reconnect they if needed
 * \param	void
 * \return	void
 */
void myWifi::Reconnect(void)
{
	while(WiFi.status() != WL_CONNECTED)
	{
		ThmUnit.Status = STATUS_ERR;
		Serial.print("WIFI connection... ");
		if(WiFi.reconnect())
		{
			Serial.println("connected");
			ThmUnit.Status = STATUS_WIFI_OK;
		}
		else
		{
			Serial.printf("failed, try again in 5 seconds\n");
			delay(5000);
		}
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void loop()
 * \brief	LOOP function
 * \note	Loopback function used for pulling the WIFI connexion state
 * \param	void
 * \return	void
 */
void myWifi::loop(void)
{
	Reconnect();
}
