/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myDefine.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_DEFINE__H
#define MY_DEFINE__H

#include <Arduino.h>

#define SD_SETTING_FILE	"/settings.json"	//!< Setting json file phat on SD Card
#define LOCK_CODE_PASS	"12345"				//!< By default unlock code
#define LOCK_CODE_LEN	10					//!< Zize of char buffer to store the unloc code
#define REBOOT_TIME_LEN	10					//!< Zize of char buffer to store the HH:MM:SS of dayly reboot time
#define MQTT_PORT		1883				//!< By default MQTT port

#define ON				true
#define OFF				false

#define YES				true
#define NO				false

#define ICON_LIST_MAX	8					//!< Bitmap array list size

#define TXT_TOP_LEFT	TL_DATUM			//!< Definition of Draw Text positions
#define TXT_TOP_CENTER	TC_DATUM
#define TXT_TOP_RIGHT	TR_DATUM
#define TXT_MID_LEFT	ML_DATUM
#define TXT_MID_CENTER	MC_DATUM
#define TXT_MID_RIGHT	MR_DATUM
#define TXT_BOT_LEFT	BL_DATUM
#define TXT_BOT_CENTER	BC_DATUM
#define TXT_BOT_RIGHT	BR_DATUM

#define THM_TARGET_NBR	5					//!< Targets index

#define TFT_WIDTH		240
#define TFT_HEIGHT		320
#define TFT_ROTATE		0					//!< 0 Portrait (0°) - 1 Paysage (90°) - 2 (180°) - 3 (240°)

#define TOUCH_OUT		39  				//!< Data out pin (T_DO) of touch screen
#define TOUCH_IN		32  				//!< Data in pin (T_DIN) of touch screen
#define TOUCH_CS		33  				//!< Chip select pin (T_CS) of touch screen
#define TOUCH_CLK		25  				//!< Clock pin (T_CLK) of touch screen
#define TOUCH_IRQ		36  				//!< Interup (T_IRQ) of touch screen
#define TOUCH_DEBOUNCE	250					//!< mS

#define THM_STATE_ON	true
#define THM_STATE_OFF	false

#define THM_LOCKED		true
#define THM_UNLOCKED	false

#define THM_PRESENCE	true
#define THM_ABSENCE		false

#define THM_LAMP_ON		true
#define THM_LAMP_OFF	false

#define THM_LED_OFF		0

#define WIFI_RSSI_NULL	0					//!< RSSI values used to select the wifi icon
#define WIFI_RSSI_0		-95
#define WIFI_RSSI_1		-85
#define WIFI_RSSI_2		-70
#define WIFI_RSSI_3		-65
#define WIFI_RSSI_4		-60

#define DIO_LED_RED		4					//!< LED1, on board RED
#define DIO_LED_BLUE	17					//!< LED1, on board BLUE
#define DIO_LED_GREEN	16					//!< LED1, on board GREEN
#define DIO_IO1_TFT		21					//!< DIO to drive the Backlight
#define DIO_IO2_LAMP	22					//!< DIO to drive the relais on power board
#define DIO_IO3			35					//!< DIO free

#endif // MY_DEFINE__H
