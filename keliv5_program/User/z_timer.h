/****************************************************************************
	*	@笔者	：	W
	*	@日期	：	2019年12月03日
	*	@所属	：	杭州众灵科技
	*	@论坛	：	www.ZL-robot.com
 ****************************************************************************/

#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f10x.h"
#include "z_main.h"

/*******定时器相关函数声明*******/
void systick_init(void);		//systick初始化 1毫秒@72MHz
u32 millis(void);						//滴答时钟查询
void TIM2_init(void);

#endif
