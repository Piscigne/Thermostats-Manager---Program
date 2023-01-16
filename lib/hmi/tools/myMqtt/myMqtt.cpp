/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myMqtt.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include "Tools/myMqtt/myMqtt.hpp"

extern myMqtt*	pMqtt;																	//!< Pointer to the MQTT class
extern myDio*	pDio;																	//!< Pointer to the DIO class
extern THM		ThmUnit;																//!< Pointer to the UNIT data structure
extern THM_DATA	ThmData[THM_NBR];														//!< Pointer to the THERMOSTATS data array

WiFiClient	 espClient;
PubSubClient mqttClient(espClient);

StaticJsonDocument<512> mqttJson;														//!< Buffer to stre the JSON data

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void callback(char* topic, byte* payload, unsigned int length)
 * \brief	MQTT CALLBACK Message received
 * \note	MQTT Callback function : called when an MQTT message is received
 * \param	[in] topic	 as char*	- MQTT Topic of received message
 * \param	[in] payload as byte*	- MQTT Payload (JSON data) of received message
 * \param	[in] length  as uint	- MQTT Payload length
 * \return	void
 */
void callback(char* topic, byte* payload, unsigned int length)
{
	pMqtt->Callback(topic, payload, length);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void init(void)
 * \brief	INIT the MQTT class
 * \note	Initialize the MQTT class
 * \param	void
 * \return	void
 */
void myMqtt::init()
{
	Serial.printf("MQTT Init: %s:%i\n", ThmUnit.Mqtt.Server, ThmUnit.Mqtt.Port);
	mqttClient.setServer(ThmUnit.Mqtt.Server, ThmUnit.Mqtt.Port);
	mqttClient.setCallback(callback);
	TopicOff = strlen(ThmUnit.Mqtt.Path)-1;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void setThm(char* msg, int thm)
 * \brief	SET the thermostat data
 * \note	SET the thermostat data structure withe the received data
 * \param	[in] msg	 as char* - Received JSON message
 * \param	[in] thm	 as int	  - Index of Thermostat
 * \return	void
 */
void myMqtt::setThm(char* msg, int thm)
{
	int Index = thm-1;
	deserializeJson(mqttJson, msg);

	strlcpy(ThmData[Index].Label, mqttJson[F("Label")], sizeof(ThmData[Index].Label));
	ThmData[Index].Temp	  = float(mqttJson[F("Temp")]);
	ThmData[Index].Target = float(mqttJson[F("Target")]);
	ThmData[Index].State  = bool( mqttJson[F("Actif")]);

	char Mode[8];
	strlcpy(Mode, mqttJson[F("Mode")], sizeof(Mode));
	if(		!strcmp(Mode, "CONF"))	ThmData[Index].Mode = THM_MODES::MODE_CONF;
	else if(!strcmp(Mode, "ON"))	ThmData[Index].Mode = THM_MODES::MODE_ON;
	else if(!strcmp(Mode, "ECO"))	ThmData[Index].Mode = THM_MODES::MODE_ECO;
	else if(!strcmp(Mode, "HG"))	ThmData[Index].Mode = THM_MODES::MODE_HG;
	else							ThmData[Index].Mode = THM_MODES::MODE_HG;

	ThmData[Index].Targets[THM_MODES::MODE_CONF]	= float(mqttJson[F("Targets")][F("CONF")]);
	ThmData[Index].Targets[THM_MODES::MODE_ON]		= float(mqttJson[F("Targets")][F("ON")]);
	ThmData[Index].Targets[THM_MODES::MODE_ECO]		= float(mqttJson[F("Targets")][F("ECO")]);
	ThmData[Index].Targets[THM_MODES::MODE_HG]		= float(mqttJson[F("Targets")][F("HG")]);
	ThmData[Index].Targets[THM_MODES::MODE_OFF]		= float(mqttJson[F("Targets")][F("OFF")]);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void setTempExt(char* msg)
 * \brief	SET External Temperatures
 * \note	SET the External Temperatures (Curent, Mawi and Mini)
 * \param	[in] msg	 as char* - Received JSON message
 * \return	void
 */
void myMqtt::setTempExt(char* msg)
{
	deserializeJson(mqttJson, msg);
	ThmUnit.TempExtern = float(mqttJson[F("ExtTemp")]);
	ThmUnit.TempExtMax = float(mqttJson[F("ExtMax")]);
	ThmUnit.TempExtMin = float(mqttJson[F("ExtMin")]);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void setPresence(char* msg)
 * \brief	SET Presence
 * \note	SET the Presence state
 * \param	[in] msg	 as char* - Received JSON message
 * \return	void
 */
void myMqtt::setPresence(char* msg)
{
	deserializeJson(mqttJson, msg);
	ThmUnit.Presence  = bool(mqttJson[F("Presence")]);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void setLeds(char* msg)
 * \brief	SET Lamp
 * \note	SET the LED Lamp state
 * \param	[in] msg	 as char* - Received JSON message
 * \return	void
 */
void myMqtt::setLeds(char* msg)
{
	ThmUnit.LedEscalier = (msg[0] == '1') ? true : false;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void callback(char* topic, byte* payload, unsigned int length)
 * \brief	CALLBACK Message received
 * \note	Callback function : called when an MQTT message is received
 * \param	[in] topic	 as char*	- MQTT Topic of received message
 * \param	[in] payload as byte*	- MQTT Payload (JSON data) of received message
 * \param	[in] length  as uint	- MQTT Payload length
 * \return	void
 */
void myMqtt::Callback(char* topic, byte* payload, unsigned int length)
{
	int TopicLen = strlen(topic)-TopicOff;
	char Msg[length]; strncpy(Msg,	 (char*)payload, length);	Msg[length]		= '\0';
	char Topic[16];	  strncpy(Topic, topic+TopicOff, TopicLen);	Topic[TopicLen] = '\0';

	if(!strncmp(Topic, "THM",	   3))	setThm(	    Msg, (int)(Topic[3]-48));
	if(!strncmp(Topic, "EXT",	   3))	setTempExt( Msg);
	if(!strncmp(Topic, "PRESENCE", 8))	setPresence(Msg);
	if(!strncmp(Topic, "LEDS",	   4))	setLeds(	Msg);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void sendStr(const char* topic, const char* str)
 * \brief	MQTT Send STRING
 * \note	Callback function : called when an MQTT message is received
 * \param	[in] topic	as char*	- MQTT Topic of message
 * \param	[in] str	as byte*	- MQTT Payload string message
 * \return	void
 */
void myMqtt::sendStr(const char* topic, const char* str)
{
	mqttClient.publish(topic, str);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void sendInt(const char* topic, int value)
 * \brief	MQTT Send INTEGER
 * \note	Callback function : called when an MQTT message is received
 * \param	[in] topic	as char*	- MQTT Topic of message
 * \param	[in] value	as int		- MQTT Payload integer message
 * \return	void
 */
void myMqtt::sendInt(const char* topic, int value)
{
	char Value[8];
	sprintf(Value, "%d", value);
	mqttClient.publish(topic, Value);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void sendBool(const char* topic, bool state)
 * \brief	MQTT Send BOOLEAN
 * \note	Callback function : called when an MQTT message is received
 * \param	[in] topic	as char*	- MQTT Topic of message
 * \param	[in] state	as bool		- MQTT Payload boolean message
 * \return	void
 */
void myMqtt::sendBool(const char* topic, bool state)
{
	mqttClient.publish(topic, state ? "1" : "0");
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void Reconnect(void)
 * \brief	RECONNECT MQTT
 * \note	Check MQTT connection and reconnect they if needed
 * \param	void
 * \return	void
 */
void myMqtt::Reconnect(void)
{
	while(!mqttClient.connected())
	{
		ThmUnit.Status = STATUS_ERR; pDio->updateStatus();
		Serial.print("MQTT connection... ");
		if(mqttClient.connect("ThermostatsClientID"))
		{
			ThmUnit.Status = STATUS_MQTT_OK; pDio->updateStatus();
			Serial.println("connected");
			Serial.printf("MQTT suscribe: %s\n", ThmUnit.Mqtt.Path);
			mqttClient.subscribe(ThmUnit.Mqtt.Path);
			mqttClient.publish("Piscigne/THMS/INFO", "THERMOSTATS connected to MQTT");
			ThmUnit.Status = STATUS_OK; pDio->updateStatus();
		}
		else
		{
			Serial.printf("failed, rc=%i try again in 5 seconds\n", mqttClient.state());
			delay(5000);
		}
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void loop()
 * \brief	LOOP function
 * \note	Loopback function used for pulling the MQTT connexion state, plus refresh the MQTT background function
 * \param	void
 * \return	void
 */
void myMqtt::loop(void)
{
	Reconnect();
	mqttClient.loop();
}
