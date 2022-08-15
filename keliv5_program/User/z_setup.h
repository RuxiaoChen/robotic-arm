/****************************************************************************
	*	@笔者	：	W
	*	@日期	：	2019年12月03日
	*	@所属	：	杭州众灵科技
	*	@论坛	：	www.ZL-robot.com
 ****************************************************************************/

#ifndef __SETUP_H__
#define __SETUP_H__

#include "z_main.h"
#include "z_key.h"
#include "z_timer.h"
#include "z_servo.h"

/*******初始化函数声明*******/
void setup_systick(void);	//初始化滴答时钟，1S增加一次systick_ms的值
void setup_key(void);			//初始化按键
void setup_servo(void);		//初始化舵机相关设置

#endif
