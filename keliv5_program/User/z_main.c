#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Serial.h"
#include "z_main.h"
#include "z_timer.h"	//存放定时器功能文件
#include "z_setup.h"
#include "z_delay.h"


/*******全局变量定义*******/
u8 i=0;
servo_data_t servo_data[SERVO_NUM];
u8 servo_index;
//kinematics_t kinematics;
int flag=0;
float j1=90;         //设置角度值
uint8_t RxFlag;
uint8_t RxData;

int delay_s(int s){
for(i=0;i<s;i++)
	{
	delay_ms(1000);
}
}

int duoji0(int a){
	servo_data[0].cur= a;
  servo_run(0,servo_data[0].cur,1000);
	return 0;
}

int duoji1(int a){
	servo_data[1].cur= a;

	return 0;
}

int duoji2(int a){
	servo_data[2].cur= a;

	return 0;
}

int duoji3(int a){
	servo_data[3].cur= a;

	return 0;
}

int duoji4(int a){
	servo_data[4].cur= a;

	return 0;
}

int duoji5(int a){
	servo_data[5].cur= a;

	return 0;
}

//void set_servo(int index, int pwm, int time) {
//	duoji_doing[index].aim = pwm;
//	duoji_doing[index].time = time;
//	duoji_doing[index].inc = (duoji_doing[index].aim -  duoji_doing[index].cur) / (duoji_doing[index].time/20.000);
//	sprintf((char *)cmd_return, "#%03dP%04dT%04d!(%.1f)\r\n", index, pwm, time, kinematics.servo_angle[index]);
//	uart1_send_str(cmd_return);	
//}


//int kinematics_move(float x, float y, float z, int time) {
//	int i,j, min = 0, flag = 0;
//	
//	if(y < 0)return 0;
//	
//	//寻找最佳角度
//	flag = 0;
//	for(i=0;i>=-135;i--) {
//		if(0 == kinematics_analysis(x,y,z,i,&kinematics)){
//			if(i<min)min = i;
//			flag = 1;
//		}
//	}
//	
//	//用3号舵机与水平最大的夹角作为最佳值
//	if(flag) {
//		kinematics_analysis(x,y,z,min,&kinematics);
//		for(j=0;j<4;j++) {
//			set_servo(j, kinematics.servo_pwm[j], time);
//		}
//		return 1;
//	}
//	
//	return 0;
//}


int main(void)	
{	
	setup_systick();	//初始化滴答时钟，1S增加一次systick_ms的值
	setup_key();		//初始化按键
	setup_servo();		//初始化舵机相关设置
	Serial_Init();
	
	while (1)
	{
		RxFlag = Serial_GetRxFlag();
		if (RxFlag == 1)
		{
			RxData = Serial_GetRxData();
			printf("angle you sent is %d\n",RxData);
			j1=(float)(RxData);
			j1=(j1/270)*2000;
			printf("the PWM is %f",j1);

			if(flag==0)
				{
				duoji1(500+j1);
				printf("the flag is %d",flag);
			  flag=1;
				continue;
				}
			if(flag==1)
			{
				 duoji2(500+j1);	
				printf("the flag is %d",flag);
			   flag=2;
				 continue;
			}
			if(flag==2)
			{duoji3(500+j1);
			printf("the flag is %d",flag);
		  	flag=3;
				continue;
			}
			if(flag==3){
			  duoji0(500+j1);
				printf("the flag is %d",flag);
			  flag=0;
			  continue;}
		}

	}
}

