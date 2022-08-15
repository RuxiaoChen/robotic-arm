/****************************************************************************
	*	@笔者	：	W
	*	@日期	：	2019年12月03日
	*	@所属	：	杭州众灵科技
	*	@论坛	：	www.ZL-robot.com
 ****************************************************************************/

#ifndef __MAIN_H__
#define __MAIN_H__

#include "z_setup.h"
#include "z_loop.h"


/*******全局变量宏定义*******/
//#define FOSC  11059200L        	//系统晶振频率
#define SERVO_NUM 8

/*******结构体定义*******/
typedef struct {
	float aim;
	float cur;
	float inc;
	int time;
}servo_data_t;

/*******全局变量外部声明*******/
extern u8 i;
extern servo_data_t servo_data[SERVO_NUM];
extern u8 servo_index;

#endif 
