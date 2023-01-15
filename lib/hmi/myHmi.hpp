/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myHmi.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MY_HMI__HPP
#define MY_HMI__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <TFT_Touch.h>

#include "tools/MyType.hpp"
#include "tools/myDefine.hpp"
#include "header/myHeader.hpp"
#include "footer/myFooter.hpp"
#include "select/mySelect.hpp"
#include "Tools/myMqtt/myMqtt.hpp"
#include "thm/myThm.hpp"

#define TOP_HEAD			0			//!< Top of the HEADER area
#define TOP_THM				38			//!< Top of the THERMOSTAT area
#define TOP_THMS			180			//!< Top of the THM SELECT area
#define TOP_FOOT			285			//!< Top of the FOUTER area

#define LOCK_KEY_TOP		50			//!< Top of KEYPAD
#define LOCK_KEY_BOTTOM		275			//!< BOTTOM of KEYPAD

#define LOOP_HMI_TOUCH		0			//!< LOOP index definition
#define LOOP_HMI_HEADER		1
#define LOOP_HMI_THM		2
#define LOOP_HMI_SELECT		3
#define LOOP_HMI_FOOTER		4
#define LOOP_HMI_PRESENT	5

class myHmi
{
public:
	myHmi();
	~myHmi() {};
	void loop();
	void init(void);

private:
	void redraw(void);
	void Presence(void);
	void isPresent(void);
	void isTouched(void);

protected:
	myHeader* 	pHead;					//!< Pointer to the HEAD class
	myThm* 		pThm;					//!< Pointer to the THERMOSTAT class
	mySelect* 	pThms;					//!< Pointer to the THM SELECT class
	myFooter* 	pFoot;					//!< Pointer to the FOOTER class
	int8_t		iLoopHmi = 0;			//!< Initialize the LOOP index
};

#endif // MY_HMI__HPP
