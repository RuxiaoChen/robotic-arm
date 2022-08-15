/****************************************************************************
	*	@笔者	：	W
	*	@日期	：	2019年12月03日
	*	@所属	：	杭州众灵科技
	*	@论坛	：	www.ZL-robot.com
 ****************************************************************************/

#ifndef __SERVO_H__
#define __SERVO_H__

#include "stm32f10x.h"
#include "z_main.h"

/*******舵机IO口映射表*******/
#define SERVO0_Pin 					GPIO_Pin_3  
#define SERVO0_GPIO_Port 		GPIOB
#define SERVO1_Pin 					GPIO_Pin_8  
#define SERVO1_GPIO_Port 		GPIOB
#define SERVO2_Pin 					GPIO_Pin_9  
#define SERVO2_GPIO_Port 		GPIOB
#define SERVO3_Pin 					GPIO_Pin_6  
#define SERVO3_GPIO_Port 		GPIOB
#define SERVO4_Pin 					GPIO_Pin_7  
#define SERVO4_GPIO_Port 		GPIOB
#define SERVO5_Pin 					GPIO_Pin_4  
#define SERVO5_GPIO_Port 		GPIOB

/*******舵机快捷指令表*******/
#define SERVO0_H() 					GPIO_SetBits(SERVO0_GPIO_Port,SERVO0_Pin) 
#define SERVO0_L()					GPIO_ResetBits(SERVO0_GPIO_Port,SERVO0_Pin)
#define SERVO1_H() 					GPIO_SetBits(SERVO1_GPIO_Port,SERVO1_Pin) 
#define SERVO1_L()					GPIO_ResetBits(SERVO1_GPIO_Port,SERVO1_Pin)
#define SERVO2_H() 					GPIO_SetBits(SERVO2_GPIO_Port,SERVO2_Pin) 
#define SERVO2_L()					GPIO_ResetBits(SERVO2_GPIO_Port,SERVO2_Pin)
#define SERVO3_H() 					GPIO_SetBits(SERVO3_GPIO_Port,SERVO3_Pin) 
#define SERVO3_L()					GPIO_ResetBits(SERVO3_GPIO_Port,SERVO3_Pin)
#define SERVO4_H() 					GPIO_SetBits(SERVO4_GPIO_Port,SERVO4_Pin) 
#define SERVO4_L()					GPIO_ResetBits(SERVO4_GPIO_Port,SERVO4_Pin)
#define SERVO5_H() 					GPIO_SetBits(SERVO5_GPIO_Port,SERVO5_Pin) 
#define SERVO5_L()					GPIO_ResetBits(SERVO5_GPIO_Port,SERVO5_Pin)

/*******舵机相关函数声明*******/
void 	servo_init(void);													//舵机初始化
void 	servo_set(u8 index, u8 level);						//设置舵机引脚输出量
float servo_abs(float value);										//绝对值计算
void 	servo_run(u8 index, int aim, int time);		//舵机控制函数

#endif
