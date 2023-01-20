/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : myTime.cpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#include "tools/myTime/MyTime.hpp"

extern THM	  ThmUnit;																//!< Pointer to the UNIT data structure

const char* myDay[]	  = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
const char* myMonth[] = {"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};

char TimeBuff[TXT_TIME_BUFFER];														//!< Buffer to store the formated string TIME
char DateBuff[TXT_DATE_BUFFER];														//!< Buffer to store the formated string TIME

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void getNtpTime(void)
 * \brief	Time from NTP
 * \note	Set the TIME from an NTP server
 * \param	void
 * \return	void
 */
void myTime::getNtpTime(void)
{
	configTime(3600, 3600, ThmUnit.Ntp.Server);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void getTime(void)
 * \brief	Get TIME
 * \note	Get the TIME in formated string
 * \param	void
 * \return	void
 */
const char* myTime::getTime(void)
{
	struct tm tmTime;
	if(!getLocalTime(&tmTime)) Serial.println("Could not obtain time info");
	strftime(TimeBuff, TXT_TIME_BUFFER, BootTxt, &tmTime);
	rebootAt(TimeBuff);
	strftime(TimeBuff, TXT_TIME_BUFFER, TimeTxt, &tmTime);

	ThmUnit.IsMorning = (tmTime.tm_hour <= 11 & tmTime.tm_min <= 59 & tmTime.tm_sec <= 59);

	return TimeBuff;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void getDate(void)
 * \brief	Get DATE
 * \note	Get the DATE in formated string
 * \param	void
 * \return	void
 */
const char* myTime::getDate(void)
{
	struct tm tmDate;
	if(!getLocalTime(&tmDate)) Serial.println("Could not obtain date info");
	sprintf(DateBuff, DateTxt, myDay[tmDate.tm_wday], tmDate.tm_mday, myMonth[tmDate.tm_mon], tmDate.tm_year+1900);
	return DateBuff;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * \fn		void rebootAt(void)
 * \brief	REBOOT dayly
 * \note	reboot the unit at specified time
 * \param	void
 * \return	void
 */
void myTime::rebootAt(const char* hhmmss)
{
	if(!strcmp(hhmmss, ThmUnit.RebootAt))													//!< Reboot dayly at the specified time
	{
		Serial.printf("It's %s, time to REBOOT...\n", hhmmss);
		ESP.restart();
	}
}
