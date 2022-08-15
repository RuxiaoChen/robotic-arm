/****************************************************************************
	*	@笔者	：	W
	*	@日期	：	2019年12月03日
	*	@所属	：	杭州众灵科技
	*	@论坛	：	www.ZL-robot.com
	*	@功能	：	存放初始化相关的函数
	*	@函数列表:
	*	1.	void setup_systick(void) -- 初始化滴答时钟
	*	2.	void setup_key(void) -- 初始化按键
	*	3.	void setup_servo(void) -- 初始化舵机
 ****************************************************************************/
 
#include "z_setup.h"

/***********************************************
	函数名称：	setup_systick() 
	功能介绍：	初始化滴答时钟，1ms增加一次systick_ms的值
	函数参数：	无
	返回值：		无
 ***********************************************/
void setup_systick(void) {
	systick_init();
}

/***********************************************
	函数名称：	setup_key() 
	功能介绍：	初始化按键
	函数参数：	无
	返回值：		无
 ***********************************************/
void setup_key(void) {
	key_init();
}

/***********************************************
	函数名称：	setup_servo() 
	功能介绍：	初始化舵机
	函数参数：	无
	返回值：		无
 ***********************************************/
void setup_servo(void) {
	for(servo_index=0;servo_index<SERVO_NUM;servo_index++){
		servo_data[servo_index].aim=1500;
		servo_data[servo_index].cur=1500;
		servo_data[servo_index].inc=0;
		servo_data[servo_index].time=0;
	}
	servo_init();
	TIM2_init();
}	
