/****************************************************************************
	*	@笔者	：	W
	*	@日期	：	2019年12月03日
	*	@所属	：	杭州众灵科技
	*	@论坛	：	www.ZL-robot.com
	*	@功能	：	存放定时器相关的函数
	*	@函数列表:
	*	1.	void systick_init(void) -- 初始化systick
	*	2.	void SysTick_Handler(void) interrupt 19 -- systick中断函数
	*	3.	u32 millis(void) -- 滴答时钟查询
	*	4.	void TIM2_init(void) -- 初始化TIM2
	*	5.	void TIM2_IRQHandler(void) -- 输出舵机控制波形
 ****************************************************************************/
 
#include "z_timer.h" 

static u32 systick_ms = 0;

/***********************************************
	函数名称：	systick_init() 
	功能介绍：	初始化systick
	函数参数：	无
	返回值：		无
 ***********************************************/
void systick_init(void)	{	//1毫秒@72MHz
	SysTick_Config(72000);
}

/***********************************************
	函数名称：	SysTick_Handler() 
	功能介绍：	SysTick中断
	函数参数：	无
	返回值：		无
 ***********************************************/
void SysTick_Handler(void) {
	systick_ms++;
}

/***********************************************
	函数名称：	millis() 
	功能介绍：	滴答时钟查询
	函数参数：	无
	返回值：		systick_ms 系统时间
 ***********************************************/
u32 millis(void) {
	return systick_ms;
}

/***********************************************
	函数名称：	TIM2_init() 
	功能介绍：	初始化TIM2
	函数参数：	无
	返回值：		无
 ***********************************************/
void TIM2_init(void) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 				//①时钟 TIM2 使能	
	//定时器 TIM2 初始化
	TIM_TimeBaseStructure.TIM_Period = 20000; 										//设置自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 71; 									//设置时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		//设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  						//②初始化 TIM2
	TIM_ARRPreloadConfig(TIM2, DISABLE);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );  									//③允许更新中断
	
	//中断优先级 NVIC 设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  						//TIM2 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	//先占优先级 0 级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  				//从优先级 2 级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  						//IRQ 通道被使能
	NVIC_Init(&NVIC_InitStructure);  														//④初始化 NVIC 寄存器
	TIM_Cmd(TIM2, ENABLE);  																		//⑤使能 TIM2
}

/***********************************************
	函数名称：	TIM2_IRQHandler() 
	功能介绍：	输出舵机控制波形
	函数参数：	无
	返回值：		无
 ***********************************************/
void TIM2_IRQHandler(void) {
	static u8 flag = 0;
	int temp;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 					//检查 TIM2 更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update ); 							//清除 TIM2 更新中断标志
		if(servo_data[servo_index].cur>2495)	servo_data[servo_index].cur=2495;
		if(servo_data[servo_index].cur<500)		servo_data[servo_index].cur=500;
				
		if(!flag) {
			TIM2->ARR = ((unsigned int)(servo_data[servo_index].cur));
			servo_set(servo_index, 1);
		} else {
			temp = 2500 - (unsigned int)(servo_data[servo_index].cur);
			if(temp < 20)temp = 20;
			TIM2->ARR = temp;
			servo_set(servo_index, 0);
			servo_index ++;
		}
		if(servo_index >= SERVO_NUM) {
			servo_index = 0;
		}
		flag = !flag;
	}
} 
