/****************************************************************************
	*	@笔者	：	W
	*	@日期	：	2019年12月02日
	*	@所属	：	杭州众灵科技
	*	@论坛	：	www.ZL-robot.com
	*	@功能	：	存放按键相关的函数
	*	@函数列表:
	*	1.	void key_init(void) -- 初始化按键
 ****************************************************************************/
 
#include "z_key.h"

/***********************************************
	函数名称：	key_init() 
	功能介绍：	初始化按键
	函数参数：	无
	返回值：		无
 ***********************************************/
void key_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = KEY1_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY1_GPIO_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY2_Pin;
	GPIO_Init(KEY2_GPIO_Port, &GPIO_InitStructure);
}
