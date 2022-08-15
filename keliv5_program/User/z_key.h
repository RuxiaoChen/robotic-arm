/****************************************************************************
	*	@笔者	：	W
	*	@日期	：	2019年12月03日
	*	@所属	：	杭州众灵科技
	*	@论坛	：	www.ZL-robot.com
 ****************************************************************************/

#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"

/*******IO口映射表*******/
#define KEY1_Pin 					GPIO_Pin_8  
#define KEY1_GPIO_Port 		GPIOA
#define KEY2_Pin 					GPIO_Pin_11
#define KEY2_GPIO_Port 		GPIOA

/*******按键快捷指令表*******/
#define KEY1	GPIO_ReadInputDataBit(KEY1_GPIO_Port,KEY1_Pin)	//读取按键KEY1状态
#define KEY2	GPIO_ReadInputDataBit(KEY2_GPIO_Port,KEY2_Pin)	//读取按键KEY2状态

/*******按键相关函数声明*******/
void key_init(void);		//按键初始化

#endif
