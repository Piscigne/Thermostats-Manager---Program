#ifndef MY_HMI__HPP
#define MY_HMI__HPP

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <TFT_Touch.h>

#include "tools/MyType.h"
#include "tools/myDefine.h"
#include "header/myHeader.hpp"
#include "footer/myFooter.hpp"
#include "select/mySelect.hpp"
#include "thm/myThm.hpp"

#define TOP_HEAD		0
#define TOP_THM			38
#define TOP_THMS		180
#define TOP_FOOT		285

#define SEP_HEADER		30
#define SEP_LINE_X		0
#define SEP_LINE_W		240
#define SEP_LINE_C		0x3186

#define LOCK_KEY_TOP	50
#define LOCK_KEY_BOTTOM	275

#define LOOP_HMI_TOUCH	0
#define LOOP_HMI_HEADER	1
#define LOOP_HMI_THM	2
#define LOOP_HMI_SELECT	3
#define LOOP_HMI_FOOTER	4

class myHmi
{
public:
	myHmi();
	~myHmi() {};
	void loop();
	void init(void);

private:
	void redraw(void);
	void isTouched(void);

protected:
	myHeader* 	pHead;
	myThm* 		pThm;
	mySelect* 	pThms;
	myFooter* 	pFoot;
	int8_t		iLoopHmi = 0;
};

#endif // MY_HMI__HPP
