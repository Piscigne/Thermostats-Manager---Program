#include "tools/myTime/MyTime.hpp"

extern THM	  ThmUnit;

const char* myDay[]	  = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
const char* myMonth[] = {"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};

char TimeBuff[TXT_TIME_BUFFER];
char DateBuff[TXT_DATE_BUFFER];

void myTime::getNtpTime(void)
{
	configTime(3600, 3600, ThmUnit.Ntp.Server);
}

void myTime::setDateTime(void)
{
	struct tm tm;
	tm.tm_year	= 2023-1900;
	tm.tm_mon	= 0;
	tm.tm_mday	= 7;
	tm.tm_hour	= 14;
	tm.tm_min	= 8;
	tm.tm_sec	= 30;
	time_t t	= mktime(&tm);
	struct timeval now = { .tv_sec = t };
	settimeofday(&now, NULL);
}

const char* myTime::getTime(void)
{
	struct tm tmTime;
	if(!getLocalTime(&tmTime)) Serial.println("Could not obtain time info");
	strftime(TimeBuff, TXT_TIME_BUFFER, TimeTxt, &tmTime);
	return TimeBuff;
}

const char* myTime::getDate(void)
{
	struct tm tmDate;
	if(!getLocalTime(&tmDate)) Serial.println("Could not obtain date info");
	sprintf(DateBuff, DateTxt, myDay[tmDate.tm_wday], tmDate.tm_mday, myMonth[tmDate.tm_mon], tmDate.tm_year+1900);
	return DateBuff;
}
