#include "main.hpp"

static const uint16_t tftWidth  = TFT_WIDTH;
static const uint16_t tftHeight = TFT_HEIGHT;

TFT_eSPI*	pTft		= new TFT_eSPI( tftWidth, tftHeight);
TFT_Touch*	pTouch		= new TFT_Touch(TOUCH_CS, TOUCH_CLK, TOUCH_IN, TOUCH_OUT);
mySDcard*	pSDcard		= new mySDcard();
myWifi*		pWifi		= new myWifi();
myMqtt*		pMqtt		= new myMqtt();
myTime*		MYtime		= new myTime();
myDio*		pDio		= new myDio();
myHmi*	 	pHmi		= new myHmi();
int8_t		iLoopMain	= 0;

THM			ThmUnit;
THM_DATA	ThmData[THERMOSTAT_NBR];

void initCOM()
{
	Serial.begin(115200);
	delay(100);
}

void initTFT()
{
	pTft->begin();
	pTft->setSwapBytes(true);
	pTft->setRotation(TFT_ROTATE);
#ifdef USE_DMA
	pTft->initDMA();
#endif
	pTft->fillScreen(TFT_BLACK);
	pTft->setTextColor(TFT_GREEN, TFT_BLACK);
	pTft->println("SCREEN initialized!");
}

void initTOUCH()
{
	pTouch->setRotation(TFT_ROTATE);
	pTouch->setCal(750, 3377, 526, 3443, 320, 240, 1);
}

void setup()
{
	initCOM();
	ThmUnit.Status = STATUS_INIT;
	pDio->init();
	initTFT();
	initTOUCH();
	pSDcard->init();
	pSDcard->getSettings();
	pWifi->init();
	ThmUnit.Status = STATUS_WIFI_OK;
	MYtime->getNtpTime();
	pMqtt->init();
	delay(1000);
	pTft->fillScreen(TFT_BLACK);
	ThmUnit.Selected = THERMOSTAT1;
	Serial.println("System initializations done!");
	pHmi->init();
	ThmUnit.Status = STATUS_NORMAL;
}

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
