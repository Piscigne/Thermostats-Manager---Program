/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : mySelect.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include <select/mySelect.hpp>

extern TFT_eSPI* pTft;																	//!< Pointer to the TFT screen class
extern THM		 ThmUnit;																//!< Pointer to the UNIT data structure
extern THM_DATA	 ThmData[THM_NBR];														//!< THERMOSTATS data array

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		mySelect(int32_t top)
 * \brief	Create the class SELECT
 * \note	Create the SELECT class
 * \param	[in] top	as int32_t	- Top offset of Select area
 * \return	
 */
mySelect::mySelect(int32_t top)
{
	Top = top;
	ThmBtn[THM_1] = new mySelectBtn(SEL_SEP_LEFT,  Top+SEL_SEP_TOP, THM_1);				//!< Create the 1st THM Button
	ThmBtn[THM_2] = new mySelectBtn(SEL_SEP_MID_1, Top+SEL_SEP_TOP, THM_2);				//!< Create the 2nd THM Button
	ThmBtn[THM_3] = new mySelectBtn(SEL_SEP_MID_2, Top+SEL_SEP_TOP, THM_3);				//!< Create the 3rd THM Button
	ThmBtn[THM_4] = new mySelectBtn(SEL_SEP_LEFT,  Top+SEL_SEP_MID, THM_4);				//!< Create the 4th THM Button
	ThmBtn[THM_5] = new mySelectBtn(SEL_SEP_MID_1, Top+SEL_SEP_MID, THM_5);				//!< Create the 5th THM Button
	ThmBtn[THM_6] = new mySelectBtn(SEL_SEP_MID_2, Top+SEL_SEP_MID, THM_6);				//!< Create the 6th THM Button
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void init(void)
 * \brief	INIT the SELECT class
 * \note	Initialize the SELECT class
 * \param	void
 * \return	void
 */
void mySelect::init(void)
{
	for(int i=0; i<THM_NBR; i++) ThmBtn[i]->init();										//!< Initialize all the THM Button
	drawSep();
}

/** ---------------------------------------------------------------------------------------------------------------------
* \fn		void redraw(void)
 * \brief	Redraw the SELECT area
 * \note	Redraw all the SELECT THM Buttons
 * \param	void
 * \return	void
 */
void mySelect::redraw(void)
{
	for(int i=0; i<THM_NBR; i++) ThmBtn[i]->redraw();									//!< Redraw all the THM Button
	drawSep();
}

/** ---------------------------------------------------------------------------------------------------------------------
* \fn		void drawSep(void)
 * \brief	Draw the SEPARATOR
 * \note	Draw all Buttons Separators
 * \param	void
 * \return	void
 */
void mySelect::drawSep(void)
{
	if(ThmUnit.Redraw)
	{
		pTft->drawFastHLine(SEL_SEP_LEFT,  Top+SEL_SEP_TOP, SEL_SEP_WIDTH, TFT_LIGHTGREY);
		pTft->drawFastHLine(SEL_SEP_LEFT,  Top+SEL_SEP_MID, SEL_SEP_WIDTH, TFT_LIGHTGREY);
		pTft->drawFastHLine(SEL_SEP_LEFT,  Top+SEL_SEP_BOT, SEL_SEP_WIDTH, TFT_LIGHTGREY);

		pTft->drawFastVLine(SEL_SEP_LEFT,  Top+SEL_SEP_TOP, SEL_SEP_HEIGH, TFT_LIGHTGREY);
		pTft->drawFastVLine(SEL_SEP_MID_1, Top+SEL_SEP_TOP, SEL_SEP_HEIGH, TFT_LIGHTGREY);
		pTft->drawFastVLine(SEL_SEP_MID_2, Top+SEL_SEP_TOP, SEL_SEP_HEIGH, TFT_LIGHTGREY);
		pTft->drawFastVLine(SEL_SEP_RIGHT, Top+SEL_SEP_TOP, SEL_SEP_HEIGH, TFT_LIGHTGREY);
		ThmUnit.Redraw = false;
	}
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void isTouched(void)
 * \brief	Manage screen touched
 * \note	If screen is touched, analyze the area concerned
 * \param	[in] touchX	as uint16_t	- X coordinate of touched point
 * \param	[in] touchY	as uint16_t	- Y coordinate of touched point
 * \return	bool - TRUE if clicked in the valid area
 */
bool mySelect::isTouched(uint16_t touchX, uint16_t touchY)
{
	if(touchY < SEL_SEP_MID)
	{
		if(		touchX < SEL_SEP_MID_1)	ThmUnit.Selected = THM_1;	//!< If THM 1 touched
		else if(touchX < SEL_SEP_MID_2)	ThmUnit.Selected = THM_2;	//!< If THM 2 touched
		else							ThmUnit.Selected = THM_3;	//!< If THM 3 touched
	}
	else
	{
		if(		touchX < SEL_SEP_MID_1)	ThmUnit.Selected = THM_4;	//!< If THM 4 touched
		else if(touchX < SEL_SEP_MID_2)	ThmUnit.Selected = THM_5;	//!< If THM 5 touched
		else							ThmUnit.Selected = THM_6;	//!< If THM 6 touched
	}
	return true;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void loop()
 * \brief	LOOP function
 * \note	Loopback function used for pulling all the Buttons (by cycle)
 * \param	
 * \return	void
 */
void mySelect::loop()
{
	if(iLoopSelect < THM_NBR) ThmBtn[iLoopSelect++]->loop();
	else					  iLoopSelect = THM_1;
	drawSep();
}
