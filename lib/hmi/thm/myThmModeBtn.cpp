/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myTHMmodeBtn.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include <thm/myThmModeBtn.hpp>

#include "resources/bitmap/thm/mode/bgnd/bgBtnON.h"
#include "resources/bitmap/thm/mode/bgnd/bgBtnOFF.h"

#include "resources/bitmap/thm/mode/icon/tempCONF.h"
#include "resources/bitmap/thm/mode/icon/tempON.h"
#include "resources/bitmap/thm/mode/icon/tempECO.h"
#include "resources/bitmap/thm/mode/icon/tempHG.h"
#include "resources/bitmap/thm/mode/icon/tempOFFon.h"
#include "resources/bitmap/thm/mode/icon/tempOFFoff.h"

extern TFT_eSPI* pTft;																	//!< Pointer to the TFT screen class
extern THM		 ThmUnit;																//!< Pointer to the UNIT data structure
extern THM_DATA	 ThmData[THM_NBR];														//!< Pointer to the THERMOSTATS data array

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		myTHMmodeBtn(int32_t x, int32_t y, THM_MODES mode)
 * \brief	Create the class MODE BUTTON
 * \note	Create the Thermostat MODE BUTTON class
 * \param	[in] x		as int32_t	 - X offset of Button
 * \param	[in] x		as int32_t	 - Y offset of Button
 * \param	[in] mode	as THM_MODES - Mode assigned of Button
 * \return	
 */
myTHMmodeBtn::myTHMmodeBtn(int32_t x, int32_t y, THM_MODES mode)
{
	X = x;	Y = y; Mode = mode;
	pBmap = new myBitmap();

	int8_t Nbr = 0;

	IconMode.Icons[Nbr++] = &tempOFFoff;
	IconMode.Icons[Nbr++] = &tempHG;
	IconMode.Icons[Nbr++] = &tempECO;
	IconMode.Icons[Nbr++] = &tempON;
	IconMode.Icons[Nbr++] = &tempCONF;
	IconMode.Nbr = Nbr;

	IconOnOff.IconON	  = &tempOFFon;
	IconOnOff.IconOFF	  = &tempOFFoff;

	IconBG.IconON	 	  = &bgBtnON;
	IconBG.IconOFF	 	  = &bgBtnOFF;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void init(void)
 * \brief	INIT the THM class
 * \note	Initialize the THM (Thermostat) class
 * \param	void
 * \return	void
 */
void myTHMmodeBtn::init(void)
{
	redraw();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void setMode(THM_MODES mode)
 * \brief	INIT the THM class
 * \note	Initialize the THM (Thermostat) class
 * \param	[in] mode	as THM_MODES - Mode assigned of Button
 * \return	void
 */
void myTHMmodeBtn::setMode(THM_MODES mode)
{
	Mode = mode;
	dispMode();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void setSelect(bool select)
 * \brief	INIT the THM class
 * \note	Initialize the THM (Thermostat) class
 * \param	[in] select	as bool - Select or unselect the Button
 * \return	void
 */
void myTHMmodeBtn::setSelect(bool select)
{
	Select = select;
	dispSelect();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispSelect(void)
 * \brief	DISPLAY the Button
 * \note	Redraw the Buttons
 * \param	void
 * \return	void
 */
void myTHMmodeBtn::dispSelect(void)
{
	dispBgnd();
	dispTarget();
	dispMode();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispBgnd(void)
 * \brief	DISPLAY the Button Background
 * \note	Redraw the Buttons Background
 * \param	void
 * \return	void
 */
void myTHMmodeBtn::dispBgnd(void)
{
	for(int8_t i = 0; i < BTN_BGND_WIDTH; i += BTN_BGND_STEP)	pBmap->drawARRAYbutton(X+i, Y, &IconBG, Select);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispTarget(void)
 * \brief	DISPLAY the Target
 * \note	Display the target value
 * \param	void
 * \return	void
 */
void myTHMmodeBtn::dispTarget(void)
{
	char TxtBuff[16];
	if(Mode == MODE_OFF | Mode == MODE_VOID) sprintf(TxtBuff, "%s", "Off");
	else				 					 sprintf(TxtBuff, "%3.1f", ThmData[ThmUnit.Selected].Targets[Mode]);
	pTft->setTextDatum(TXT_TOP_RIGHT);
	if(Select)	pTft->setTextColor(myRGB(232, 232, 232), myRGB(148, 148, 148), false);
	else		pTft->setTextColor(myRGB( 64,  64,  64), myRGB(228, 228, 228), false);
	pTft->drawString(TxtBuff, X+BTN_TXT_TARGET_X, Y+BTN_TXT_TARGET_Y, BTN_TXT_TARGET_F);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void dispMode(void)
 * \brief	DISPLAY the Button Icon
 * \note	Redraw the Buttons Icon
 * \param	void
 * \return	void
 */
void myTHMmodeBtn::dispMode(void)
{
	if(Mode == MODE_OFF)	pBmap->drawARRAYbutton(X+BTN_ICO_MODE_X, Y+BTN_ICO_MODE_Y, &IconOnOff, Select ? false : true);
	else					pBmap->drawARRAYlist(  X+BTN_ICO_MODE_X, Y+BTN_ICO_MODE_Y, &IconMode,  (int8_t)Mode);
}

/** ---------------------------------------------------------------------------------------------------------------------
* \fn		void redraw(void)
 * \brief	Redraw the Thermostat Mode
 * \note	Redraw all the Thermostat Mode buttons
 * \param	void
 * \return	void
 */
void myTHMmodeBtn::redraw(void)
{
	dispSelect();
}
