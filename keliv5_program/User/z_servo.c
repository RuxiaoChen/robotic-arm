/****************************************************************************
	*	@笔者	：	W
	*	@日期	：	2019年12月02日
	*	@所属	：	杭州众灵科技
	*	@论坛	：	www.ZL-robot.com
	*	@功能	：	存放舵机相关的函数
	*	@函数列表:
	*	1.	void servo_init(void) -- 初始化舵机
	*	2.	void servo_set(u8 index, u8 level) -- 设置舵机引脚输出量
	*	3.	float servo_abs(float value) -- 绝对值计算
	*	4.	void servo_run(u8 index, int aim, int time) -- 舵机控制函数
 ****************************************************************************/
 
#include "z_servo.h"

/***********************************************
	函数名称：	servo_init() 
	功能介绍：	初始化舵机
	函数参数：	无
	返回值：		无
 ***********************************************/
void servo_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  SERVO0_Pin|SERVO1_Pin|SERVO2_Pin|SERVO3_Pin|SERVO4_Pin|SERVO5_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SERVO0_GPIO_Port, &GPIO_InitStructure);	
	servo_set(0,0);
	servo_set(1,0);
	servo_set(2,0);
	servo_set(3,0);
	servo_set(4,0);
	servo_set(5,0);
}

/***********************************************
	函数名称：	servo_set(index,level) 
	功能介绍：	设置舵机引脚输出量
	函数参数：	index 舵机编号 level 输出量
	返回值：		无
 ***********************************************/
void servo_set(u8 index, u8 level) {
	if(level) {
		switch(index) {
			case 0:	SERVO0_H();	break;
			case 1:	SERVO1_H();	break;
			case 2:	SERVO2_H();	break;
			case 3:	SERVO3_H();	break;
			case 4:	SERVO4_H();	break;
			case 5:	SERVO5_H();	break;
			default:	break;
		}
	}
	else {
		switch(index) {
			case 0:	SERVO0_L();	break;
			case 1:	SERVO1_L();	break;
			case 2:	SERVO2_L();	break;
			case 3:	SERVO3_L();	break;
			case 4:	SERVO4_L();	break;
			case 5:	SERVO5_L();	break;
			default:	break;
		}	
	}
}

/***********************************************
	函数名称：	servo_abs(value) 
	功能介绍：	绝对值计算
	函数参数：	value 转换量
	返回值：		转换量的绝对值
 ***********************************************/
float servo_abs(float value) {
	if(value>0) {
		return value;
	}
	return (-1*value);
}

/***********************************************
	函数名称：	servo_run(index,aim,time) 
	功能介绍：	舵机控制函数
	函数参数：	index 舵机编号 aim 目标值 time 时间量
	返回值：		无
 ***********************************************/
void servo_run(u8 index, int aim, int time) {
	if(index < SERVO_NUM && (aim<=2500)&& (aim>=500) && (time<10000)) {
		if(servo_data[index].cur == aim){
			aim = aim+0.0077;
		} 
		
		if(aim>2497)	aim=2497;
		if(aim<500)		aim=500;
		
		if(time < 20) {
			servo_data[index].aim = aim;
			servo_data[index].cur = aim;
			servo_data[index].inc = 0;
		} else {
			servo_data[index].aim = aim;
			servo_data[index].time = time;
			servo_data[index].inc = (servo_data[index].aim-servo_data[index].cur)/(servo_data[index].time/20.000);
		}
	}
}
