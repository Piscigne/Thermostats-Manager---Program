/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myBitmap.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include "tools/myBitmap/myBitmap.hpp"

extern TFT_eSPI* pTft;																	//!< Pointer to the TFT screen class

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		drawARRAY(int32_t x, int32_t y, const BITMAP* img)
 * \brief	Display BITMAP
 * \note	Display a Bitmap from array
 * \param	[in] x		as int32_t - X offset of Bitmap
 * \param	[in] x		as int32_t - Y offset of Bitmap
 * \param	[in] img	as BITMAP* - pointer to the Bitmap Array
 * \return	
 */
void myBitmap::drawARRAY(int32_t x, int32_t y, const BITMAP* img)
{
	pTft->pushImage(x, y, img->width, img->height, img->data, TFT_BLACK);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		drawARRAYbutton(int32_t x, int32_t y, ICON_BOOL* img, bool state)
 * \brief	Display BITMAP State
 * \note	Display a Bitmap from an array depending the State (ON or OFF)
 * \param	[in] x		as int32_t	  - X offset of Bitmap
 * \param	[in] x		as int32_t	  - Y offset of Bitmap
 * \param	[in] img	as ICON_BOOL* - pointer to the tow Bitmaps Array
 * \param	[in] state	as bool		  - State assigned of Button
 * \return	
 */
void myBitmap::drawARRAYbutton(int32_t x, int32_t y, ICON_BOOL* img, bool state)
{
	if(state)	pTft->pushImage(x, y, img->IconON->width,  img->IconON->height,  img->IconON->data,  TFT_BLACK);
	else		pTft->pushImage(x, y, img->IconOFF->width, img->IconOFF->height, img->IconOFF->data, TFT_BLACK);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		drawARRAYlist(int32_t x, int32_t y, ICON_LIST* img, int8_t index)
 * \brief	Display BITMAP List
 * \note	Display a Bitmap from a List selected by the Index
 * \param	[in] x		as int32_t	  - X offset of Bitmap
 * \param	[in] x		as int32_t	  - Y offset of Bitmap
 * \param	[in] img	as ICON_BOOL* - pointer to the Bitmaps list
 * \param	[in] index	as int8_t	  - index of Bitmap
 * \return	
 */
void myBitmap::drawARRAYlist(int32_t x, int32_t y, ICON_LIST* img, int8_t index)
{
	if(index < img->Nbr)
	{
		pTft->pushImage(x, y, img->Icons[index]->width, img->Icons[index]->height, img->Icons[index]->data, TFT_BLACK);
	}
}

unsigned short int myRGB(uint8_t r, uint8_t g, uint8_t b)
{
    unsigned short  B =  (b >> 3)        & 0x001F;
    unsigned short  G = ((g >> 2) <<  5) & 0x07E0;
    unsigned short  R = ((r >> 3) << 11) & 0xF800;
    return (unsigned short int) (R | G | B);
}
