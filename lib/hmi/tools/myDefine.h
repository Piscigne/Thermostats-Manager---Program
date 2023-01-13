#ifndef MY_DEFINE__H
#define MY_DEFINE__H

#include <Arduino.h>	// TFT_eSPI -> https://projetsdiy.fr/ttgo-t-watch-debuter-librairie-esp32-tft_espi/

#define SD_SETTING_FILE	"/settings.json"
#define LOCK_CODE_PASS	"12345"
#define LOCK_CODE_LEN	10
#define MQTT_PORT		1883

#define ON				true
#define OFF				false

#define YES				true
#define NO				false

#define ICON_LIST_MAX	8

#define TXT_TOP_LEFT	TL_DATUM
#define TXT_TOP_CENTER	TC_DATUM
#define TXT_TOP_RIGHT	TR_DATUM
#define TXT_MID_LEFT	ML_DATUM
#define TXT_MID_CENTER	MC_DATUM
#define TXT_MID_RIGHT	MR_DATUM
#define TXT_BOT_LEFT	BL_DATUM
#define TXT_BOT_CENTER	BC_DATUM
#define TXT_BOT_RIGHT	BR_DATUM

#define THERMOSTAT_NBR	6	// Thermostat index
#define THERMOSTAT1		0
#define THERMOSTAT2		1
#define THERMOSTAT3		2
#define THERMOSTAT4		3
#define THERMOSTAT5		4
#define THERMOSTAT6		5
#define THERMOSTAT_VOID	-1

#define THM_TARGET_NBR	5	// Targets index
#define THM_TARGET_OFF	0
#define THM_TARGET_HG	1
#define THM_TARGET_ECO	2
#define THM_TARGET_ON	3
#define THM_TARGET_CONF	4
#define THM_TARGET_VOID	-1

#define TFT_WIDTH		240
#define TFT_HEIGHT		320
#define TFT_ROTATE		0	// 0 Portrait (0°) - 1 Paysage (90°) - 2 (180°) - 3 (240°)

#define TOUCH_OUT		39  // Data out pin (T_DO) of touch screen
#define TOUCH_IN		32  // Data in pin (T_DIN) of touch screen
#define TOUCH_CS		33  // Chip select pin (T_CS) of touch screen
#define TOUCH_CLK		25  // Clock pin (T_CLK) of touch screen
#define TOUCH_IRQ		36  // Interup (T_IRQ) of touch screen
#define TOUCH_DEBOUNCE	250	// mS

#define THM_MODE_OFF	0	// Thermostat mode values
#define THM_MODE_HG		1
#define THM_MODE_ECO	2
#define THM_MODE_ON		3
#define THM_MODE_CONF	4
#define THM_MODE_VOID	-1

#define THM_STATE_ON	true
#define THM_STATE_OFF	false

#define THM_LOCKED		true
#define THM_UNLOCKED	false

#define THM_PRESENCE	true
#define THM_ABSENCE		false

#define THM_LAMP_ON		true
#define THM_LAMP_OFF	false

#define THM_LED_OFF		0

#define WIFI_0			0	// WIFI status values
#define WIFI_1			1
#define WIFI_2			2
#define WIFI_3			3
#define WIFI_4			4
#define WIFI_ERR		5
#define WIFI_STOP		6
#define WIFI_VOID		-1

#define WIFI_RSSI_NULL	0	// RSSI values used to select the wifi icon
#define WIFI_RSSI_1		-95
#define WIFI_RSSI_2		-70
#define WIFI_RSSI_3		-65
#define WIFI_RSSI_4		-60

#define STATUS_ERROR	0	// Status values to light the LED1
#define STATUS_NORMAL	1
#define STATUS_INIT		2
#define STATUS_WIFI_OK	3
#define STATUS_MQTT_OK	4
#define STATUS_TOUCH_OK	5

#define DIO_LED_RED		4	// LED1, on board RED
#define DIO_LED_BLUE	17	// LED1, on board BLUE
#define DIO_LED_GREEN	16	// LED1, on board GREEN
#define DIO_IO1_TFT		21	// DIO to drive the Backlight
#define DIO_IO2_LAMP	22	// DIO to drive the relais on power board
#define DIO_IO3			35	// DIO free

#endif // MY_DEFINE__H
