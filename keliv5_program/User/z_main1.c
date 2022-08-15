/****************************************************************************
	*	@笔者	：	W
	*	@日期	：	2019年12月03日
	*	@所属	：	杭州众灵科技
	*	@论坛	：	www.ZL-robot.com
	*	@功能	：	ZL-KPZ控制板（32版）模块例程例程8————PWM舵机控制
	*	@函数列表:
	*	1.	void main(void) -- 主函数
	
	按键1和按键2 控制 0 号舵机 左右转
 ****************************************************************************/

#include "z_main.h"

/*******全局变量定义*******/
u8 i=0;
servo_data_t servo_data[SERVO_NUM];
u8 servo_index;


int delay_s(int s){
for(i=0;i<s;i++)
	{
	delay_ms(1000);
}
}


int duoji0(int a){
	delay_s(1);
	servo_data[0].cur= a;
  servo_run(0,servo_data[0].cur,1000);
	return 0;
}

int duoji1(int a){
	delay_s(1);
	servo_data[1].cur= a;
  servo_run(1,servo_data[1].cur,1000);
	return 0;
}

int duoji2(int a){
	delay_s(1);
	servo_data[2].cur= a;
  servo_run(2,servo_data[2].cur,1000);
	return 0;
}

int duoji3(int a){
	delay_s(1);
	servo_data[3].cur= a;
  servo_run(3,servo_data[3].cur,1000);
	return 0;
}

int duoji4(int a){
	delay_s(1);
	servo_data[4].cur= a;
  servo_run(4,servo_data[4].cur,1000);
	return 0;
}

int duoji5(int a){
	delay_s(1);
	servo_data[5].cur= a;
  servo_run(5,servo_data[5].cur,1000);
	return 0;
}



int main(void) {																																																																																																																															//ZL
	setup_systick();	//初始化滴答时钟，1S增加一次systick_ms的值
	setup_key();		//初始化按键
	setup_servo();		//初始化舵机相关设置

	float t1=90;         //设置角度值
	t1=(t1/270)*2000;    //角度对应的占空比

	duoji3(500+t1);	
	while (1)
		{

	}
}






