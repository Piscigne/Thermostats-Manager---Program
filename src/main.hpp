/***********************************************************************************************************************
 ESP32-WROOM - THERMOSTATS
 FILE           : main.hpp
 REVISION       : 1.0a

 FIRST ISSUE    : January 2023
 CREATED BY		: S.Izoard
***********************************************************************************************************************/
#ifndef MAIN__HPP
#define MAIN__HPP

#include <Arduino.h>
#include <TFT_Touch.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "tools/mySDcard/mySDcard.hpp"
#include "tools/myWifi/myWifi.hpp"
#include "Tools/myMqtt/myMqtt.hpp"
#include "tools/myTime/MyTime.hpp"
#include "tools/myLock/myLock.hpp"
#include "tools/myDio/myDio.hpp"
#include "tools/myDefine.hpp"
#include "tools/myEnum.hpp"
#include "myHmi.hpp"

#define LOOP_MAIN			0			//!< LOOP index definition
#define LOOP_MAIN_HMI		1
#define LOOP_MAIN_WIFI		2
#define LOOP_MAIN_MQTT		3

#endif // MAIN__HPP
