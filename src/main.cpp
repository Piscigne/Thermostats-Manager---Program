/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : main.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include "main.hpp"

TFT_eSPI*	pTft		= new TFT_eSPI( TFT_WIDTH, TFT_HEIGHT);						//!< Create the TFT screen class
TFT_Touch*	pTouch		= new TFT_Touch(TOUCH_CS, TOUCH_CLK, TOUCH_IN, TOUCH_OUT);	//!< Create the TOUCH screen class
mySDcard*	pSDcard		= new mySDcard();											//!< Create the SD Card class
myWifi*		pWifi		= new myWifi();												//!< Create the WIFI class
myMqtt*		pMqtt		= new myMqtt();												//!< Create the MQTT class
myLock*		pLock		= new myLock();												//!< Create the LOCK class
myTime*		pTime		= new myTime();												//!< Create the TIME class
myDio*		pDio		= new myDio();												//!< Create the DIO class
myHmi*	 	pHmi		= new myHmi();												//!< Create the HMI class
int8_t		iLoopMain	= 0;														//!< Initialize the LOOP index

THM			ThmUnit;																//!< Create the UNIT data structure
THM_DATA	ThmData[THM_NBR];														//!< Create the THERMOSTATS data array

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void initCOM(void)
 * \brief	COM initialization
 * \note	Initialize the communication port
 * \param	void
 * \return	void
 */
void initCOM(void)
{
	Serial.begin(115200);
	delay(100);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void initTFT(void)
 * \brief	TFT initialization
 * \note	Initialize the TFT screen
 * \param	void
 * \return	void
 */
void initTFT(void)
{
	pTft->begin();
	pTft->setSwapBytes(true);
	pTft->setRotation(TFT_ROTATE);
	pTft->fillScreen(TFT_BLACK);
	pTft->setTextColor(TFT_GREEN, TFT_BLACK);
	pTft->println("SCREEN initialized!");
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void initTOUCH(void)
 * \brief	TOUCH initialization
 * \note	Initialize the touch screen
 * \param	void
 * \return	void
 */
void initTOUCH(void)
{
	pTouch->setRotation(TFT_ROTATE);
	pTouch->setCal(750, 3377, 526, 3443, 320, 240, 1);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void setup()
 * \brief	Main program entry
 * \note	Main function called at boot
 * \param	
 * \return	void
 */
void setup()
{
	initCOM();
	ThmUnit.Status = STATUS_INIT;
	strcpy(ThmUnit.LockPass, LOCK_CODE_PASS);
	pDio->init();
	initTFT();
	initTOUCH();
	pSDcard->init();
	pSDcard->getSettings();
	pWifi->init();
	ThmUnit.Status = STATUS_WIFI_OK;
	pTime->getNtpTime();
	pMqtt->init();
	delay(1000);
	pTft->fillScreen(TFT_BLACK);
	ThmUnit.Selected = THM_1;
	Serial.println("System initializations done!");
	pHmi->init();
	ThmUnit.Status = STATUS_OK;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void loop()
 * \brief	LOOP function
 * \note	Loopback function used for pulling HMI, WIFI and MQTT
 * \param	
 * \return	void
 */
void loop()
{
	switch(iLoopMain++)
	{
		case LOOP_MAIN:							break;
		case LOOP_MAIN_HMI:		pHmi->loop();	break;
		case LOOP_MAIN_WIFI:	pWifi->loop();	break;
		case LOOP_MAIN_MQTT:	pMqtt->loop();	break;
		default:				iLoopMain = 0;
	}
	pDio->loop();
}
