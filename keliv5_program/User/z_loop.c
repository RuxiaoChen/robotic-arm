/****************************************************************************
	*	@笔者	：	W
	*	@日期	：	2019年12月03日
	*	@所属	：	杭州众灵科技
	*	@论坛	：	www.ZL-robot.com
	*	@功能	：	存放永久循环执行的函数
	*	@函数列表:
	*	1.	void loop_key(void) -- 循环检测按键状态
	*	2.	void loop_servo(void) -- 循环处理舵机的指令
 ****************************************************************************/
 
#include "z_loop.h"

/***********************************************
	函数名称：	loop_key() 
	功能介绍：	循环检测按键状态
	函数参数：	无
	返回值：		无
 ***********************************************/
void loop_key(void) {
	static u32 systick_ms_bak = 0;

/*****************按键1按下检测*****************/
	if(KEY1==0){
		delay_ms(50);
		if(KEY1==0){
/*****************按键1长按检测*****************/
			systick_ms_bak = millis();
			while(KEY1==0){
				if(millis() - systick_ms_bak >= 500) {
/*****************按键1长按执行*****************/
					if((millis() - systick_ms_bak) % 500 == 0)
						servo_run(0,servo_data[0].aim+=10,500);
/***********************************************/
				}
			}
/*****************按键1松开执行*****************/
			servo_run(0,servo_data[0].cur,500);
/***********************************************/
/*****************按键1单次检测*****************/
			if(millis() - systick_ms_bak < 500) {
/*****************按键1单次执行*****************/
				servo_run(0,servo_data[0].aim+100,500);
/***********************************************/
			}
			
		}
	}

/*****************按键2按下检测*****************/
	if(KEY2==0){
		delay_ms(50);
		if(KEY2==0){
/*****************按键2长按检测*****************/
			systick_ms_bak = millis();
			while(KEY2==0){
				if(millis() - systick_ms_bak >= 500) {
/*****************按键2长按执行*****************/
					if((millis() - systick_ms_bak) % 500 == 0)
						servo_run(0,servo_data[0].aim-=10,500);
/***********************************************/
				}
			}
/*****************按键2松开执行*****************/
			servo_run(0,servo_data[0].cur,500);
/***********************************************/
/*****************按键2单次检测*****************/
			if(millis() - systick_ms_bak < 500) {
/*****************按键2单次执行*****************/
				servo_run(0,servo_data[0].aim-100,500);
/***********************************************/
			}
		}
	}
}

/***********************************************
	函数名称：	loop_servo() 
	功能介绍：	循环处理舵机的指令
	函数参数：	无
	返回值：		无
 ***********************************************/
void loop_servo(void) {
	if(servo_data[servo_index].inc != 0) {
		if(servo_data[servo_index].aim>2495)	servo_data[servo_index].aim=2495;
		if(servo_data[servo_index].aim<500)		servo_data[servo_index].aim=500;
		if(servo_abs(servo_data[servo_index].aim - servo_data[servo_index].cur) <= servo_abs(servo_data[servo_index].inc + servo_data[servo_index].inc)) {
			servo_data[servo_index].cur = servo_data[servo_index].aim;
			servo_data[servo_index].inc = 0;
		} else {
			servo_data[servo_index].cur += servo_data[servo_index].inc;
		}
	}
}
